CC=gcc
CFLAGS= -Wall -Wextra -Werror -std=c99 -pedantic
DEPS = grafo.h fila_bfs.h
OBJ = grafo.o fila_bfs.o tp1.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tp1: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm *.o	
