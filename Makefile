CC = gcc
CFLAGS = -Wall

SRC = $(wildcard src/*.c)

talc: $(SRC)
	$(CC) -o build/$@ $^ $(CFLAGS)

run: talc
	build/talc
