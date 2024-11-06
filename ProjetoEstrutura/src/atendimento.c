#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/atendimento.h"
#include "include/cadastro.h"

Celula *criar_celula(Registro *registro, int m){
    Celula *celula = malloc(sizeof(Celula));
    celula->anterior = NULL;
    celula ->proximo = NULL;
    celula->registro = registro;
    celula->modo = m;
    return celula;
}
Stack *criar_stack(){
    Stack *stack = malloc(sizeof(Stack));
    stack->topo = NULL;
    stack->qtde = 0;
    return stack;
}
void push(Stack *stack, Registro *registro, int m){
    Celula *novo = criar_celula(registro, m);
    if(stack->qtde > 0){
        novo->anterior = stack->topo;
        stack->topo->proximo = novo;
    }
    stack->topo = novo;
    stack->qtde++;
}

char* show_pop(Stack *stack) {
    if (stack->qtde == 0) {
        return "Nenhuma ação para desfazer.";
    }
    Celula *topo = stack->topo;
    char *mensagem = malloc(300 * sizeof(char)); 

    if (topo->modo == 1) {
        snprintf(mensagem, 300, "Desfazer acao: Enfileiramento do paciente %s (RG: %s)", 
                 topo->registro->nome, topo->registro->rg);
    } else if (topo->modo == 2) {
        snprintf(mensagem, 300, "Desfazer acao: Desenfileiramento do paciente %s (RG: %s)", 
                 topo->registro->nome, topo->registro->rg);
    } else {
        snprintf(mensagem, 300, "Ação desconhecida para desfazer.");
    }

    return mensagem; 
}

void pop(Stack *stack, Fila *fila){
    if(stack->qtde == 0){
        printf("Stack underflow\n");
    }
    Celula *atual = stack->topo;
    if(stack->qtde >= 1){
        if(atual->modo == 1){
            desfazer_enfileirar(fila);
        }
        else{
            desfazer_desenfileirar(fila,atual->registro);
        }
        }
        stack->topo = stack->topo->anterior;
        free(atual);
    stack->qtde--;
    
}


// Elimina o ultimo elemento da fila, para desfazer um enfileiramento indesejado 
// Percorre ate o final da final da fila e seta os ponteiros de acordo
void desfazer_enfileirar(Fila *fila){
    if (fila->qtd > 0) {
        EFila *atual = fila->head;
        EFila *temp = NULL;
        if (fila->qtd == 1) {
            fila->head = NULL; 
            fila->tail = NULL; 

        } else {
            while (atual->proximo != NULL) {
                temp = atual;
                atual = atual->proximo;
            }
            fila->tail = temp;
            fila->tail->proximo = NULL; 
        }
        printf("Idade do desenfileirado: %d\n", atual->dados->idade);
        printf("Nome do desenfileirado: %s \n", atual->dados->nome);
        free(atual);
        fila->qtd--; 
    } else {
        printf("Fila vazia!");
    }
}



void desfazer_desenfileirar(Fila *fila, Registro *registro) {
    if (registro == NULL) {
        printf("Nenhuma ação de desenfileiramento para desfazer!\n");
        return;
    }
    char rg[20];
    strcpy(rg, registro->rg);
    Registro *reg = existe_RG(rg);

    if (registro != NULL) {
        EFila *novo = cria_efila(reg);
        novo->proximo = fila->head; 
        fila->head = novo;
        if (fila->tail == NULL) {
            fila->tail = novo;
        }
        fila->qtd++;  
    } 
}



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
    liberar_lista(l);
}

// Enfileira um elemento de fila com o registro resgatado pela funcao existe_RG 
void enfileirar(Fila *fila, Stack *stack, char rg[20]){
    Registro *reg = existe_RG(rg);
    if(reg != NULL){
        EFila *novo = cria_efila(reg);
        if(fila -> qtd == 0){
            fila->head = novo;
        }
        else {
            fila->tail->proximo = novo;
        }
        push(stack,novo->dados,1);
        fila->tail = novo;
        fila->qtd++;
        }
}

// Tira um elemento da fila e mostra as informacoes do paciente removido
void desenfileirar(Fila *fila, Stack *stack){
    if(fila->qtd > 0){
        EFila *temp = fila->head;
        push(stack, temp->dados, 2);
        
        fila->head = fila->head->proximo;
        if(fila->qtd == 1){
        fila->tail = NULL;
        }

        fila->qtd--;
        printf("Idade do desenfileirado: %d\n", temp->dados->idade);
        printf("Nome do desenfileirado: %s \n",temp->dados->nome);
        free(temp->dados->entrada);
        free(temp->dados);
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

void liberar_fila(Fila *fila) {
    while (fila->qtd > 0) {  
        desenfileirar(fila, NULL);  
    }
    free(fila);
}

void liberar_stack(Stack *stack) {
    while (stack->qtde > 0) {  
        pop(stack, NULL);  
    }
    free(stack);
}

void atendimento() {
    Fila *fila = cria_Fila();
    Stack *stack = criar_stack();
    char rg[20];
    int y;
    do {
        printf("BOA TARDE\n");
        printf("Escolha o que deseja fazer: \n");
        printf("1. Registrar Paciente na Fila\n");
        printf("2. Atualizar Fila\n");
        printf("3. Consultar Fila\n");
        printf("4. Para desfazer a ultima Acao\n");
        printf("5. Para encerrar o Programa\n");
        scanf("%d", &y);
        switch (y) {
            case 1: {
                printf("RG do Paciente a ser atendido: \n");
                scanf("%s",rg);
                enfileirar(fila,stack, rg);
                break;
            }
            case 2: {
                printf("Atualizar Fila\n");
                desenfileirar(fila, stack);
                break;
            }
            case 3: {
            show(fila);
                break;
            }
            case 4: {
                int z;
                char *mensagem = show_pop(stack);
                printf("%s \n", mensagem);
                free(mensagem);
                printf("1. Para confirmar\n");
                scanf("%d", &z);
                if(z == 1){
                    pop(stack,fila);
                }
            }
            default: {
            break;
            }

        }
    }
    while (y != 5);
    liberar_fila(fila);
    liberar_stack(stack);
}
