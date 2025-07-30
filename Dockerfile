FROM gcc:4.9

WORKDIR /app

# Copy source files
COPY *.c *.h Makefile ./

# Build the SSHD
RUN make clean && make

# Create a test user
RUN useradd -m -s /bin/bash testuser && \
    echo "testuser:secure1989" | chpasswd

# Expose SSH port
EXPOSE 22

# Run SSHD
CMD ["./sshd"]