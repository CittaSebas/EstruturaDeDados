#include <stdio.h>
#include <stdlib.h>
#include "../include/util.h"
#include "../include/atendimento.h"


EFila *cria_efila(int valor){
	EFila *efila = malloc(sizeof(EFila));
	efila->proximo = NULL;
	efila->anterior = NULL;
	efila->dados = valor;

	return efila;
}

Fila *cria_Fila(){
	Fila *Fila = malloc(sizeof(Fila));
	Fila->head = NULL;
	Fila->tail = NULL;
	Fila->qtd = 0;

	return Fila;
}

void enfileirar(Fila *fila, int valor){
	EFila *novo = cria_celula(valor);
  if(fila -> qtd == 0){
    fila->head = novo;
  }
  else {
    fila->tail->proximo = novo;
    novo->anterior = fila->tail;
  }
  fila->tail = novo;
  fila->qtd++;
	}

int desenfileirar(Fila *fila){
	if(fila->qtd > 0){
    int valor = fila->head->valor;
    EFila *temp = fila->head;
    fila->head = fila->head->proximo;
    if(fila->qtd == 1){
      fila->tail = NULL;
    }
    else{
      fila->head->anterior = NULL;
    }
    fila->qtd--;
    free(temp);
    return valor;
  }
  printf("Fila vazia!");
  return -1;
}

void show(Fila *fila){
	EFila *atual = fila->head;
  while(atual != NULL){
    printf("%d ", atual->valor);
    atual= atual->proximo;
  }
  printf("\n");
}

void show_invertido(Fila *fila){
	EFila *atual = fila->tail;
  while (atual != NULL){
    printf("%d", atual->valor);
    atual= atual->anterior;
  }
}

int main(void) {
	Fila *qnum1 = cria_Fila();
	
}