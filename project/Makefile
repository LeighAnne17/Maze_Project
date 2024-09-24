# Makefile
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -Iinc   # Added -Iinc to include the inc directory
LDFLAGS = -lSDL2 -lm
SRC = src/main.c src/raycasting.c src/map.c
OBJ = $(SRC:.c=.o)
EXEC = build/raycasting

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: clean

