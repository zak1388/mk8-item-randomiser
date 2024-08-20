CC=gcc
CFLAGS=

all: console graphical 

outputfolder:
	mkdir -p output

items: outputfolder items.c items.h
	$(CC) $(CFLAGS) -c -o output/items.o items.c

graphical: outputfolder items graphical.c graphical.h
	$(CC) $$(pkg-config --cflags gtk4) $(CFLAGS) -o output/graphical output/items.o graphical.c $$(pkg-config --libs gtk4)

console: outputfolder items console.h console.c
	$(CC) -o output/console output/items.o console.c $(CFLAGS)

clean:
	rm output/*

