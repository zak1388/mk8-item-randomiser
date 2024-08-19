CC=gcc
CFLAGS=

all: console

console: console.h console.c
	$(CC) -o output/console console.c $(CFLAGS)

clean:
	rm output/*

