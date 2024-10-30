#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H
#include "cadastro.h"

typedef struct EFila {
	Registro *dados;
	struct EFila *proximo;
} EFila;

typedef struct {
	EFila *head;
	EFila *tail;
	int qtd;
} Fila;

EFila *cria_efila(Registro *registro);
Fila *cria_Fila();
Registro* existe_RG(char rg[20]);
void enfileirar(Fila *fila, char rg[20]);
void desenfileirar(Fila *fila);
void show(Fila *fila);
#endif