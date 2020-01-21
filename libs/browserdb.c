//
// Created by diego on 04/01/2020.
//

#include "browserdb.h"
#include "database.h"
#include "extrafuncs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void formatar_nome_tabela(char *str);

void extrair_ids(int *ptr, char *valor_na_coluna) {
    if (ptr != NULL) {
        int index = 1;
        char *pt;
        pt = strtok(valor_na_coluna, ",");
        while (pt != NULL) {
            int value = (int) strtol(pt, NULL, 10);
            ptr[index] = value;
            index++;
            pt = strtok(NULL, ",");
        }
    }
}

int exibir_resultados(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna) {
    int qtd_resultados = (int) strtol(valor_na_coluna[0], NULL, 10);
    ((int *) ptr)[0] = qtd_resultados;

    if (qtd_resultados > 0) {
        extrair_ids((int *) ptr, valor_na_coluna[1]);

        for (int i = 2; i < qtd_colunas; i++) {
            upper(valor_na_coluna[i]);
            printf("\t\t%s\n", valor_na_coluna[i]);
        }
    }

    return 0;
}

void formatar_nome_tabela(char *str) {
    upper(str);
    while (*str) {
        if (*str == '_')
            *str = ' ';
        str++;
    }
}
