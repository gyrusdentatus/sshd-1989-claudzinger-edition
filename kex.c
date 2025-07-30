#include "sshd.h"
#include <time.h>

int do_key_exchange(ssh_session_t *session) {
    unsigned long server_private, server_public;
    unsigned long client_public, shared_secret;
    unsigned char msg_type;
    char buffer[256];
    int n;
    
    /* Generate server's DH keypair */
    srand(time(NULL) ^ getpid());
    server_private = (rand() % (DH_P - 2)) + 1;
    server_public = modexp(DH_G, server_private, DH_P);
    
    /* Send KEXINIT with our public key */
    msg_type = MSG_KEXINIT;
    send(session->socket, &msg_type, 1, 0);
    sprintf(buffer, "%lu", server_public);
    send(session->socket, buffer, strlen(buffer), 0);
    
    /* Receive client's public key */
    n = recv(session->socket, &msg_type, 1, 0);
    if (n <= 0 || msg_type != MSG_KEXREPLY) {
        return 0;
    }
    
    n = recv(session->socket, buffer, sizeof(buffer)-1, 0);
    if (n <= 0) {
        return 0;
    }
    buffer[n] = '\0';
    client_public = strtoul(buffer, NULL, 10);
    
    /* Compute shared secret */
    shared_secret = modexp(client_public, server_private, DH_P);
    
    /* Derive session key from shared secret */
    /* In 1989, we just use the bits directly! */
    int i;
    for (i = 0; i < 16; i++) {
        session->session_key[i] = (shared_secret >> (8 * (i % 4))) & 0xFF;
    }
    
    /* Initialize RC4 with session key */
    rc4_init(session->session_key, 16);
    
    return 1;
}