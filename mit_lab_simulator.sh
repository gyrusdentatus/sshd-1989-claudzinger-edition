#!/bin/bash
# MIT Computer Lab Simulator (1989)
# "What the sysadmin sees vs what's really happening"

# Colors for the show
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}=== MIT ATHENA WORKSTATION ===${NC}"
echo "Username: hans@ATHENA.MIT.EDU"
echo "Quota: 10 CPU hours (2.3 used)"
echo "Active processes: 3"
echo ""

# The Show Terminal (what admins see)
simulate_normal_work() {
  while true; do
    echo -e "${GREEN}[$$]${NC} Compiling assignment3.c..."
    sleep 3
    echo "  -> Parsing source file..."
    sleep 2
    echo "  -> Optimizing loops..."
    sleep 2
    echo "  -> Linking object files..."
    sleep 4
    echo -e "${GREEN}[$$]${NC} Build successful"
    echo ""
    sleep 5
    
    echo -e "${GREEN}[$$]${NC} Running LaTeX on thesis_draft.tex"
    sleep 2
    echo "  -> Processing chapter 1..."
    sleep 3
    echo "  -> Generating bibliography..."
    sleep 2
    echo "  -> Output: thesis_draft.pdf (142 pages)"
    echo ""
    sleep 5
    
    echo -e "${GREEN}[$$]${NC} Analyzing dataset for 6.033 project"
    sleep 2
    for i in {1..5}; do
      echo "  -> Data point $((RANDOM % 1000)): correlation 0.$((RANDOM % 999))"
      sleep 1
    done
    echo ""
  done
}

# What's REALLY running (hidden)
the_real_work() {
  # Terminal 1: SSH daemon development
  exec -a "cc -O2 network_hw.c" ./sshd 2>&1 | \
    sed 's/SSH/NET/g; s/crypto/math/g; s/password/dataset/g' > /dev/null &
  
  # Terminal 2: Cracking DES (for research!)
  exec -a "gnuplot thesis_data.csv" ./des_cracker 2>&1 | \
    sed 's/cracking/analyzing/g; s/key found/pattern detected/g' > /dev/null &
  
  # Terminal 3: IRC for crypto discussions
  exec -a "vi ~/.emacs" nc irc.freenode.net 6667 > /dev/null 2>&1 &
  
  # Terminal 4: The tunnel to home
  mkfifo /tmp/.academic_pipe 2>/dev/null
  exec -a "latex thesis.tex" sh -c 'nc -l -p 31337 < /tmp/.academic_pipe | nc home.server 22 > /tmp/.academic_pipe' &
}

# The Panic Button Simulator
show_panic() {
  echo ""
  echo -e "${RED}[ALERT] Sysadmin detected! Activating countermeasures...${NC}"
  sleep 0.5
  
  # Kill the evidence
  killall -q sshd des_cracker nc 2>/dev/null
  
  # Flood with academic nonsense
  echo "Segmentation fault in matrix_multiply() at line 42"
  echo "Dumping core..."
  echo ""
  
  # Open innocent apps
  echo "Recovering by opening saved work..."
  echo " -> emacs homework4.c"
  echo " -> gnuplot experiment_results.dat"
  echo " -> pine (checking homework email)"
  echo ""
  echo "Recovery complete. Continue working on assignments."
}

# The Network Monitor Faker
fake_network_activity() {
  echo -e "\n${BLUE}Network Activity Monitor:${NC}"
  while true; do
    # Show fake legitimate traffic
    echo "[$(date +%H:%M:%S)] HTTP  -> web.mit.edu (GET /~hans/homework.html)"
    sleep 3
    echo "[$(date +%H:%M:%S)] NFS   -> athena-fs.mit.edu (READ thesis_draft.tex)"
    sleep 2
    echo "[$(date +%H:%M:%S)] SMTP  -> mail.mit.edu (HELO student.mit.edu)"
    sleep 4
    echo "[$(date +%H:%M:%S)] DNS   -> ns.mit.edu (QUERY web.mit.edu)"
    sleep 2
    
    # Hide the real traffic in between
    # [ACTUAL: nc crypto.underground.net 1337]
  done
}

# The CPU Time Hider
hide_cpu_usage() {
  # Spread load across multiple innocent process names
  INNOCENT_NAMES=(
    "pdflatex thesis.tex"
    "matlab -nodisplay"
    "mathematica -script"
    "spice circuit.cir"
    "gfortran simulate.f90"
  )
  
  for name in "${INNOCENT_NAMES[@]}"; do
    # Run a piece of real work with fake name
    exec -a "$name" sh -c 'while true; do echo "Working..." > /dev/null; done' &
  done
}

# The Main Show
main() {
  clear
  echo -e "${BLUE}╔══════════════════════════════════════════╗${NC}"
  echo -e "${BLUE}║   MIT ATHENA WORKSTATION LAB 26-100      ║${NC}"
  echo -e "${BLUE}║   'What happens in Athena...'            ║${NC}"
  echo -e "${BLUE}╚══════════════════════════════════════════╝${NC}"
  echo ""
  
  # Start the real work (hidden)
  the_real_work
  
  # Show the fake work
  simulate_normal_work &
  FAKE_PID=$!
  
  # Monitor for sysadmin
  trap show_panic INT
  
  echo "Press Ctrl+C to simulate sysadmin approach..."
  echo ""
  
  # Wait for interrupt
  wait $FAKE_PID
}

# The "ps" output faker
fake_ps() {
  cat << 'PS_OUTPUT'
USER   PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
hans  1234  0.1  0.1   2048  1024 pts/0    S    14:30   0:01 vi thesis.tex
hans  1235  2.3  0.5   4096  2048 pts/1    R    14:31   0:15 cc -O2 homework.c
hans  1236  0.0  0.1   2048   512 pts/2    S    14:32   0:00 latex report.tex
hans  1237  1.2  0.3   3072  1536 pts/3    S    14:32   0:08 gnuplot data.csv
root  1238  0.0  0.0   1024   256 ?        S    14:00   0:00 [definitely not irc]
PS_OUTPUT
}

# If someone's watching...
if [ "$1" == "--demo" ]; then
  main
elif [ "$1" == "--ps" ]; then
  fake_ps
else
  echo "Starting 'homework compiler'..."
  exec -a "make -j4 final_project" "$0" --demo
fi