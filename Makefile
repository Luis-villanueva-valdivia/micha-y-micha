# Makefile — compila Micha y Micha con un solo comando.
#   make         compila el programa
#   make run     compila y ejecuta
#   make clean   borra el ejecutable y los .o

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Iinclude
SRC     = $(wildcard src/*.c)
OBJ     = $(SRC:.c=.o)
EXE     = micha

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXE)
	./$(EXE)

clean:
	rm -f $(OBJ) $(EXE) $(EXE).exe

.PHONY: all run clean
