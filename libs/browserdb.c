//
// Created by diego on 04/01/2020.
//

#include "browserdb.h"
#include "database.h"
#include "extrafuncs.h"
#include <stdio.h>
#include <stdlib.h>

void formatar_nome_tabela(char *str);

void extrair(void *ptr, char *valor_na_coluna) {
    if (ptr != NULL) {
        int index = ((int *) ptr)[0];
        index++;
        int value = (int) strtol(valor_na_coluna, NULL, 10);
        ((int *) ptr)[0] = index;
        ((int *) ptr)[index] = value;
    }
}

int exibir_resultados(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna) {
    extrair(ptr, valor_na_coluna[0]);
    for (int i = 0; i < qtd_colunas; i++) {
        formatar_nome_tabela(nome_da_coluna[i]);
        upper(valor_na_coluna[i]);
        printf("\t\t%s: %s\n", nome_da_coluna[i], valor_na_coluna[i]);
    }
    puts("");
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
