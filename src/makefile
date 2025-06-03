CC=gcc
CFLAGS=-I. -g -O3
DEPS = include/*.h
SRC = board.c input.c logic.c main.c render.c tetromino.c
OBJ = $(SRC:.c=.o)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tetris: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	find . -name "*.o" -type f -delete
	rm -f tetris