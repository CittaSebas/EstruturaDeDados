
#ifndef UTIL_H
#define UTIL_H

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

#endif 