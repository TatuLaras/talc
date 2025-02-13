CC = gcc
CFLAGS = -Wall -ggdb -lm
CFLAGS_RELEASE = -Wall -lm

SRC = $(wildcard src/*.c)

all: setup debug

setup:
	@mkdir -p build

debug: $(SRC)
	echo "DEBUG"
	$(CC) -o build/$@ $^ $(CFLAGS)

release: $(SRC)
	echo "RELEASE"
	$(CC) -o build/$@ $^ $(CFLAGS_RELEASE)

run: all
	build/debug


