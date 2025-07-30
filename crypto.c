#include "sshd.h"

static unsigned char rc4_s[256];
static int rc4_i = 0, rc4_j = 0;

void rc4_init(unsigned char *key, int keylen) {
    int i, j;
    unsigned char tmp;
    
    /* Initialize S-box */
    for (i = 0; i < 256; i++) {
        rc4_s[i] = i;
    }
    
    /* Key scheduling algorithm */
    j = 0;
    for (i = 0; i < 256; i++) {
        j = (j + rc4_s[i] + key[i % keylen]) & 0xFF;
        tmp = rc4_s[i];
        rc4_s[i] = rc4_s[j];
        rc4_s[j] = tmp;
    }
    
    rc4_i = rc4_j = 0;
}

void rc4_crypt(unsigned char *data, int len) {
    int k;
    unsigned char tmp;
    
    for (k = 0; k < len; k++) {
        rc4_i = (rc4_i + 1) & 0xFF;
        rc4_j = (rc4_j + rc4_s[rc4_i]) & 0xFF;
        
        tmp = rc4_s[rc4_i];
        rc4_s[rc4_i] = rc4_s[rc4_j];
        rc4_s[rc4_j] = tmp;
        
        data[k] ^= rc4_s[(rc4_s[rc4_i] + rc4_s[rc4_j]) & 0xFF];
    }
}

/* Simple modular exponentiation for DH */
unsigned long modexp(unsigned long base, unsigned long exp, unsigned long mod) {
    unsigned long result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    
    return result;
}