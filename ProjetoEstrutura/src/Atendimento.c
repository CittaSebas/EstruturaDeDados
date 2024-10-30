#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/atendimento.h"
#include "include/cadastro.h"


// ---- Inicializacao do elemento da fila ou da fila em si
EFila *cria_efila(Registro *registro){
    EFila *efila = malloc(sizeof(EFila));
    efila->proximo = NULL;
    efila->dados = registro;

    return efila;
}

Fila *cria_Fila(){
    Fila *Fila = malloc(sizeof(Fila));
    Fila->head = NULL;
    Fila->tail = NULL;
    Fila->qtd = 0;

    return Fila;
}

// ----

// Recebe um RG e verifica se ele existe na lista que eh inicializada, carregada e percorrida 
Registro* existe_RG(char rg[20]){
    Lista *l = malloc(sizeof(Lista));
    carregarLista(l);

    ELista *atual = l->primeiro;
    while (atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("RG não encontrado\n");      
        return NULL;
    } else {
        // Retorna um ponteiro para o registro do paciente
        return atual->dados;
    }
}

// Enfileira um elemento de fila com o registro resgatado pela funcao existe_RG 
void enfileirar(Fila *fila, char rg[20]){
    if(existe_RG(rg) != NULL){
        Registro *reg = existe_RG(rg);
        EFila *novo = cria_efila(reg);
        if(fila -> qtd == 0){
            fila->head = novo;
        }
        else {
            fila->tail->proximo = novo;
        }
        fila->tail = novo;
        fila->qtd++;
        }
}

// Tira um elemento da fila e mostra as informacoes do paciente removido
void desenfileirar(Fila *fila){
    if(fila->qtd > 0){
        EFila *temp = fila->head;
        fila->head = fila->head->proximo;
        if(fila->qtd == 1){
        fila->tail = NULL;
        }

        fila->qtd--;
        printf("Idade do desenfileirado: %d\n", temp->dados->idade);
        printf("Nome do desenfileirado: %s \n",temp->dados->nome);
        free(temp);
    }
    else{
    printf("Fila vazia!");
    }
}

// Atravessa a fila e mostra informacoes basicas dos elementos da fila
void show(Fila *fila){
    EFila *atual = fila->head;
    printf("===================\n");
    printf("       Fila\n");
    while (atual != NULL) {
        printf("RG: %s, ", atual->dados->rg);
        printf("Nome: %s \n", atual->dados->nome);
        atual = atual->proximo;
    }
    printf("===================\n");
    printf("\n");
}
