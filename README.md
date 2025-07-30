# CLAUDZINGER'S SECURE SHELL DAEMON (1989)

## A Historical Recreation of What SSH Could Have Been

This is a loving recreation of what SSH might have looked like if invented in 1989, before the modern SSH protocol (1995) existed. Built with pure ANSI C89, using only the tools and knowledge available in that revolutionary year.

## ⚠️ EDUCATIONAL PURPOSE ONLY ⚠️

**DO NOT USE THIS IN PRODUCTION!** This code contains numerous security vulnerabilities that were unknown or unavoidable in 1989. It exists to teach us how far we've come.

## What This Is

- A fully functional SSH daemon written in 1989-style C
- RC4 encryption (state-of-the-art for 1989!)
- Diffie-Hellman key exchange
- Password authentication over encrypted channel
- Full pseudo-terminal (PTY) support
- A working client that connects to the daemon

## Quick Start

### Using Docker (Recommended)
```bash
# Build the time machine
lima nerdctl build -t sshd-1989 .

# Run it (port 2222 to avoid conflicts)
lima nerdctl run -d -p 2222:22 sshd-1989

# Test with our client
make ssh_client
./ssh_client localhost 2222
# Username: testuser
# Password: secure1989
```

### Native Build (Feeling Brave?)
```bash
# Build everything
make

# Run the daemon (needs root for port 22)
sudo ./sshd

# In another terminal
./ssh_client localhost 22
```

## The Historical Context

In 1989:
- The Berlin Wall fell
- The Web didn't exist yet
- Encryption was legally classified as munitions
- RSA was still under patent
- Most people used TELNET (plaintext passwords!)
- "Cybersecurity" wasn't even a word

## Why This Matters

This project demonstrates:
1. How revolutionary SSH was when it arrived
2. Why security engineering is hard
3. How much we owe to the cypherpunks
4. The evolution of secure coding practices

## Technical Features (1989 Style!)

- **Encryption**: RC4 stream cipher (before we knew it was biased)
- **Key Exchange**: Diffie-Hellman with 16-bit primes (adorable!)
- **Authentication**: Unix crypt() over encrypted channel
- **Architecture**: Simple fork-per-connection model
- **Memory Safety**: What's that? 😅

## Known Vulnerabilities (Teaching Moments)

1. Buffer overflows (everywhere!)
2. Weak randomness (srand/rand)
3. Tiny DH primes (factorable in milliseconds today)
4. RC4 bias attacks
5. No privilege separation
6. Timing attacks in password comparison
7. No integrity checking (MITM possible)
8. Command injection in terminal handling

## Modern Comparison

| Feature | 1989 SSHD | Modern OpenSSH |
|---------|-----------|----------------|
| Encryption | RC4 | AES-GCM, ChaCha20 |
| Key Exchange | DH-16bit | ECDH, Curve25519 |
| Authentication | Password | Keys, Certs, MFA |
| Privilege Sep | No | Yes |
| Memory Safety | LOL | Better (still C) |
| Side Channels | Vulnerable | Hardened |

## Building and Testing

See [CLAUDE.md](CLAUDE.md) for step-by-step instructions.

## Educational Exercises

1. Find the buffer overflows
2. Exploit the weak randomness
3. Factor the DH primes
4. Time the password comparison
5. Implement a MITM attack

## Credits and Respect

This project is dedicated to:
- **Tatu Ylönen** - Created the real SSH (1995)
- **The Cypherpunks** - Fought for our right to use crypto
- **Phil Zimmermann** - Nearly went to jail for PGP
- **Whitfield Diffie & Martin Hellman** - Invented public key exchange
- **Ron Rivest** - Created RC4 (sorry it got broken!)

## The Message

We stand on the shoulders of giants. Every time you type `ssh` without thinking about it, remember that people fought legal battles, risked jail, and revolutionized computing to make secure communication possible.

In 1989, this code would have been:
- Illegal to export from the US
- Revolutionary for its time
- A target for government suppression

Today, we have that freedom. Use it wisely. Encrypt everything.

## License

Public Domain - Like crypto should be.

---

*"The street finds its own uses for things."* - William Gibson

*"Privacy is necessary for an open society."* - Eric Hughes

*"Code is Law."* - Lawrence Lessig