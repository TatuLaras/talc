CC = gcc
CFLAGS = -Wall -ggdb -lm
CFLAGS_RELEASE = -Wall

SRC = $(wildcard src/*.c)

debug: $(SRC)
	echo "DEBUG"
	$(CC) -o build/$@ $^ $(CFLAGS)

release: $(SRC)
	echo "RELEASE"
	$(CC) -o build/$@ $^ $(CFLAGS_RELEASE)

run: debug
	build/debug


