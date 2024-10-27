#ifndef CADASTRO_H
#define CADASTRO_H
#include "util.h"

// Structs padroes para lista dinamica
typedef struct ELista {
  struct ELista *proximo;
  Registro *dados;
} ELista;

typedef struct {
  ELista *primeiro;
  int qtde;
} Lista;

#endif