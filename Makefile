CC=gcc
TARGET=nce
FILES=main.c
LINK=-lncurses
CFLAGS=-Wall

.PHONY: all clean

all:
	$(CC) -o $(TARGET) $(FILES) $(LINK) $(CFLAGS)
clean:
	rm $(TARGET)