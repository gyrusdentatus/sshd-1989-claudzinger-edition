#!/bin/bash

echo "=================================="
echo "TESTING CLAUDZINGER'S SSHD (1989)"
echo "=================================="
echo
echo "1. Testing with netcat (banner only):"
echo "--------------------------------------"
echo "SSH-0.1-CLIENT" | nc -w 2 localhost 2223 | head -1
echo
echo "2. To connect with full encryption:"
echo "-----------------------------------"
echo "First, build the client:"
echo "  make ssh_client"
echo
echo "Then connect:"
echo "  ./ssh_client localhost 2223"
echo
echo "Test credentials:"
echo "  Username: testuser"
echo "  Password: secure1989"
echo
echo "=================================="
echo "THE FUTURE IS NOW! NO MORE TELNET!"
echo "==================================">