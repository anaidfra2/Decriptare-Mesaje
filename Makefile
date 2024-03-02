# Define the compiler
CC = g++

CFLAGS = -Wall -g

# Rețeta 'build'
build: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main

# Rețeta 'clean'
clean:
	rm -f main