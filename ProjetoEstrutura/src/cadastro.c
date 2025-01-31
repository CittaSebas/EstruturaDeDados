#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "include/cadastro.h"


// Inicializacao da Lista
Lista *criar_lista() {
    Lista *lista = malloc(sizeof(Lista));
    lista->primeiro = NULL;
    lista->qtde = 0;
    return lista;
}
// Inicializacao do elemento da lista
ELista *criar_ELista(Registro *registro) {  
    ELista *eLista = malloc(sizeof(ELista));
    eLista->proximo = NULL;
    eLista->dados = registro;  
    return eLista;
}


int salvarLista(Lista *lista) {
    FILE *f = fopen("lista.bin", "wb");
    if (f == NULL) {
        return -1; 
    }
    // Salvando a quantidade de elementos salvos
    fwrite(&lista->qtde, sizeof(int), 1, f);

    // Travessia padrao de lista encadeada
    ELista *atual = lista->primeiro;
    while (atual != NULL) {
        // Escreve os dados no arquivo com os tamanhos definidos para cada struct
        fwrite(atual->dados, sizeof(Registro), 1, f);
        fwrite(atual->dados->entrada, sizeof(Data), 1, f);
        atual = atual->proximo;
    }

    fclose(f);
    return 0; 
}


int carregarLista(Lista *lista) {
    //Abre o arquivo em binario e retorna se estiver vazio
    FILE *f = fopen("lista.bin", "rb");
    if (f == NULL) {
        return -1; 
    }
    // Le a quantidade de registros salvos no arquivo
    fread(&lista->qtde, sizeof(int), 1, f);
    lista->primeiro = NULL;

    for (int i = 0; i < lista->qtde; i++) {
        // Alocacao de memoria para data e registro  
        // !! Por algum motivo nao funcionava alocando a memoria da data direto no registro !!
        // e tivemos que criar uma variavel (data) adicional
        Registro *registro = malloc(sizeof(Registro));
        Data *data = malloc(sizeof(Data));
        //Lendo as informacoes do arquivo em tamanho de data e registro
        fread(registro, sizeof(Registro), 1, f);
        fread(data, sizeof(Data), 1, f);

        ELista *novo = criar_ELista(registro);
        //Salvando a data manualmente 
        novo->dados->entrada = malloc(sizeof(Data));
        novo->dados->entrada->dia = data->dia;
        novo->dados->entrada->mes = data->mes;
        novo->dados->entrada->ano = data->ano;
        // Para manter a ordem de insercao percorremos a lista e inserimos o paciente no final da lista
        if (lista->primeiro == NULL) {  
            lista->primeiro = novo;  
        } else {
            
            ELista *atual = lista->primeiro;
            while (atual->proximo != NULL) {
                atual = atual->proximo;
            }
            atual->proximo = novo;  
        }
        //Liberando a variavel adicional
        free(data);  
    }
    
    fclose(f);
    return 0; 
}






// Funcoes
void cadastrar(Lista *lista){
    // Criacao e alocao de memoria para as variaveis a serem salvos no registro e depois na lista
    char nome[100], rg[20];
    int idade, dia, mes, ano;
    Registro *registro = malloc(sizeof(Registro));
    registro->entrada = malloc(sizeof(Data));
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Resgatando a data com time.h
    // dia = tm.tm_mday;
    // mes = tm.tm_mon + 1;
    // ano = tm.tm_year + 1900;
    printf("Digite o Dia:\n");  
    scanf("%d",&dia);
    printf("Digite o Mes:\n");  
    scanf("%d",&mes);
    printf("Digite el Ano:\n");  
    scanf("%d",&ano);
     // Pedindo as informacoes para o usuario
    getchar();
    printf("Digite o Nome:\n");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;
    printf("Digite a Idade:\n");  
    scanf("%d",&idade);
    printf("Digite o RG:\n");
    scanf("%s",rg);
    // Preenchendo os campos do registro
    registro->entrada->dia = dia; 
    registro->entrada->mes = mes; 
    registro->entrada->ano = ano; 
    registro->idade = idade;
    strcpy(registro->nome, nome);  
    strcpy(registro->rg, rg);
    // Criando o elemento da lista e inserindo-o no comeco da lista encadeada
    ELista *novo = criar_ELista(registro);
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;
    lista->qtde++;

}




// Funcao de remocao padrao de lista encadeada 
void remover(Lista *lista, char rg[20]){
    //Criacao de dois elementos para atravessar a lista e setar corretamente os ponteiros dos 
    // elementos a frente ou atras do elemento a ser removido
    ELista *atual = lista->primeiro;
    ELista *anterior = NULL;
    // Comparacao do rg informado com os existentes na lista
    while (atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
        anterior = atual;
        atual = atual->proximo;
  }
    // caso nao existente
    if (atual == NULL) {
        printf("RG não encontrado\n");      
        return;
  }
    // caso seja o primeiro
    if (anterior == NULL) {
        lista->primeiro = atual->proximo;
  } 
    // caso seja no meio ou no fim
    else {
        anterior->proximo = atual->proximo;
  }
    // Liberamos o elemento atual
    free(atual);
    lista->qtde--;
}

// O proximo bloco de funcoes atravessam a lista buscando ou mostrando informacoes contidas
// todos iteram sobre a lista usando o ponteiro do proximo dentro do ELista ate encontrar 
// a informacao ou chegar no final da lista (atual == NULL)

// Funcao que mostra informacoes limitadas sobre todos os pacientes contidos na lista
void mostrar_lista(Lista *lista){
    ELista *atual = lista->primeiro;
    printf("===================\n");
    printf("    Pacientes\n");
    while (atual != NULL) {
    printf("RG: %s, ", atual->dados->rg);
    printf("Nome: %s \n", atual->dados->nome);
    atual = atual->proximo;
  }
    printf("===================\n");
    printf("\n");
}

// Funcao recebe um RG e mostra todas as informacoes do paciente, caso o RG existir
void mostrar_paciente(Lista *lista, char rg[20]){
    ELista *atual = lista->primeiro;
    while (atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
        atual = atual->proximo;
    }
    if (atual == NULL) {
      printf("RG não encontrado\n");      
      return;
    } 
  else {
      printf("Nome: %s\n", atual->dados->nome);
      printf("RG: %s\n", atual->dados->rg);
      printf("Idade: %d\n", atual->dados->idade);
      printf("Data de entrada: %d / %d / %d\n", atual->dados->entrada->dia, atual->dados->entrada->mes, atual->dados->entrada->ano);
  }
}

// Funcao que recebe um RG e pede para o usuario escolher qual campo do registro do paciente 
// deve ser alterado
void alterar(Lista *lista, char rg[20]){
    // Variavel para selecao 
    int x;

    ELista *atual = lista->primeiro;
    while (atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
      atual = atual->proximo;
    }

    if (atual == NULL) {
      printf("RG não encontrado\n");
      return;
    }

    // Decidimos fazer um do while para o usuario poder fazer varias alteracoes de uma vez
    do {
        printf("Escolha o que deseja alterar:\n");
        printf("1. Para Nome\n");
        printf("2. Para RG\n");
        printf("3. Para Idade\n");
        printf("4. Para sair\n");
        scanf("%d", &x);
        // Todos os cases pedem uma informacao ao usuario e trocam a informacao contida no
        // registro encontrado pelo RG
        switch (x) {
            case 1: {
                char nome[100];
                printf("Digite o novo nome: \n");
                getchar();
                fgets(nome, sizeof(nome), stdin);
                strcpy(atual->dados->nome, nome);
                break;
          }
            case 2: {
                char rgn[20];
                printf("Digite o novo RG: ");
                scanf("%s", rgn);
                strcpy(atual->dados->rg, rgn);
                break;
            }
            case 3: {
                int  idadetemp;
                printf("Digite a nova idade: ");
                scanf("%d", &idadetemp);
                atual->dados->idade = idadetemp;
                break;
            }
            case 4: {
                printf("Saindo...\n");
                break;
            }
            default: {
                printf("Opção inválida. Tente novamente.\n");
                break;
            }
      }
  } while (x != 4);

}

// Funcao para ser usada na main com todas as funcionalidades do modulo de cadastro
int lista(void){
  char rg[20];
  int y;
  // Cria lista e carrega as informacoes do arquivo 
  Lista *lista = criar_lista();
  carregarLista(lista);
  // Loop do while para o usuario acessar as funcionalidades
  do {
    printf("BOA TARDE\n");
    printf("Escolha o que deseja fazer: \n");
    printf("1. Cadastrar usuario\n");
    printf("2. Consultar Paciente\n");
    printf("3. Consultar Lista de Pacientes\n");
    printf("4. Alterar Info do Paciente\n");
    printf("5. Remover cadastro do Paciente\n");
    printf("6. Salvar\n");
    printf("7. Encerrar programa\n");
    scanf("%d", &y);
    switch (y) {
        case 1: {
            cadastrar(lista);
            break;
        }
        case 2: {
            printf("RG do Paciente qual deseja consultar\n");
            scanf("%s",rg);
            mostrar_paciente(lista,rg);
            break;
        }
        case 3: {
          mostrar_lista(lista);
            break;
        }
        case 4: {
            printf("RG do Paciente a ser alterado:\n");
            scanf("%s",rg);
            alterar(lista,rg);
            break;
        }
        case 5: {
            printf("RG do Paciente a ser removido:\n");
            scanf("%s",rg);
            remover(lista,rg);
            break;
        }
        case 6: {
            printf("Salvando....\n");
            salvarLista(lista);
            break;
        }
        case 7: {
            printf("Saindo...\n");
            return -1;
        }
        default: {
            printf("Opção inválida. Tente novamente.\n");
            break;
        }
    }

  } while (y != 7);
  liberar_lista(lista);
  return 0;
}

// Funcao para liberar a lista usada pela funcao lista() 
void liberar_lista(Lista *lista){
    ELista *atual = lista->primeiro;
    while(lista->qtde > 0){
        ELista *temp = atual;
        ELista *atual = atual->proximo;
        lista->qtde--;
        free(temp->dados->entrada);
        free(temp->dados);
        free(temp);
    }
    free(lista);
}

