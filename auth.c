#include "sshd.h"
#include <crypt.h>
#include <shadow.h>

int authenticate_user(ssh_session_t *session) {
    unsigned char msg_type;
    char username[32], password[32];
    char buffer[BUFFER_SIZE];
    struct passwd *pw;
    struct spwd *sp;
    char *encrypted;
    int n;
    
    /* Receive auth request */
    n = recv(session->socket, buffer, 1, 0);
    if (n <= 0) return 0;
    
    /* Decrypt message type */
    rc4_crypt((unsigned char *)buffer, 1);
    msg_type = buffer[0];
    
    if (msg_type != MSG_AUTH) {
        return 0;
    }
    
    /* Receive username */
    n = recv(session->socket, buffer, 32, 0);
    if (n <= 0) return 0;
    rc4_crypt((unsigned char *)buffer, n);
    strncpy(username, buffer, sizeof(username)-1);
    username[sizeof(username)-1] = '\0';
    
    /* Receive password */
    n = recv(session->socket, buffer, 32, 0);
    if (n <= 0) return 0;
    rc4_crypt((unsigned char *)buffer, n);
    strncpy(password, buffer, sizeof(password)-1);
    password[sizeof(password)-1] = '\0';
    
    /* Look up user */
    pw = getpwnam(username);
    if (!pw) {
        msg_type = MSG_AUTH_FAIL;
        rc4_crypt(&msg_type, 1);
        send(session->socket, &msg_type, 1, 0);
        return 0;
    }
    
    /* Get shadow password if available */
    sp = getspnam(username);
    encrypted = crypt(password, sp ? sp->sp_pwdp : pw->pw_passwd);
    
    if (strcmp(encrypted, sp ? sp->sp_pwdp : pw->pw_passwd) != 0) {
        msg_type = MSG_AUTH_FAIL;
        rc4_crypt(&msg_type, 1);
        send(session->socket, &msg_type, 1, 0);
        return 0;
    }
    
    /* Success! */
    strncpy(session->username, username, sizeof(session->username)-1);
    session->authenticated = 1;
    
    msg_type = MSG_AUTH_OK;
    rc4_crypt(&msg_type, 1);
    send(session->socket, &msg_type, 1, 0);
    
    return 1;
}