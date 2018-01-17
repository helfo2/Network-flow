#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "grafo.h"

#define max(x, y) (((x) > (y)) ? (x) : (y))

typedef struct cliente {
	int id;
	int visitado;
} cliente;

void le_ciclofaixas(grafo* cidade, int ciclofaixas);
int* le_franquias(int F, int *franquias, int *maximo_franquias);
void le_clientes(int C, cliente *clientes);

int main(void) {
	int V = 0, E = 0, F = 0, C = 0; // entrada
	int *franquias = NULL;
	cliente* clientes = NULL;
	int i = 0, j = 0; // contadores	
	grafo* cidade = NULL; // grafo

	int *maior_qnt_ciclistas = NULL, maximo_franquias = 0;
	
	scanf("%d %d %d %d", &V, &E, &F, &C);	
	
	franquias = (int*)malloc(F * sizeof(int)); 
	for(i = 0; i < F; i++)
		franquias[i] = -1; 
	
	clientes = (cliente*)malloc(C * sizeof(cliente)); 
	for(j = 0; j < C; j++) { 
		clientes[j].id = -1;
		clientes[j].visitado = -1;		
	}

	cidade = cria_grafo(V); // aloca memoria para os vertices informados, considerando que o grafo e direcionado
	
	le_ciclofaixas(cidade, E); // adiciona as arestas ao grafo
	maior_qnt_ciclistas = le_franquias(F, franquias, &maximo_franquias); // seta as franquias no grafo, para propositos de armazenamento
	le_clientes(C, clientes); // seta os clientes no grafo, para propositos de armazenamento

	int qnt_ciclistas = 0;
	for(i = 0; i < F; i++) { // para cada franquia, de onde saimos		
		for(j = 0; j < C; j++) { // visita-se cada cliente
			qnt_ciclistas = ff(cidade, franquias[i], clientes[j].id); // ford-fulkerson			

			if(clientes[j].visitado != 1 && qnt_ciclistas > maior_qnt_ciclistas[franquias[i]]) {// maximiza os ciclistas por hora
				maior_qnt_ciclistas[franquias[i]] = qnt_ciclistas;
				clientes[j].visitado = 1;
			}
		}
	}
	
	int qnt_total = 0;
	for(j = 0; j <= maximo_franquias; j++)		
		qnt_total += maior_qnt_ciclistas[j];

	printf("%d\n", qnt_total);

	clear_grafo(cidade);
	
	free(franquias);
	free(clientes);
	free(maior_qnt_ciclistas);
	
	return 0;
}

void le_ciclofaixas(grafo* cidade, int ciclofaixas) {
	int u = 0, v = 0, m = 0;

	while(ciclofaixas-- > 0) {
		scanf("%d %d %d", &u, &v, &m);
		add_aresta(cidade, u, v, m);
	}
}

int* le_franquias(int F, int *franquias, int *maximo_franquias) {
	int f = 0, cont_franquias = 0, max_franquias = 0;
	int *maior_qnt_ciclistas = NULL;

	while(F-- > 0) {
		scanf("%d", &f);		
		
		if(f > max_franquias) max_franquias = f;

		franquias[cont_franquias] = f; 
		cont_franquias++;
	}	

	maior_qnt_ciclistas = (int*)malloc((max_franquias + 1) * sizeof(int));
	for(cont_franquias = 0; cont_franquias <= max_franquias; cont_franquias++) {
		maior_qnt_ciclistas[cont_franquias] = 0;
	}

	*maximo_franquias = max_franquias;
	return maior_qnt_ciclistas;
}

void le_clientes(int C, cliente *clientes) {
	int c = 0, cont_clientes = 0;

	while(C-- > 0) {		
		scanf("%d", &c);		

		clientes[cont_clientes].id = c;
		cont_clientes++;
	}
}
