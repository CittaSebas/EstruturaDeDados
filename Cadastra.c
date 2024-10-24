#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Structs para organizar dados
typedef struct Data{
  int dia;
  int mes;
  int ano;
} Data;

typedef struct Registro{
  char nome[100];
  char rg[20];
  int idade;
  Data *entrada;
} Registro;

// Structs padroes para lista dinamica
typedef struct ELista {
  struct ELista *proximo;
  Registro *dados;
} ELista;

typedef struct {
  ELista *primeiro;
  int qtde;
} Lista;

// Inicializacao da Lista
Lista *criar_lista() {
  Lista *lista = malloc(sizeof(Lista));
  lista->primeiro = NULL;
  lista->qtde = 0;
  return lista;
}

ELista *criar_ELista(Registro *registro) {  
    ELista *eLista = malloc(sizeof(ELista));
    eLista->proximo = NULL;
    eLista->dados = registro;  
    return eLista;
}

// Funcoes
void cadastrar(Lista *lista){
    // variaveis
    char nome[100], rg[20];
    int idade, dia, mes, ano;
    Registro *registro = malloc(sizeof(Registro));
    registro->entrada = malloc(sizeof(Data));
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // infos
    dia = tm.tm_mday;
    mes = tm.tm_mon + 1;
    ano = tm.tm_year + 1900;
    printf("Digite o Nome:\n");
    scanf("%s",nome);
    printf("Digite a Idade:\n");  
    scanf("%d",&idade);
    printf("Digite o RG:\n");
    scanf("%s",rg);

    registro->entrada->dia = dia; 
    registro->entrada->mes = mes; 
    registro->entrada->ano = ano; 
    registro->idade = idade;
    strcpy(registro->nome, nome);  
    strcpy(registro->rg, rg);
    ELista *novo = criar_ELista(registro);
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;
    lista->qtde++;

}



void remover(Lista *lista, char rg[20]){
  ELista *atual = lista->primeiro;
  ELista *anterior = NULL;
  while (atual != NULL && atual->dados->rg != rg) {
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

  free(atual);
  lista->qtde--;
}

void mostrar_lista(Lista *lista){
  ELista *atual = lista->primeiro;
  while (atual != NULL) {
    printf("%s ", atual->dados->rg);
    printf("%s ", atual->dados->nome);
    atual = atual->proximo;
  }
  printf("\n");
}

void mostrar_paciente(Lista *lista, char rg[20]){
  ELista *atual = lista->primeiro;
  while (atual != NULL && atual->dados->rg != rg) {
      atual = atual->proximo;
  }
  // caso nao existente
  if (atual == NULL) {
      printf("RG não encontrado\n");      
      return;
  }

  else{
    printf("Nome: %s", atual->dados->nome);
    printf("RG: %s", atual->dados->rg);
    printf("Idade: %d", atual->dados->idade);
    printf("Data de Registro: %d / %d / %d", atual->dados->entrada->dia, atual->dados->entrada->mes, atual->dados->entrada->ano);
  }
}

void alterar(Lista *lista, char rg[20]){
  char nome[100];
  char rgn[20];
  int x,idadetemp;

  ELista *atual = lista->primeiro;
  while (atual != NULL && atual->dados->rg != rg) {
      atual = atual->proximo;
  }
  do {
      printf("Escolha o que deseja alterar:\n");
      printf("1. Para Nome\n");
      printf("2. Para RG\n");
      printf("3. Para Idade\n");
      printf("4. Para sair\n");

      scanf("%d", &x);

        switch (x) {
          case 1: {
              printf("Digite o novo nome: ");
              scanf("%s", nome);
              strcpy(atual->dados->nome, nome);
              break;
          }
          case 2: {
              printf("Digite o novo RG: ");
              scanf("%s", rgn);
              strcpy(atual->dados->rg, rgn);
              break;
          }
          case 3: {
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






int main(void){
  char rg[20];
  int y;
  Lista *lista = criar_lista();
  do {
    printf("BOA TARDE\n");
    printf("Escolha o que deseja fazer: \n");
    printf("1. Cadastrar usuario\n");
    printf("2. Consultar Paciente\n");
    printf("3. Consultar Lista de Pacientes\n");
    printf("4. Alterar Info do Paciente\n");
    printf("5. Remover cadastro do Paciente\n");
    printf("6. Encerrar programa\n");
    scanf("%d", &y);
    switch (y) {
        case 1: {
            cadastrar(lista);
            break;
        }
        case 2: {
            printf("RG do Paciente qual deseja consultar");
            scanf("%s",rg);
            mostrar_paciente(lista,rg);
            break;
        }
        case 3: {
          mostrar_lista(lista);
            break;
        }
        case 4: {
            printf("Saindo...\n");
            break;
        }
        case 5: {
            printf("Saindo...\n");
            break;
        }
        default: {
            printf("Opção inválida. Tente novamente.\n");
            break;
        }
    }

  } while (y != 6);
  return 0;
}
