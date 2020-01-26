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

#define LIMIT_BUSCA 100

void formatar_quartos_disponiveis(char *sql, char *tipo, char *inicio, char *fim) {
    strcpy(sql,
           "SELECT count(id), group_concat(id, ','), 'TIPO: ' || descricao, 'VALOR: ' || valor, 'QUARTOS: \n\t\t[ ' || group_concat(id, ' ][ ') || ' ]'");
    strcat(sql, "FROM (SELECT q.id, q.valor, q.descricao FROM quartos q ");
    if (tipo != NULL) {
        strcat(sql, " WHERE q.tipo = ");
        strcat(sql, tipo);
        strcat(sql, " AND ");
    }
    strcat(sql, "q.id NOT IN (SELECT r.id_quarto FROM reservas r JOIN quartos_reservados qr ON r.id_quarto = qr.id ");
    strcat(sql, "WHERE (inicio <= '");
    strcat(sql, inicio);
    strcat(sql, "' AND fim >= '");
    strcat(sql, inicio);
    strcat(sql, "') OR (inicio < '");
    strcat(sql, fim);
    strcat(sql, "' AND fim >= '");
    strcat(sql, fim);
    strcat(sql, "') OR ('");
    strcat(sql, inicio);
    strcat(sql, "' <= inicio AND '");
    strcat(sql, fim);
    strcat(sql, "' >= inicio)));");
}

int mostrar_quartos_disponiveis(struct tm *data_inicio, struct tm *data_final, int tipo, int *ids) {
    char inicio[15], fim[15], tipo_quarto[3];
    char sql[500];

    formatar_data_sql(data_inicio, inicio);
    formatar_data_sql(data_final, fim);
    snprintf(tipo_quarto, 3, "%d", tipo);
    formatar_quartos_disponiveis(sql, tipo_quarto, inicio, fim);
    int qtd = executar_sql(sql, exibir_resultados, ids);

    return qtd;
}

int selecionar_quarto(struct tm *data_inicio, struct tm *data_final, int *id_quarto) {
    int total_quartos = 25;
    int ids_encontrados[LIMIT_BUSCA] = {0};
    int tipo;
    int op;

    do {
        limpar_tela();
        mostrar_titulo();
        puts("\n");
        tipo = selecionar_tipo_quarto();

        limpar_tela();
        mostrar_titulo();
        puts("\n");

        if (tipo == 0)
            return 0;
        else if (mostrar_quartos_disponiveis(data_inicio, data_final, tipo, ids_encontrados) == 0) {
            printf("\n\n\t\tNAO EXISTEM QUARTOS DESSE TIPO DISPONIVEIS NESSA DATA\n");
            pausa();
            continue;
        }

        while (1) {
            printf("\n\n\t\tNUMERO DO QUARTO: ");
            scanf(" %d", id_quarto);

            if (*id_quarto != 0 && is_in(*id_quarto, ids_encontrados, total_quartos)) {
                limpar_tela();
                mostrar_titulo();
                printf("\n\n\t\tDADOS DO QUARTO\n");
                busca_quarto_id(*id_quarto);

                printf("\n\n\t\t(1) SELECIONAR QUARTO (0) VOLTAR: ");
                scanf(" %d", &op);

                if (op == 1)
                    return *id_quarto;
                else if (op == 0)
                    return 0;

            } else {
                printf("\n\n\t\tNUMERO INVALIDO!\n");
                pausa();

                limpar_tela();
                mostrar_titulo();
                puts("\n");

                mostrar_quartos_disponiveis(data_inicio, data_final, tipo, ids_encontrados);
            }
        }
    } while (1);
}

int selecionar_tipo_quarto() {
    int tipo;
    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\n\t\tSELECIONAR QUARTO\n");
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

int busca_quarto_id(int id) {
    char sql[200];
    char str[5];
    int ids[5];

    strcpy(sql,
           "SELECT count(id), group_concat(id, ','), 'TIPO: ' || descricao, 'VALOR: ' || valor, 'NUMERO: \n\t\t[ ' || id || ' ]'");
    strcat(sql, "FROM (SELECT q.id, q.valor, q.descricao FROM quartos q ");
    strcat(sql, " WHERE id = ");
    snprintf(str, 5, "%d", id);
    strcat(sql, str);
    strcat(sql, ");");

    return executar_sql(sql, exibir_resultados, ids);
}