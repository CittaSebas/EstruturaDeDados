#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/atendimento.h"
#include "include/cadastro.h"
#include "include/pesquisa.h"



int main(void){
    printf("Bem-Vindo \n");
  int y;
  do {
    printf("Escolha o que deseja fazer: \n");
    printf("1. Gerir a Lista de Pacientes\n");
    printf("2. Gerir a Fila de Atendimento\n");
    printf("3. Pesquisar Dados da Lista de Pacientes\n");
    printf("4. Encerrar programa\n");
    scanf("%d", &y);
    switch (y) {
        case 1: {
            lista();
            break;
        }
        case 2: {
            atendimento();
            break;
        }
        case 3: {
          pesquisar_dados();
            break;
        }
        case 4: {
            return 0;
        }
        default: {
          printf("Opcao invalida. \n");
          break;
        }

    }
  }
  while (y != 5);
  return 0;
}