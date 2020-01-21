//
// Created by diego on 07/01/2020.
//

#include "reservas.h"
#include "../datas.h"
#include "../extrafuncs.h"
#include "../database.h"
#include "quartos.h"
#include "../browserdb.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inserir_data_reserva(struct tm *data_inicio, struct tm *data_final) {
    do {
        printf("\n\n\t\tDATA DE ENTRADA (EX.: DD-MM-AAAA): ");
        scanf(" %d %d %d", &data_inicio->tm_mday, &data_inicio->tm_mon, &data_inicio->tm_year);

        printf("\n\t\tDATA DE SAIDA (EX.: DD-MM-AAAA): ");
        scanf(" %d %d %d", &data_final->tm_mday, &data_final->tm_mon, &data_final->tm_year);

        if (validar_periodo(data_inicio, data_final) == 0) {
            printf("\n\nDATA OU PERIODO INVALIDO\n");
            pausa();
        } else
            break;

    } while (1);

}

void criar_nova_reserva(CLIENTE *c) {
    RESERVA r;

    if (c == NULL)
        c = (CLIENTE *) malloc(sizeof(CLIENTE));

    char opcao[2];

    limpar_tela();
    mostrar_titulo();

    do {
        printf("\n\n\n\t\tPERIODO DE HOSPEDAGEM\n\n");
        inserir_data_reserva(&r.inicio, &r.fim);

        selecionar_quarto(&r.inicio, &r.fim, &r.id_quarto);

        printf("\n\n\t\tCONFIRMAR DADOS (S) (N): ");
        scanf(" %s", opcao);
        if (opcao[0] == 's' || opcao[0] == 'S') break;
    } while (1);

    pegar_dados_cliente(c);

    gerar_id("clientes", &c->id);
    gerar_id("reservas", &r.id);

    r.id_cliente = c->id;
    c->id_reserva = r.id;
    c->id_quarto = r.id_quarto;


    registrar_reserva(formatar_reserva(&r));
}

void mostrar_reserva(RESERVA *r, CLIENTE *c) {
    printf("\t\tID: %04d\n", r->id);
    printf("\t\t NOME DO CLIENTE: %s\n", c->nome);
    printf("\t\t  CPF: %s\n", c->cpf);
    // printf("\t\t   QUARTO: %d\n\n", r->qrt->id);
    printf("\t\t    RESERVA: ");
    puts("\t-----------------------------------------------------------------------------------\n");
}

int busca_reserva(char *coluna, char *valor, int *ids) {
    int qtd_resultados;
    qtd_resultados = db_listar_clientes(coluna, valor, -1, NULL, ids, exibir_resultados);
    return qtd_resultados;
}

char *formatar_reserva(RESERVA *r) {
    char *sql = (char *) malloc(sizeof(char) * 200);
    char str[100];

    strcpy(sql, "insert into reservas values (null, ");
    snprintf(str, 10, "%d", r->id_cliente);
    strcat(sql, str);
    strcat(sql, ", ");
    snprintf(str, 10, "%d", r->id_quarto);
    strcat(sql, str);
    strcat(sql, ", '");
    formatar_data_sql(&r->inicio, str);
    strcat(sql, str);
    formatar_data_sql(&r->fim, str);
    strcat(sql, "', '");
    strcat(sql, str);
    strcat(sql, "');");

    reservar_quarto(r->id_quarto, r->id);
    return sql;
}

void exibir_qtd_reservas() {

}

void buscar_reserva() {
    int opcao;

    char dados_busca[50];

    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tBUSCAR RESERVA\n\n");
        printf("\t\t(1) BUSCAR POR CLIENTE DA RESERVA\n");
        printf("\t\t  (2) BUSCAR POR QUARTO DA RESERVA\n");
        printf("\t\t    (3) BUSCAR POR DATA DA RESERVA\n");
        printf("\t\t      (4) BUSCAR POR ID DA RESERVA\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n\t\tINSIRA O NOME: ");
                busca_cliente("NOME", dados_busca, NULL);
                break;
            case 2:
                printf("\n\t\tINSIRA O CPF: ");
                busca_cliente("NOME", dados_busca, NULL);
                break;
            case 3:
                printf("\n\t\tINSIRA O ID: ");
                busca_cliente("NOME", dados_busca, NULL);
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