#include <stdio.h>

typedef struct Celula *Apontador;

typedef struct Celula {
	int Item;
	Apontador Prox;
} TCelula;

typedef struct {
	Apontador Frente, Tras;
} TFila;

void FFVazia(TFila *Fila);
int Vazia(TFila Fila);
void Enfileira(int x, TFila *Fila);
void Desenfileira(TFila *Fila, int *Item);
void Destroi(TFila *Fila);
