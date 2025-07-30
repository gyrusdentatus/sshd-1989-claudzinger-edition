#include "sshd.h"
#include <termios.h>
#include <sys/ioctl.h>
#include <pty.h>

void run_shell(ssh_session_t *session) {
    int master, slave;
    pid_t pid;
    char *slave_name;
    struct passwd *pw;
    fd_set rfds;
    char buffer[BUFFER_SIZE];
    int n, maxfd;
    unsigned char msg_type;
    
    /* Get user info */
    pw = getpwnam(session->username);
    if (!pw) return;
    
    /* Open pseudo-terminal */
    if (openpty(&master, &slave, NULL, NULL, NULL) < 0) {
        perror("openpty");
        return;
    }
    
    /* Fork child process */
    pid = fork();
    if (pid < 0) {
        perror("fork");
        close(master);
        close(slave);
        return;
    }
    
    if (pid == 0) {
        /* Child process - run shell */
        close(master);
        close(session->socket);
        
        /* Create new session */
        setsid();
        
        /* Make slave the controlling terminal */
        ioctl(slave, TIOCSCTTY, 0);
        
        /* Redirect stdio to slave */
        dup2(slave, 0);
        dup2(slave, 1);
        dup2(slave, 2);
        close(slave);
        
        /* Set environment */
        setenv("USER", pw->pw_name, 1);
        setenv("HOME", pw->pw_dir, 1);
        setenv("SHELL", pw->pw_shell, 1);
        setenv("TERM", "vt100", 1);
        
        /* Change to user */
        setgid(pw->pw_gid);
        setuid(pw->pw_uid);
        chdir(pw->pw_dir);
        
        /* Execute shell */
        execl(pw->pw_shell, pw->pw_shell, "-i", NULL);
        perror("execl");
        exit(1);
    }
    
    /* Parent process - relay data */
    close(slave);
    session->shell_pid = pid;
    
    /* Set non-blocking mode */
    fcntl(master, F_SETFL, O_NONBLOCK);
    fcntl(session->socket, F_SETFL, O_NONBLOCK);
    
    /* Main I/O loop */
    while (1) {
        FD_ZERO(&rfds);
        FD_SET(master, &rfds);
        FD_SET(session->socket, &rfds);
        maxfd = (master > session->socket) ? master : session->socket;
        
        if (select(maxfd + 1, &rfds, NULL, NULL, NULL) < 0) {
            if (errno == EINTR) continue;
            break;
        }
        
        /* Data from shell to client */
        if (FD_ISSET(master, &rfds)) {
            n = read(master, buffer + 1, sizeof(buffer) - 2);
            if (n <= 0) break;
            
            buffer[0] = MSG_DATA;
            rc4_crypt((unsigned char *)buffer, n + 1);
            send(session->socket, buffer, n + 1, 0);
        }
        
        /* Data from client to shell */
        if (FD_ISSET(session->socket, &rfds)) {
            n = recv(session->socket, buffer, sizeof(buffer), 0);
            if (n <= 0) break;
            
            rc4_crypt((unsigned char *)buffer, n);
            
            if (buffer[0] == MSG_DATA && n > 1) {
                write(master, buffer + 1, n - 1);
            } else if (buffer[0] == MSG_DISCONNECT) {
                break;
            }
        }
    }
    
    /* Clean up */
    close(master);
    kill(session->shell_pid, SIGTERM);
    waitpid(session->shell_pid, NULL, 0);
}