#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/atendimento.h"
#include "include/cadastro.h"
#include "include/pesquisa.h"

// Informacoes sobre a dupla
void sobre(){
    printf(" ========================\n ");
    printf("    Projeto feito por\n");
    printf(" ======================== \n");
    printf("Juan Manuel Citta, RA:24.123.022-6 \n");
    printf("Sebastian Citta, RA:24.123.068-9 \n");
    printf("No 4o Ciclo\n");
    printf("Curso: Ciencia da Computacao\n");
    printf("Disciplina: CC4652 - Estrutura de dados\n");
    printf("Terminado em: 06/11/2024\n");
    printf(" ======================== \n");
}

// Funcao principal que chama todas as funcoes de acesso criados nos modulos
int main(void){
    printf("Bem-Vindo \n");
  int y;
  do {
    printf("Escolha o que deseja fazer: \n");
    printf("1. Gerir a Lista de Pacientes\n");
    printf("2. Gerir a Fila de Atendimento\n");
    printf("3. Pesquisar Dados da Lista de Pacientes\n");
    printf("4. Sobre\n");
    printf("5. Encerrar programa\n");
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
        case 4:{
            sobre();
            break;
        }
        case 5: {
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