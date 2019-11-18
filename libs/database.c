//
// Created by Administrador on 14/11/2019.
//
#include "database.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sqlite/sqlite3.h"

int total_clientes = 0;

char *executar_query(char *query, int (*callback)(void *, int, char **, char **)) {
    char *error_msg;
    sqlite3 *db;
    sqlite3_open("hotel.db", &db);
    sqlite3_exec(db, query, callback, NULL, &error_msg);
    if (error_msg != NULL)
        puts(error_msg);
    sqlite3_close(db);

    return error_msg;
}

int inserir_cliente(CLIENTE *c) {
    char *query = (char *) malloc(sizeof(char) * 150);

    strcpy(query, "INSERT INTO clientes VALUES(NULL, '");
    strcat(query, c->nome);
    strcat(query, "', '");
    strcat(query, c->cpf);
    strcat(query, "', '");
    strcat(query, c->phone);
    strcat(query, "', '");
    strcat(query, c->cred_card);
    strcat(query, "', 1);");

    executar_query(query, NULL);

    return 0;
}

int mostrar_clientes(void *ptr, int resultados, char **STR1, char **STR2) {
    printf("%3s", STR1[0]);
    printf("|%10s", STR1[1]);
    printf("|%15s\n", STR1[2]);

    return 0;
}

int listar_clientes(char *filtro, int limit) {
    char *query = (char *) malloc(sizeof(char) * 150);
    char char_limit[3];
    snprintf(char_limit, 3, "%d", limit);

    strcpy(query, "select * from clientes ");
    if (limit > 0) {
        strcat(query, "limit ");
        strcat(query, char_limit);
    }
    strcat(query, ";");

    executar_query(query, mostrar_clientes);

    free(query);

    return 0;
}

int montar_cliente(void *ptr, int resultados, char **STR1, char **STR2) {
    int i;

    for (i = 0; STR1[i] != NULL; i++) {
        printf("%s = %s\n", STR2[i], STR1[i]);
    }

    return 0;
}

int recuperar_clientes(CLIENTE *c) {
    char *query = (char *) malloc(sizeof(char) * 150);
    strcpy(query, "select clientes.id, clientes.nome, clientes.cpf from clientes;");
    executar_query(query, montar_cliente);
    free(query);
    return 0;
}

int buscar_cliente(char *column, char *filter, int limit) {
    char *query = (char *) malloc(sizeof(char) * 150);
    char char_limit[3];
    snprintf(char_limit, 3, "%d", limit);

    strcpy(query, "select id, nome, cpf from clientes where ");

    if (strcmp(column, "id") == 0) {
        strcat(query, column);
        strcat(query, " = ");
        strcat(query, filter);
    } else {
        strcat(query, column);
        strcat(query, " like '");
        strcat(query, filter);
        strcat(query, "' ");
    }

    if (limit > 0) {
        strcat(query, " limit ");
        strcat(query, char_limit);
    }

    strcat(query, ";");
    executar_query(query, mostrar_clientes);

    free(query);

    return 0;
}

int montar_qtd(void *ptr, int resultados, char **STR1, char **STR2) {
    total_clientes = (int) strtol(STR1[0], NULL, 10);
    return total_clientes;
}

int qtd_clientes() {
    char *query = (char *) malloc(sizeof(char) * 150);
    strcpy(query, "select count (id) FROM clientes;");
    executar_query(query, montar_qtd);
    free(query);

    return total_clientes;
}

int remover_cliente(char *column, char *filter) {
    char *query = (char *) malloc(sizeof(char) * 150);

    strcpy(query, "delete from clientes where ");

    if (strcmp(column, "id") == 0) {
        strcat(query, column);
        strcat(query, " = ");
        strcat(query, filter);
    } else {
        strcat(query, column);
        strcat(query, " like '");
        strcat(query, filter);
        strcat(query, "' ");
    }

    strcat(query, ";");
    executar_query(query, mostrar_clientes);

    free(query);

    return 0;
}

int inserir_reserva(RESERVA *r) {
    return 0;
}

