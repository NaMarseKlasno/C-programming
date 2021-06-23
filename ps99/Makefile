CFLAGS= -std=c11 -Werror -Wall -Wconversion -lm
OUTPUT = ps99

all: $(OUTPUT)
$(OUTPUT): main.c playlist.c playlist.h track.c track.h
	$(CC) $(CFLAGS) main.c playlist.c track.c -o $/$(OUTPUT)

playlist.o: playlist.c playlist.h
	gcc $(CFLAGS) -c playlist.c -o $/playlist.o

track.o: track.c track.h
	gcc $(CFLAGS) -c track.c -o $/track.o

main.o: main.c
	gcc $(CFLAGS) -c main.c -o $/main.o

clean:
	rm -rf /$(OUTPUT) *.0