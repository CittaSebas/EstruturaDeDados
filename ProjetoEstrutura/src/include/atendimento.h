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

typedef struct Celula{
    struct Celula *anterior;
    Registro *registro;
    struct Celula *proximo;
    int modo;
}Celula;

typedef struct {
    Celula *topo;
    int qtde;
}Stack;

EFila *cria_efila(Registro *registro);
Fila *cria_Fila();
Registro* existe_RG(char rg[20]);
void enfileirar(Fila *fila, Stack *stack, char rg[20]);
void desenfileirar(Fila *fila, Stack *stack);
void show(Fila *fila);
Celula *criar_celula(Registro *registro, int m);
Stack *criar_stack();
void push(Stack *stack, Registro *registro, int m);
void pop(Stack *stack, Fila *fila);
char* show_pop(Stack *stack);
void liberar_stack(Stack *stack);
void liberar_fila(Fila *fila);
void atendimento();
void desfazer_enfileirar(Fila *fila);
void desfazer_desenfileirar(Fila *fila, Registro *registro);

#endif