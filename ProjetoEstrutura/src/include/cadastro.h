#ifndef CADASTRO_H
#define CADASTRO_H

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

int salvarLista(Lista *lista);
int carregarLista(Lista *lista);
ELista *criar_ELista(Registro *registro);
Lista *criar_lista();
void cadastrar(Lista *lista);
void remover(Lista *lista, char rg[20]);
void mostrar_lista(Lista *lista);
void mostrar_paciente(Lista *lista, char rg[20]);
void alterar(Lista *lista, char rg[20]);

#endif