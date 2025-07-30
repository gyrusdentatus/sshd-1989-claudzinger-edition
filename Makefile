CC = gcc
CFLAGS = -O2 -Wall -std=c89 -D_GNU_SOURCE
LDFLAGS = -lcrypt -lutil

SSHD_OBJS = sshd.o crypto.o kex.o auth.o shell.o
CLIENT_OBJS = ssh_client.o crypto.o

all: sshd ssh_client

sshd: $(SSHD_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

ssh_client: $(CLIENT_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c sshd.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o sshd ssh_client

install: sshd
	install -m 755 sshd /usr/local/sbin/
	@echo "Remember to run as root for port 22!"

.PHONY: all clean install