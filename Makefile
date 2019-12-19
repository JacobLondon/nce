CC=gcc
TARGET=nce
OBJ_FILES=nce.o
CFLAGS=-std=c11 -O2 -Wall -lncurses

.PHONY: clean

$(TARGET): main.o nce.a
	$(CC) -o $@ $^ $(CFLAGS)

nce.a: $(OBJ_FILES)
	ar rcs $@ $^

main.o: main.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(TARGET) $(OBJ_FILES) *.o *.a