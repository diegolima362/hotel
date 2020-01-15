//
// Created by diego on 07/01/2020.
//

#include "quartos.h"
#include "../datas.h"

#include <bits/types/struct_tm.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../database.h"
#include "../browserdb.h"
#include "../extrafuncs.h"

int mostrar_quartos_disponiveis(struct tm *data_inicio, struct tm *data_final, int tipo, int *index) {
    char inicio[15], fim[15], tipo_quarto[3];

    formatar_data_sql(data_inicio, inicio);
    formatar_data_sql(data_final, fim);
    snprintf(tipo_quarto, 3, "%d", tipo);

    printf("\n\t\t%6s%7s%11s%12s", "NUM", "TIPO", "DESCRICAO", "VALOR");

    listar_quartos_ocupados(inicio, fim, tipo_quarto, 0, index, exibir_resultados);

    return 0;
}

int selecionar_quarto(struct tm *data_inicio, struct tm *data_final, int *id_quarto) {
    int total_quartos = 25;
    int index[25] = {0};

    int tipo = selecionar_tipo_quarto();
    if (tipo == 0)
        return -1;
    do {
        mostrar_quartos_disponiveis(data_inicio, data_final, tipo, index);
        printf("\n\n\t\tNUMERO DO QUARTO: ");
        scanf(" %d", id_quarto);

        index[0] = 0;
        if (*id_quarto != 0 && is_in(*id_quarto, index, total_quartos)) {
            return *id_quarto;
        } else {
            printf("\n\n\t\tNUMERO INVALIDO!\n");
            pausa();
        }
    } while (1);
}

int selecionar_tipo_quarto() {
    int tipo;
    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tSELECIONAR QUARTO\n");
        printf("\n\t\t(7) PRESIDENCIAL\n");
        printf("\n\t\t (6) LUXO SIMPLES");
        printf("\n\t\t  (5) LUXO DUPLO");
        printf("\n\t\t   (4) LUXO TRIPLO\n");
        printf("\n\t\t  (3) EXECUTIVO SIMPLES");
        printf("\n\t\t (2) EXECUTIVO DUPLO");
        printf("\n\t\t(1) EXECUTIVO TRIPLO\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        limpar_teclado();
        scanf(" %d", &tipo);

        if (tipo >= 0 && tipo <= 7)
            break;
        else {
            printf("\n\n\t\tOPCAO INVALIDA!\n");
            pausa();
        }
    } while (1);

    return tipo;
}

int busca_quarto(char *coluna, char *valor, int *ids) {
    int qtd_resultados;
    qtd_resultados = db_listar_clientes(coluna, valor, -1, ids, exibir_resultados);
    return qtd_resultados;
}