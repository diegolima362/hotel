//
// Created by diego on 04/01/2020.
//

#include "browserdb.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>

int exibir_quarto(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna) {
    if (ptr != NULL) {
        int index = ++((int *) ptr)[0];
        int value = 0;
        value = (int) strtol(valor_na_coluna[0], NULL, 10);
        ((int *) ptr)[index] = value;
    }

    printf("\n\t\t%5s%5s%17s   $%s", valor_na_coluna[0], valor_na_coluna[1], valor_na_coluna[2], valor_na_coluna[3]);

    return 0;
}

int exibir_cliente(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna) {
    printf("\n\t\t%3s%20s%20s", valor_na_coluna[0], valor_na_coluna[1], valor_na_coluna[2]);
    return 0;
}

int exibir_reserva(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna) {
    printf("\n\t\t%3s%20s%20s", valor_na_coluna[0], valor_na_coluna[1], valor_na_coluna[2]);
    return 0;
}