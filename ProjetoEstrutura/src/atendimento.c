#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/atendimento.h"
#include "include/cadastro.h"


// Retorna celula do stack recebendo um registro e um modo (m) a depender da operacao que foi feita na fila
Celula *criar_celula(Registro *registro, int m) {
    Celula *celula = malloc(sizeof(Celula));
    celula->anterior = NULL;
    celula->proximo = NULL;
    // Aloca memoria para os dois structs que fazem parte do registro
    celula->registro = malloc(sizeof(Registro));
    strcpy(celula->registro->nome, registro->nome);
    strcpy(celula->registro->rg, registro->rg);
    celula->registro->idade = registro->idade;

    celula->registro->entrada = malloc(sizeof(Data));
    celula->registro->entrada->dia = registro->entrada->dia;
    celula->registro->entrada->mes = registro->entrada->mes;
    celula->registro->entrada->ano = registro->entrada->ano;

    celula->modo = m;
    return celula;
}


// Inicializa o stack
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

// Funcao que retorna uma mensagem com as informacoes da ultima operacao realizada
char* show_pop(Stack *stack) {
    if (stack->qtde == 0) {
        return "Nenhuma acao para desfazer.";
    }
    Celula *topo = stack->topo;
    char *mensagem = malloc(300 * sizeof(char)); 
    // Verifica o modo e muda a string de acordo com a operacao
    if (topo->modo == 1) {
        snprintf(mensagem, 300, "Desfazer acao: Enfileiramento do paciente %s (RG: %s)", 
                 topo->registro->nome, topo->registro->rg);
    } else if (topo->modo == 2) {
        snprintf(mensagem, 300, "Desfazer acao: Desenfileiramento do paciente %s (RG: %s)", 
                 topo->registro->nome, topo->registro->rg);
    } 
    return mensagem; 
}
// Remove a primeira posicao do stack e desfaz a operacao chamando a funcao adequada a depender do modo na celula do stack
void pop(Stack *stack, Fila *fila) {
    // Verifica se o stack nao esta vazio
    if (stack->qtde >= 1) {
        Celula *atual = stack->topo;
        // Verifica o modo salvo no topo do stack
        if (atual->modo == 1) {
            desfazer_enfileirar(fila);
        } else {
            desfazer_desenfileirar(fila, atual->registro);
        }
        stack->topo = stack->topo->anterior;
        free(atual->registro);           
        free(atual);
        stack->qtde--;
    }
    return;
    
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
        printf("RG do desenfileirado: %s \n", atual->dados->nome);
        // Elimina os dados da memoria
        free(atual->dados->entrada);
        free(atual->dados);
        free(atual);
        fila->qtd--; 
    } else {
        printf("Fila vazia!");
    }
}


// Enfileira o paciente desenfileirado, com o registro salvo no stack
void desfazer_desenfileirar(Fila *fila, Registro *registro) {
    if (registro != NULL) {
        EFila *novo = cria_efila(registro);
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

// Funcao para verificar se o rg ja esta enfileirado, retorna 0 para rgs ja enfileirados e 1 para rgs inexistentes na fila
int rg_enfileirado(Fila *fila, char rg[20]){
    EFila *atual = fila->head;
    // Loop while que atravessa a fila e compara os rgs atraves do strcmp
    while(atual != NULL){
        if(strcmp(atual->dados->rg, rg ) == 0){
            return 0;
        }
        atual = atual->proximo;
    }
    return 1;
}

// Enfileira um elemento de fila com o registro resgatado pela funcao existe_RG 
void enfileirar(Fila *fila, Stack *stack, char rg[20]){
    Registro *reg = existe_RG(rg);

    if(reg != NULL && rg_enfileirado(fila,rg) == 1){
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
    else{
        printf("RG ja esta enfileirado ou nao existe na Lista\n");
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

// -------------------------
// Funcoes para liberar a fila e o stack
void liberar_fila(Fila *fila) {
    while (fila->qtd > 0) {  
        if(fila->qtd > 0){
        EFila *temp = fila->head;
        fila->head = fila->head->proximo;
        if(fila->qtd == 1){
            fila->tail = NULL;
        }
        fila->qtd--;
        free(temp->dados->entrada);
        free(temp->dados);
        free(temp);
    }
    }
}

void liberar_stack(Stack *stack) {
    while (stack->qtde > 0) {  
        Celula *atual = stack->topo;
        stack->topo = stack->topo->anterior;
        free(atual->registro);           
        free(atual);
        stack->qtde--;
    }
}
// -------------------------

// Funcao para acessar as funcionalidades do modulo atendimento
void atendimento() {
    // Inicializa a stack e a fila
    Fila *fila = cria_Fila();
    Stack *stack = criar_stack();
    char rg[20];
    int y;
    // Loop do while para acessar as funcionalidades
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
                // Mostra a mensagem contendo as informacoes da ultima operacao
                int z;
                char *mensagem = show_pop(stack);
                printf("%s \n", mensagem);
                // Libera a mensagem para evitar fuga de memoria
                free(mensagem);
                // Verifica se o usuario quer seguir com a operacao
                printf("1. Para confirmar\n");
                scanf("%d", &z);
                if(z == 1){
                    pop(stack,fila);
                    break;
                }
                else{
                    break;
                }
            }
            default: {
            break;
            }

        }
    }
    while (y != 5);
    // Libera a fila e o stack da memoria
    liberar_fila(fila);
    liberar_stack(stack);
}
