#include <stdio.h>
#include <stdlib.h>

typedef struct Aresta {	
	int peso;	
} aresta;

typedef struct Grafo {
	int V;
	aresta **matriz;
} grafo;

grafo* cria_grafo(int v);

void add_aresta(grafo *g, int origem, int destino, int peso);

void imprime_grafo(grafo *g);

void clear_grafo(grafo *g);

int bfs(grafo *g, int origem, int destino, int *pai);

int ff(grafo *g, int origem, int destino);
