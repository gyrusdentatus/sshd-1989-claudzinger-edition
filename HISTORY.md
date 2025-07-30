# The History of Secure Shell: From Telnet to Today

## The Dark Ages: Pre-SSH Era (1969-1994)

### TELNET: The Original Sin
- Created in 1969 for ARPANET
- Passwords sent in PLAINTEXT
- Every keystroke visible to anyone on the network
- Still used in production in 1994 (!!!)

### The Problems Nobody Talked About
```
User: telnet server.com
Password: mypassword123  <-- VISIBLE TO EVERYONE
```
- Network admins could see everything
- Anyone with a packet sniffer owned you
- "Security through obscurity" was the norm

## The Crypto Wars (1970s-1990s)

### When Math Was Illegal
- **1976**: Diffie-Hellman published (NSA was PISSED)
- **1977**: RSA invented (patent wars begin)
- **1991**: PGP released (Phil Zimmermann investigated)
- **1992**: AT&T tries to suppress BSD's encryption

### Export Restrictions
- Crypto over 40 bits = "munitions"
- Books with code = legal (1st Amendment)
- Floppy disks with same code = federal crime
- T-shirts with RSA = weapons trafficking

## The Revolution: SSH is Born (1995)

### Tatu Ylönen's Moment
- Finnish researcher at Helsinki University
- Network password sniffed at university
- "Fuck this, I'll build something better"
- 5 months later: SSH-1.0 released

### Why SSH Was Revolutionary
1. **Everything Encrypted** - No more plaintext
2. **Key-Based Auth** - No passwords needed
3. **Port Forwarding** - Encrypted tunnels for everything
4. **X11 Forwarding** - Secure remote GUIs
5. **Free Software** - (Initially)

## The Timeline of Freedom

### 1995-1999: The Growth
- **1995**: SSH-1.0 released (July)
- **1996**: SSH Communications Security founded
- **1997**: IETF starts SSH-2.0 standardization
- **1999**: OpenSSH forked (FREE FOREVER!)

### Key Moments
- **1995**: 20,000 users in 50 countries (in 5 months!)
- **1996**: Commercial version (some got angry)
- **1999**: OpenBSD team says "fuck commercial SSH"
- **2000**: OpenSSH becomes the standard

## The Technical Evolution

### SSH-1 (1995)
```
- RSA for key exchange
- 3DES/Blowfish for encryption
- CRC32 for integrity (oops)
- Simple and working
```

### SSH-2 (2006)
```
- Multiple key exchange methods
- Better crypto algorithms
- MAC for integrity
- Subsystems (SFTP)
- No more CRC32 vulnerability
```

### Modern SSH (2020s)
```
- Ed25519 keys
- ChaCha20-Poly1305
- Post-quantum ready
- Hardware key support
- Certificate authorities
```

## The Heroes We Forgot

### The Cypherpunks
- **Eric Hughes**: "Privacy is necessary for an open society"
- **Tim May**: Crypto Anarchist Manifesto
- **John Gilmore**: EFF co-founder, fought export laws
- **Julian Assange**: Yes, he was one too

### The Coders
- **Tatu Ylönen**: Created SSH
- **Theo de Raadt**: Led OpenSSH (still does!)
- **Damien Miller**: OpenSSH portable
- **Markus Friedl**: OpenSSH developer

### The Lawyers
- **Cindy Cohn**: Defended crypto in court
- **Lee Tien**: EFF lawyer, fought export controls
- **Eben Moglen**: Free software legal theory

## The Battles Won

### Legal Victories
- **1996**: Bernstein v. US (code = speech)
- **1999**: Export controls relaxed
- **2000**: RSA patent expires
- **Today**: Crypto is a human right (mostly)

### Technical Victories
- Telnet is (mostly) dead
- HTTPS everywhere
- End-to-end encryption normal
- Crypto in every pocket

## The Irony of Today

### We Won, But...
- **1995**: "Crypto for the masses!"
- **2025**: "Just use HTTP, it's fine"

### The New Battles
- Backdoor demands from governments
- "Lawful access" (same shit, new name)
- Quantum computing threats
- AI reading everything anyway

## Lessons from History

### 1. Freedom Isn't Free
People literally risked jail to give us crypto. Zimmermann was investigated for 3 years. Bernstein sued the government. They won so we could have nice things.

### 2. Standards Matter
SSH succeeded because:
- It solved a real problem
- It was better than alternatives
- It became a standard
- OpenSSH kept it free

### 3. The Fight Never Ends
- 1990s: "Crypto should be legal"
- 2000s: "Crypto should be standard"
- 2010s: "Crypto should be correct"
- 2020s: "Crypto should be quantum-safe"

### 4. Code Is Political
Every time you use SSH, you're using tools that were illegal to export. Every encrypted connection is a small act of rebellion against surveillance.

## Standing on Shoulders

When we built our 1989 SSH, we were imagining what could have been. But the real heroes actually did it:

- They fought the law (and won)
- They wrote the code (for free)
- They changed the world (forever)

Every `git push`, every `scp`, every `ssh` command works because someone said "fuck plaintext passwords" and did something about it.

## The Future

### What's Next?
- Post-quantum algorithms
- Decentralized identity
- Zero-knowledge proofs
- Homomorphic encryption

### The Eternal Vigilance
As long as there are those who would read our secrets, there must be those who build tools to keep them. The cypherpunks were right: privacy is necessary for an open society.

The price of privacy is eternal vigilance.

---

## Required Reading

- "Applied Cryptography" - Bruce Schneier
- "The Cypherpunk Manifesto" - Eric Hughes
- "Crypto" - Steven Levy
- "The Code Book" - Simon Singh

## Movies to Watch
- "The Imitation Game" (Turing's story)
- "Sneakers" (1992 hacker classic)
- "The Internet's Own Boy" (Aaron Swartz)

---

*"Those who would give up essential Liberty, to purchase a little temporary Safety, deserve neither Liberty nor Safety."* - Benjamin Franklin

*"Privacy is not for hiding wrongdoing, but for protecting what is most sacred."* - Unknown Cypherpunk