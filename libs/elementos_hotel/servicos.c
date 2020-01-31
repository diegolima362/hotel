//
// Created by diego on 07/01/2020.
//

#include <stdio.h>
#include "../extrafuncs.h"

void exibir_menu_gerenciar_servicos() {
    int opcao;
    do {
        mostrar_titulo();

        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                limpar_tela();
                break;
            case 0:
                return;
            default:
                printf("\n\nOPCAO INVALIDA!\n\n");
                pausa();
                break;
        }
    } while (opcao != 0);
}
