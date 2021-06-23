CFLAGS= -std=c11 -Werror -Wall -Wconversion -lm
OUTPUT = adventure
BUILD_DIR := ./build

all: $(OUTPUT)
$(OUTPUT): main.c playlist.c playlist.h track.c track.h
	$(CC) $(CFLAGS) main.c playlist.c track.c -o $(BUILD_DIR)/$(OUTPUT)

playlist.o: playlist.c playlist.h
	gcc $(CFLAGS) -c playlist.c -o $(BUILD_DIR)/playlist.o

track.o: track.c track.h
	gcc $(CFLAGS) -c track.c -o $(BUILD_DIR)/track.o

main.o: main.c
	gcc $(CFLAGS) -c main.c -o $(BUILD_DIR)/main.o

clean:
	rm -rf $(BUILD_DIR)/$(OUTPUT) *.0