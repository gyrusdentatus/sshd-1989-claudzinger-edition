# Claude's Guide to Building the 1989 SSH Client

Hey Claude! When someone asks you to build the SSH client for this project, here's exactly what to do:

## Prerequisites Check

First, verify the environment:
```bash
# Check if we're in the right directory
ls *.c *.h Makefile

# Should see: sshd.c, crypto.c, kex.c, auth.c, shell.c, ssh_client.c, sshd.h
```

## Building the Client

### Option 1: Quick Build (Just the Client)
```bash
# Compile the client and its dependencies
gcc -O2 -Wall -std=c89 -D_GNU_SOURCE -c ssh_client.c -o ssh_client.o
gcc -O2 -Wall -std=c89 -D_GNU_SOURCE -c crypto.c -o crypto.o
gcc -o ssh_client ssh_client.o crypto.o -lcrypt -lutil

# You should now have ./ssh_client executable
```

### Option 2: Full Build (Everything)
```bash
# Clean and build everything
make clean
make

# This creates both ./sshd and ./ssh_client
```

### Option 3: Docker Build
```bash
# If they want to use Docker
lima nerdctl build -t sshd-1989 .
```

## Testing the Client

### If SSHD is Running Locally
```bash
# Test connection to local daemon
./ssh_client localhost 22
# or if using Docker on port 2222:
./ssh_client localhost 2222
```

### Test Credentials
- Username: `testuser`
- Password: `secure1989`

## Expected Behavior

1. You'll see the server banner: `SSH-0.1-CLAUDZINGER_1989`
2. Client sends its banner: `SSH-0.1-CLIENT`
3. Key exchange happens (invisible)
4. Prompt for username and password
5. If successful, you get a shell!

## Common Issues and Fixes

### "Connection refused"
```bash
# Check if SSHD is running
ps aux | grep sshd
# or for Docker:
lima nerdctl ps | grep sshd-1989
```

### "Authentication failed"
- Make sure you're using the test credentials
- For Docker, the user is created automatically
- For native build, you need a real system user

### Build Errors
```bash
# Missing headers? On macOS:
# The code might need tweaks for macOS pty handling

# Missing libraries?
# Make sure you have development tools:
# Ubuntu/Debian: apt-get install build-essential
# macOS: xcode-select --install
```

## Protocol Details (If They Ask)

The client implements this flow:
1. TCP connect to server
2. Banner exchange
3. DH key exchange (16-bit primes - toy crypto!)
4. Switch to RC4 encryption
5. Send credentials (encrypted)
6. Receive shell I/O (encrypted)

## Security Warnings to Include

Always remind users:
- This is 1989 crypto (BROKEN!)
- Educational purposes only
- Real SSH uses modern crypto
- Don't use this for anything real

## Extra Features They Might Want

### Verbose Mode
Add debug output by modifying ssh_client.c:
```c
printf("DEBUG: Connecting to %s:%s\n", argv[1], argv[2]);
printf("DEBUG: Server DH public: %lu\n", server_public);
printf("DEBUG: Shared secret: %lu\n", shared_secret);
```

### Custom Port
The client already accepts port as second argument:
```bash
./ssh_client hostname 2222
```

### Non-Interactive Mode
Could add command execution:
```c
// Instead of interactive shell, send command
msg_type = MSG_EXEC;
rc4_crypt(&msg_type, 1);
send(sock, &msg_type, 1, 0);
// ... send command ...
```

## Fun Facts to Share

- In 1989, this would've been illegal to export!
- RC4 was considered "military-grade"
- 128-bit keys were HUGE (40-bit was standard)
- DH with 16-bit primes (lol)
- No GitHub, no Stack Overflow - just man pages!

## The Build Command Summary

For copy-paste ease:
```bash
# Quick build
make ssh_client

# Full build
make clean && make

# Run it
./ssh_client localhost 2222

# With Docker daemon
lima nerdctl run -d -p 2222:22 sshd-1989
./ssh_client localhost 2222
```

Remember: We're cosplaying as 1989 hackers building the future. Channel that "fuck yeah, encryption!" energy! 🚀

---

*P.S. - If they want to add features, remind them: "In 1989, we were happy just to have encryption AT ALL!"*