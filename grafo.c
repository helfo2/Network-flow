#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "fila_bfs.h"
#include "grafo.h"

#define min(x, y) (((x) < (y)) ? (x) : (y))

grafo* cria_grafo(int v) { // cria grafo com v vertices
	grafo *g = (grafo*)malloc(sizeof(grafo));

	g->V = v;
	g->matriz = (aresta**)malloc(v * sizeof(aresta*));

	int i, j;
	for(i = 0; i < v; i++)
		g->matriz[i] = (aresta*)malloc(v * sizeof(aresta));

	for(i = 0; i < v; i++) {
		for(j = 0; j < v; j++) {
			g->matriz[i][j].peso = 0;			
		}
	}


	return g;
}

void add_aresta(grafo *g, int origem, int destino, int peso) {
	// como a cidade e um grafo unidirecionado	
	g->matriz[origem][destino].peso = peso;
}

void imprime_grafo(grafo *g) {
	int i, j;
	
	for(i = 0; i < g->V; i++) {
		for(j = 0; j < g->V; j++) {
			printf("grafo[%d][%d].peso = %d\n", i, j, g->matriz[i][j].peso);			
		}
		printf("\n");
	}
}

void clear_grafo(grafo *g) {
	int i;

	for(i = 0; i < g->V; i++) {
		free(g->matriz[i]);
	}

	free(g->matriz);
	free(g);
}

int bfs(grafo *g, int origem, int destino, int *pai) {
	int i, v, u, qnt_v = g->V;
	int visitados[qnt_v]; // vetor booleano que armazena vertices visitados

	for(i = 0; i < qnt_v; i++) 
		visitados[i] = 0;

	if(destino >= qnt_v) {
		printf("Erro: informe um destino dentro dos limites do grafo.\n");
		return -1;
	}

	//pilha *p = (pilha*)malloc(sizeof(pilha)); p->fundo = NULL; p->topo = NULL; p->tam = -1; 
	TFila *p = (TFila*)malloc(1*sizeof(TFila)); p->Frente = p->Tras = NULL;
	//init_pilha(p);	
	FFVazia(p);

	//push(origem, p);	
	Enfileira(origem, p);

	visitados[origem] = 1;
	pai[origem] = -1;
	
	//while(!pilha_vazia(*p)) {
		//pop(p, &u);
	while(!Vazia(*p)) {
		Desenfileira(p, &u);

		for(v = 0; v < qnt_v; v++) {			
			if(visitados[v] == 0 && g->matriz[u][v].peso > 0) {				
				//push(v, p);
				Enfileira(v, p);
				pai[v] = u;
				visitados[v] = 1;
			}
		}
	}
	
	//destroi_pilha(p);
	Destroi(p);

	return (visitados[destino] == 1);	
}

int ff(grafo *g, int origem, int destino) {
	int u, v, qnt_v = g->V;

	grafo *g_residual = cria_grafo(qnt_v);

	for(u = 0; u < qnt_v; u++) {
		for(v = 0; v < qnt_v; v++) {
			g_residual->matriz[u][v] = g->matriz[u][v];
		}
	}

	int *pais = (int*)malloc(qnt_v * sizeof(int));
	for(int i = 0; i < qnt_v; i++) pais[i] = -1;

	int fluxo_max = 0;

	while(bfs(g_residual, origem, destino, pais)) {
		int fluxo = INT_MAX;

		for(v = destino; v != origem; v = pais[v]) {
			u = pais[v];
			fluxo = min(fluxo, g_residual->matriz[u][v].peso);
		}

		for(v = destino; v != origem; v = pais[v]) {
			u = pais[v];

			g_residual->matriz[u][v].peso -= fluxo;
			g_residual->matriz[v][u].peso += fluxo;			
		}

		fluxo_max += fluxo;
	}

	clear_grafo(g_residual);
	free(pais);

	return fluxo_max;
}
