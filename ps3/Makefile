CFLAGS= -std=c11 -Werror -Wall -Wconversion
OUTPUT = game

all: $(OUTPUT)

hof.o: hof.c hof.h
	gcc $(CFLAGS) -lm -c hof.c -o hof.o

k.o: k.c k.h
	gcc $(CFLAGS) -lm -c k.c -o k.o

ui.o: ui.c ui.h
	gcc $(CFLAGS) -lm -c ui.c -o ui.o

clean:
	rm -rf $(OUTPUT) *.0

