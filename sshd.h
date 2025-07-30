#ifndef SSHD_H
#define SSHD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <pwd.h>
#include <sys/wait.h>
#include <arpa/inet.h>

#define SSH_PORT 22
#define BANNER "SSH-0.1-CLAUDZINGER_1989\r\n"
#define MAX_CLIENTS 10
#define BUFFER_SIZE 4096

#define DH_P 65537  /* Small prime for 1989 - we're not paranoid yet! */
#define DH_G 3

typedef struct {
    int socket;
    unsigned char session_key[16];  /* 128-bit keys - HUGE for 1989! */
    int authenticated;
    char username[32];
    pid_t shell_pid;
} ssh_session_t;

/* Protocol messages */
#define MSG_KEXINIT     1
#define MSG_KEXREPLY    2
#define MSG_AUTH        3
#define MSG_AUTH_OK     4
#define MSG_AUTH_FAIL   5
#define MSG_DATA        6
#define MSG_DISCONNECT  7

/* Function prototypes */
void handle_client(int client_sock);
int do_key_exchange(ssh_session_t *session);
int authenticate_user(ssh_session_t *session);
void run_shell(ssh_session_t *session);

/* Crypto functions */
void rc4_init(unsigned char *key, int keylen);
void rc4_crypt(unsigned char *data, int len);
unsigned long modexp(unsigned long base, unsigned long exp, unsigned long mod);

#endif /* SSHD_H */