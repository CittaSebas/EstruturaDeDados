#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/atendimento.h"
#include "include/cadastro.h"
#include "include/pesquisa.h"


int lista(void){
  char rg[20];
  int y;
  Lista *lista = criar_lista();
  carregarLista(lista);
  pesquisar_dados();
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
  
  return 0;
}

int main(void) {
    lista();
  Fila *fila = cria_Fila();
  char rg[20];
  int y;
  do {
    printf("BOA TARDE\n");
    printf("Escolha o que deseja fazer: \n");
    printf("1. Registrar Paciente na Fila\n");
    printf("2. Atualizar Fila\n");
    printf("3. Consultar Fila\n");
    printf("4. Encerrar programa\n");
    scanf("%d", &y);
    switch (y) {
        case 1: {
            printf("RG do Paciente a ser atendido: \n");
            scanf("%s",rg);
            enfileirar(fila, rg);
            break;
        }
        case 2: {
            printf("Atualizar Fila\n");
            desenfileirar(fila);
            break;
        }
        case 3: {
          show(fila);
            break;
        }
        default: {
          printf("Opcao invalida. \n");
          break;
        }

    }
  }
  while (y != 4);
  return 0;
}