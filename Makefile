CFLAGS= -std=c11 -Werror -Wall
OUTPUT = ps1

all: $(OUTPUT)

ps1: playfair.o bmp.o main.o
	gcc $(CFLAGS) -lm playfair.o bmp.o main.o -o ps1

main.o: main.c
	gcc $(CFLAGS) -lm -c main.c -o main.o

playfire.o: playfair.c playfair.h
	gcc $(CFLAGS) -lm -c bmp.c -o playfair.o

bmp.o: bmp.c bmp.h
	gcc $(CFLAGS) -lm -c bmp.c -o bmp.o

clean:
	rm -rf $(OUTPUT) *.0
