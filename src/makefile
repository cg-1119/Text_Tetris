CC=clang
CFLAGS=-I. -g -O3
DEPS = include/*.h
SRC = config.c table.c input.c logic.c main.c render.c tetromino.c point.c
OBJ = $(SRC:.c=.o)

ifeq ($(OS),Windows_NT)
  TARGET  = tetris.exe
  RM      = del /F /Q
  EXE     = .exe
  LDFLAGS = -lws2_32 -Wl,/INCREMENTAL:NO -Wl,/DEBUG:NONE
else
  TARGET  = tetris
  RM      = rm -f
  EXE     =
  LDFLAGS =
endif

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	$(RM) *.o
	$(RM) tetris$(EXE)