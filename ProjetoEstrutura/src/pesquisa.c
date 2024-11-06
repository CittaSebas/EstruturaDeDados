#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/pesquisa.h"
#include "include/cadastro.h"



// Funcao para mostrar a arvore em ordem, com o parametro do modo escolhemos por qual valor
// do registro do paciente deve ser ordenada a busca
void in_ordem(Vertice *raiz, int modo) {
    
    if (raiz != NULL) {
        in_ordem(raiz->esq, modo);
        
        // Verificar o modo e imprimir todos os pacientes da lista ordenados 
        // Mantivemos o dado pelo qual foi ordenado primeiro
        switch (modo) {
            case 1:
                printf("Dia: %d, ", raiz->registro->entrada->dia);
                printf("Mes: %d, ", raiz->registro->entrada->mes);
                printf("Ano: %d, ", raiz->registro->entrada->ano);
                printf("Idade: %d, ", raiz->registro->idade);
                printf("RG: %s, ", raiz->registro->rg);
                printf("Nome: %s \n", raiz->registro->nome);
                break;
            case 2:
                printf("Mes: %d, ", raiz->registro->entrada->mes);
                printf("Dia: %d, ", raiz->registro->entrada->dia);
                printf("Ano: %d, ", raiz->registro->entrada->ano);
                printf("Idade: %d, ", raiz->registro->idade);
                printf("RG: %s, ", raiz->registro->rg);
                printf("Nome: %s\n", raiz->registro->nome);
                break;
            case 3:
                printf("Ano: %d, ", raiz->registro->entrada->ano);
                printf("Mes: %d, ", raiz->registro->entrada->mes);
                printf("Dia: %d, ", raiz->registro->entrada->dia);
                printf("Idade: %d, ", raiz->registro->idade);
                printf("RG: %s, ", raiz->registro->rg);
                printf("Nome: %s\n", raiz->registro->nome);
                break;
            case 4:
                printf("Idade: %d, ", raiz->registro->idade);
                printf("Ano: %d, ", raiz->registro->entrada->ano);
                printf("Mes: %d, ", raiz->registro->entrada->mes);
                printf("Dia: %d, ", raiz->registro->entrada->dia);
                printf("RG: %s, ", raiz->registro->rg);
                printf("Nome: %s\n", raiz->registro->nome);
                break;
            default:
                return;
        }
        
        in_ordem(raiz->dir, modo);
    }
}


//Aloca separadamente a memoria para o vertice, a data e o registro
// e copia os valores do registro passado no parametro para o vertice criado
Vertice* cria_vertice(Registro *registro) {
    Vertice* novo = malloc(sizeof(Vertice));
    novo->registro = malloc(sizeof(Registro));
    novo->registro->entrada = malloc(sizeof(Data));
    novo->registro->idade = registro->idade;
    strcpy(novo->registro->nome, registro->nome);
    strcpy(novo->registro->rg, registro->rg);
    novo->registro->entrada->dia = registro->entrada->dia;
    novo->registro->entrada->mes = registro->entrada->mes;
    novo->registro->entrada->ano = registro->entrada->ano;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = NULL;
    return novo;
}

// Aloca a memoria e inicia os valores da arvore
Arvore *cria_arvore(){
	Arvore* arvore = malloc(sizeof(Arvore));
	arvore->raiz = NULL;
	arvore->qtde = 0;

	return arvore;
}
// Bloco de funcoes que inserem os registros ordenados por determinados valores (dia,ano,mes ou idade)
// Sao funcoes padrao de insercao em arvore binaria
void inserir_por_dia(Arvore *arvore, Registro *registro) {
    Vertice *novo = cria_vertice(registro);
    Vertice *atual = arvore->raiz;
    Vertice *pai = NULL;

    while (atual != NULL) {
        pai = atual;
        if (registro->entrada->dia < atual->registro->entrada->dia) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    novo->pai = pai;
    if (pai == NULL) { 
        arvore->raiz = novo;
    } else if (registro->entrada->dia < pai->registro->entrada->dia) {
        pai->esq = novo;
    } else {
        pai->dir = novo;
    }
    arvore->qtde++;
}

void inserir_por_mes(Arvore *arvore, Registro *registro) {
    Vertice *novo = cria_vertice(registro);
    Vertice *atual = arvore->raiz;
    Vertice *pai = NULL;

    while (atual != NULL) {
        pai = atual;
        if (registro->entrada->mes < atual->registro->entrada->mes) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    novo->pai = pai;
    if (pai == NULL) {
        arvore->raiz = novo;
    } else if (registro->entrada->mes < pai->registro->entrada->mes) {
        pai->esq = novo;
    } else {
        pai->dir = novo;
    }
    arvore->qtde++;
}

void inserir_por_ano(Arvore *arvore, Registro *registro) {
    Vertice *novo = cria_vertice(registro);
    Vertice *atual = arvore->raiz;
    Vertice *pai = NULL;

    while (atual != NULL) {
        pai = atual;
        if (registro->entrada->ano < atual->registro->entrada->ano) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    novo->pai = pai;
    if (pai == NULL) {
        arvore->raiz = novo;
    } else if (registro->entrada->ano < pai->registro->entrada->ano) {
        pai->esq = novo;
    } else {
        pai->dir = novo;
    }
    arvore->qtde++;
}

void inserir_por_idade(Arvore *arvore, Registro *registro) {
    Vertice *novo = cria_vertice(registro);
    Vertice *atual = arvore->raiz;
    Vertice *pai = NULL;

    while (atual != NULL) {
        pai = atual;
        if (registro->idade < atual->registro->idade) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    novo->pai = pai;
    if (pai == NULL) {
        arvore->raiz = novo;
    } else if (registro->idade < pai->registro->idade) {
        pai->esq = novo;
    } else {
        pai->dir = novo;
    }
    arvore->qtde++;
}
//

// Funcao de inserir que chama as funcoes de inserir com o modo estabelecido
// iterando pela lista carregada ate o seu fim (por isso usamos Elemento de lista)
void inserir(Arvore *arvore, int modo) {
    Lista *l = malloc(sizeof(Lista));
    carregarLista(l);

    ELista *elemento_lista = l->primeiro; 
    while (elemento_lista != NULL) {
        Registro *registro = elemento_lista->dados;

        switch (modo) {
            case 1:
                inserir_por_dia(arvore, registro);
                break;
            case 2:
                inserir_por_mes(arvore, registro);
                break;
            case 3:
                inserir_por_ano(arvore, registro);
                break;
            case 4:
                inserir_por_idade(arvore, registro);
                break;
            default:
                printf("Modo de inserção inválido.\n");
                break;
        }

        elemento_lista = elemento_lista->proximo;
    }
    //Libera a memoria da lista
    free(l); 
}

// Libera a arvore, como eh usada apenas para mostrar os valores nao eh necessario mante-la
void liberar_arvore(Vertice* vertice) {
    if (vertice != NULL) {
        liberar_arvore(vertice->esq);
        liberar_arvore(vertice->dir);
        free(vertice);
    }
}

// Funcao para o uso desse modulo, para ser chamado no main
void pesquisar_dados(){
    int m;

    do {
        Arvore *arvore = cria_arvore();
        printf("Os dados devem ser ordenados por qual informacao?\n");
        printf("1. Dia de entrada\n");
        printf("2. Mes de entrada\n");
        printf("3. Ano de entrada\n");
        printf("4. Idade do paciente\n");
        printf("5. Sair da funcao\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &m);

        if (m >= 1 && m <= 4) {
            inserir(arvore, m);
            in_ordem(arvore->raiz, m);
            liberar_arvore(arvore->raiz);
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }
        
    } while (m!= 5);

}