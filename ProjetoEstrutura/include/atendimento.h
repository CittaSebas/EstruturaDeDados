#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H
#include "util.h"

typedef struct Celula {
	Registro *dados;
	struct Celula *proximo;
	struct Celula *anterior;
} EFila;

typedef struct {
	EFila *head;
	EFila *tail;
	int qtd;
} Fila;


#endif