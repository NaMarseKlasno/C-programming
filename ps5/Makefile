CFLAGS= -std=c11 -Werror -Wall -Wconversion -lm
OUTPUT = adventure
BUILD_DIR := ./build

all: $(OUTPUT)
$(OUTPUT): backpack.c backpack.h command.c command.h container.c container.h game.c game.h item.c item.h parser.c parser.h room.c room.h world.c world.h main.c
	$(CC) $(CFLAGS) backpack.c command.c container.c game.c item.c parser.c room.c world.c main.c -o $(BUILD_DIR)/$(OUTPUT)

backpack.o: backpack.c backpack.h
	gcc $(CFLAGS) -c backpack.c -o $(BUILD_DIR)/backpack.o

command.o: command.c command.h
	gcc $(CFLAGS) -c command.c -o $(BUILD_DIR)/command.o

container.o: container.c container.h
	gcc $(CFLAGS) -c container.c -o $(BUILD_DIR)/container.o

game.o: game.c game.h
	gcc $(CFLAGS) -c game.c -o $(BUILD_DIR)/game.o

item.o: item.c item.h
	gcc $(CFLAGS) -c item.c -o $(BUILD_DIR)/item.o

parser.o: parser.c parser.h
	gcc $(CFLAGS) -c parser.c -o $(BUILD_DIR)/parser.o

room.o: room.c room.h
	gcc $(CFLAGS) -c room.c -o $(BUILD_DIR)/room.o

world.o: world.c world.h
	gcc $(CFLAGS) -c world.c -o $(BUILD_DIR)/world.o

main.o: main.c
	gcc $(CFLAGS) -c main.c -o $(BUILD_DIR)/main.o

clean:
	rm -rf $(BUILD_DIR)/$(OUTPUT) *.0

clean_all:
	rm -rf $(BUILD_DIR)/$(OUTPUT)
	rm -rf $(BUILD_DIR)/backpack.o
	rm -rf $(BUILD_DIR)/command.o *.0
	rm -rf $(BUILD_DIR)/container.o *.0
	rm -rf $(BUILD_DIR)/game.o *.0
	rm -rf $(BUILD_DIR)/item.o *.0
	rm -rf $(BUILD_DIR)/parser.o *.0
	rm -rf $(BUILD_DIR)/room.o *.0
	rm -rf $(BUILD_DIR)/world.o *.0
	rm -rf $(BUILD_DIR)/main.o *.0