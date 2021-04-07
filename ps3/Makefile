CFLAGS= -std=c11 -Werror -Wall -Wconversion
OUTPUT = game

all: $(OUTPUT)
$(OUTPUT): hof.c hof.h k.c k.h ui.c ui.h main.c
	$(CC) $(CFLAGS) hof.c k.c ui.c main.c -lm -o $(OUTPUT)

hof.o: hof.c hof.h
	gcc $(CFLAGS) -lm -c hof.c -o hof.o

k.o: k.c k.h
	gcc $(CFLAGS) -lm -c k.c -o k.o

ui.o: ui.c ui.h
	gcc $(CFLAGS) -lm -c ui.c -o ui.o

main.o: main.c
	gcc $(CFLAGS) -lm -c main.c -o main.o

clean:
	rm -rf $(OUTPUT) *.0
