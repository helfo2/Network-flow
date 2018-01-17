#include <stdio.h>
#include <stdlib.h>

#include "fila_bfs.h"

void FFVazia(TFila *Fila) {	
	Fila->Frente = (Apontador)malloc(1*sizeof(TCelula));
	
	Fila->Frente->Item = -1;	

	Fila->Tras = Fila->Frente;
	Fila->Tras->Item = -1;

	Fila->Frente->Prox = NULL;	
}

int Vazia(TFila Fila) {
	return (Fila.Frente == Fila.Tras);
}

void Enfileira(int x, TFila *Fila) {	
	Fila->Tras->Prox = (Apontador)malloc(1*sizeof(TCelula));
	
	Fila->Tras = Fila->Tras->Prox;
	Fila->Tras->Item = x;
	Fila->Tras->Prox = NULL;
}

void Desenfileira(TFila *Fila, int *x){
	if(Vazia(*Fila)){
		printf("Erro: fila vazia!\n");
		return;
	}

	Apontador q = Fila->Frente;
	Fila->Frente = Fila->Frente->Prox;
	*x = Fila->Frente->Item;
	free(q);
}

void Destroi(TFila *Fila){
	Apontador temp = Fila->Frente, aux = NULL;

	while(temp) {
		aux = temp;
		temp = temp->Prox;
		free(aux);
	}

	free(Fila);
}
