#include "sshd.h"

int server_socket;

void sigchld_handler(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

void cleanup(int sig) {
    printf("\nShutting down SSHD...\n");
    close(server_socket);
    exit(0);
}

int main(int argc, char *argv[]) {
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_sock;
    pid_t pid;
    
    printf("CLAUDZINGER'S SECURE SHELL DAEMON v0.1 (1989)\n");
    printf("The Future of Remote Access is HERE!\n\n");
    
    /* Set up signal handlers */
    signal(SIGCHLD, sigchld_handler);
    signal(SIGINT, cleanup);
    
    /* Create socket */
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        exit(1);
    }
    
    /* Allow socket reuse */
    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    /* Bind to port 22 */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SSH_PORT);
    
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        printf("Hint: You might need to run as root for port 22!\n");
        exit(1);
    }
    
    /* Listen for connections */
    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("listen");
        exit(1);
    }
    
    printf("Listening on port %d...\n", SSH_PORT);
    printf("Connect with: nc localhost %d\n\n", SSH_PORT);
    
    /* Main server loop */
    while (1) {
        client_sock = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_sock < 0) {
            perror("accept");
            continue;
        }
        
        printf("New connection from %s:%d\n", 
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        
        /* Fork to handle client */
        pid = fork();
        if (pid < 0) {
            perror("fork");
            close(client_sock);
        } else if (pid == 0) {
            /* Child process */
            close(server_socket);
            handle_client(client_sock);
            exit(0);
        } else {
            /* Parent process */
            close(client_sock);
        }
    }
    
    return 0;
}

void handle_client(int client_sock) {
    ssh_session_t session;
    char buffer[BUFFER_SIZE];
    int n;
    
    memset(&session, 0, sizeof(session));
    session.socket = client_sock;
    
    /* Send banner */
    send(client_sock, BANNER, strlen(BANNER), 0);
    
    /* Read client banner */
    n = recv(client_sock, buffer, sizeof(buffer)-1, 0);
    if (n <= 0) {
        close(client_sock);
        return;
    }
    buffer[n] = '\0';
    printf("Client banner: %s", buffer);
    
    /* Key exchange */
    if (!do_key_exchange(&session)) {
        printf("Key exchange failed!\n");
        close(client_sock);
        return;
    }
    
    printf("Encryption established! (RC4 with 128-bit key)\n");
    
    /* Authentication */
    if (!authenticate_user(&session)) {
        printf("Authentication failed!\n");
        close(client_sock);
        return;
    }
    
    printf("User '%s' authenticated successfully!\n", session.username);
    
    /* Run shell */
    run_shell(&session);
    
    close(client_sock);
}