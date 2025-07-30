#include "sshd.h"

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    unsigned char msg_type;
    unsigned long client_private, client_public, server_public, shared_secret;
    unsigned char session_key[16];
    char username[32], password[32];
    int n, i;
    
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        fprintf(stderr, "Example: %s localhost 22\n", argv[0]);
        exit(1);
    }
    
    printf("CLAUDZINGER'S SSH CLIENT v0.1 (1989)\n");
    printf("Connecting to %s:%s...\n", argv[1], argv[2]);
    
    /* Create socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }
    
    /* Connect to server */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(1);
    }
    
    /* Exchange banners */
    n = recv(sock, buffer, sizeof(buffer)-1, 0);
    buffer[n] = '\0';
    printf("Server: %s", buffer);
    
    send(sock, "SSH-0.1-CLIENT\r\n", 16, 0);
    
    /* Key exchange */
    n = recv(sock, &msg_type, 1, 0);
    if (msg_type != MSG_KEXINIT) {
        fprintf(stderr, "Unexpected message type: %d\n", msg_type);
        exit(1);
    }
    
    n = recv(sock, buffer, sizeof(buffer)-1, 0);
    buffer[n] = '\0';
    server_public = strtoul(buffer, NULL, 10);
    
    /* Generate client DH keypair */
    srand(time(NULL));
    client_private = (rand() % (DH_P - 2)) + 1;
    client_public = modexp(DH_G, client_private, DH_P);
    
    /* Send our public key */
    msg_type = MSG_KEXREPLY;
    send(sock, &msg_type, 1, 0);
    sprintf(buffer, "%lu", client_public);
    send(sock, buffer, strlen(buffer), 0);
    
    /* Compute shared secret */
    shared_secret = modexp(server_public, client_private, DH_P);
    
    /* Derive session key */
    for (i = 0; i < 16; i++) {
        session_key[i] = (shared_secret >> (8 * (i % 4))) & 0xFF;
    }
    
    /* Initialize encryption */
    rc4_init(session_key, 16);
    printf("Encryption established!\n");
    
    /* Authentication */
    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    
    printf("Password: ");
    system("stty -echo");
    fgets(password, sizeof(password), stdin);
    system("stty echo");
    printf("\n");
    password[strcspn(password, "\n")] = '\0';
    
    /* Send auth request */
    msg_type = MSG_AUTH;
    rc4_crypt(&msg_type, 1);
    send(sock, &msg_type, 1, 0);
    
    strcpy(buffer, username);
    rc4_crypt((unsigned char *)buffer, 32);
    send(sock, buffer, 32, 0);
    
    strcpy(buffer, password);
    rc4_crypt((unsigned char *)buffer, 32);
    send(sock, buffer, 32, 0);
    
    /* Check auth response */
    recv(sock, &msg_type, 1, 0);
    rc4_crypt(&msg_type, 1);
    
    if (msg_type != MSG_AUTH_OK) {
        fprintf(stderr, "Authentication failed!\n");
        exit(1);
    }
    
    printf("Authentication successful! Enjoy your ENCRYPTED shell!\n\n");
    
    /* Set raw mode for terminal */
    system("stty raw -echo");
    
    /* Main I/O loop */
    fd_set rfds;
    while (1) {
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);  /* stdin */
        FD_SET(sock, &rfds);
        
        if (select(sock + 1, &rfds, NULL, NULL, NULL) < 0) {
            break;
        }
        
        /* Input from user */
        if (FD_ISSET(0, &rfds)) {
            n = read(0, buffer + 1, sizeof(buffer) - 2);
            if (n <= 0) break;
            
            buffer[0] = MSG_DATA;
            rc4_crypt((unsigned char *)buffer, n + 1);
            send(sock, buffer, n + 1, 0);
        }
        
        /* Data from server */
        if (FD_ISSET(sock, &rfds)) {
            n = recv(sock, buffer, sizeof(buffer), 0);
            if (n <= 0) break;
            
            rc4_crypt((unsigned char *)buffer, n);
            
            if (buffer[0] == MSG_DATA && n > 1) {
                write(1, buffer + 1, n - 1);
            }
        }
    }
    
    /* Restore terminal */
    system("stty sane");
    
    close(sock);
    return 0;
}