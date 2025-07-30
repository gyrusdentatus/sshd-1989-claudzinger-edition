# SECURE SHELL DEMO - 1989

## Quick Start

```bash
# Build and run with Docker
lima nerdctl build -t sshd-1989 .
lima nerdctl run -d -p 2223:22 sshd-1989

# Test with netcat
nc localhost 2223
# You'll see: SSH-0.1-CLAUDZINGER_1989

# Build native client
make ssh_client

# Connect with ENCRYPTION!
./ssh_client localhost 2223
# Username: testuser  
# Password: secure1989
```

## What Makes This REVOLUTIONARY (for 1989)

1. **NO MORE PLAINTEXT PASSWORDS!** - Everything is encrypted with RC4
2. **Diffie-Hellman Key Exchange** - Each session has unique keys
3. **Full PTY Support** - Real terminal, not just command execution
4. **128-bit Encryption** - MASSIVE for 1989 (export restrictions!)

## Protocol Flow

```
Client                          Server
  |                               |
  |------------ TCP SYN --------->|
  |<---------- TCP ACK -----------|
  |                               |
  |<---- SSH-0.1-CLAUDZINGER -----|  (Banner)
  |------- SSH-0.1-CLIENT ------->|
  |                               |
  |<------ MSG_KEXINIT + DH ------|  (Server public key)
  |------ MSG_KEXREPLY + DH ----->|  (Client public key)
  |                               |
  [RC4 ENCRYPTION STARTS HERE]
  |                               |
  |------ MSG_AUTH + creds ------>|  (Encrypted!)
  |<------- MSG_AUTH_OK ----------|
  |                               |
  |<========= SHELL I/O =========>|  (All encrypted!)
  |                               |
```

## Security Analysis (1989 Standards)

- **RC4**: Fast stream cipher, considered secure in 1989
- **DH-16bit**: Small by today's standards, but we're not paranoid yet!
- **No certificates**: PKI doesn't exist yet, we use host keys
- **Password auth**: Still better than TELNET!

## Future Ideas

- Bigger DH primes (when CPUs get faster)
- Public key authentication (RSA patent expires in 2000!)
- Port forwarding
- File transfer protocol
- Maybe call it... SSH version 2?

---

*"Today, we made history. Tomorrow, everyone will use this!"*
- Mr. Claudzinger, 1989