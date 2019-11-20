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
    sqlite3_open(DB_PATH, &db);
    sqlite3_exec(db, query, callback, NULL, &error_msg);
    if (error_msg != NULL)
        puts(error_msg);
    sqlite3_close(db);

    return error_msg;
}

void criar_quartos(int n, char *query, sqlite3 *db) {
    char *error_msg;
    for (int i = 0; i < n; i++)
        sqlite3_exec(db, query, NULL, NULL, &error_msg);
}

void gerar_dados(sqlite3 *db) {
    char *error_msg, *error_msg1, *error_msg2;

    char *cliente = "insert into clientes values (null, 'joao', '123', 0, 0);"
                    "insert into clientes values (null, 'jose', '321', 0, 0);"
                    "insert into clientes values (null, 'lucas', '111', 0, 0);"
                    "insert into clientes values (null, 'mateus', '122', 0, 0);"
                    "insert into clientes values (null, 'pedro', '112', 0, 0);"
                    "insert into clientes values (null, 'seinfeld', '311', 0, 0);"
                    "insert into clientes values (null, 'kramer', '254', 0, 0);"
                    "insert into clientes values (null, 'elane', '678', 0, 0);"
                    "insert into clientes values (null, 'george', '158', 0, 0);"
                    "insert into clientes values (null, 'newman', '187', 0, 0);"
                    "insert into clientes values (null, 'leo', '877', 0, 0);";

    char *reservas = "insert into reservas values (null, 1, 3, current_date, current_timestamp);"
                     "insert into reservas values (null, 2, 3, current_date, current_timestamp);"
                     "insert into reservas values (null, 3, 3, current_date, current_timestamp);"
                     "insert into reservas values (null, 5, 3, current_date, current_timestamp);"
                     "insert into reservas values (null, 7, 3, current_date, current_timestamp);"
                     "insert into reservas values (null, ABS(RANDOM() % 10), ABS(RANDOM() % 10), current_date, current_timestamp);"
                     "insert into reservas values (null, ABS(RANDOM() % 10), ABS(RANDOM() % 10), current_date, current_timestamp);"
                     "insert into reservas values (null, ABS(RANDOM() % 10), ABS(RANDOM() % 10), current_date, current_timestamp);"
                     "insert into reservas values (null, ABS(RANDOM() % 10), ABS(RANDOM() % 10), current_date, current_timestamp);"
                     "insert into reservas values (null, ABS(RANDOM() % 10), ABS(RANDOM() % 10), current_date, current_timestamp);"
                     "insert into reservas values (null, ABS(RANDOM() % 10), ABS(RANDOM() % 10), current_date, current_timestamp);"
                     "insert into reservas values (null, ABS(RANDOM() % 10), ABS(RANDOM() % 10), current_date, current_timestamp);";

    sqlite3_exec(db, cliente, NULL, NULL, &error_msg);

    criar_quartos(20, "insert into quartos values (null, 1, 'Executivo triplo', 0, 440, null, null);", db);
    criar_quartos(15, "insert into quartos values (null, 2, 'Executivo duplo', 0, 385, null, null);", db);
    criar_quartos(5, "insert into quartos values (null, 3, 'Executivo simples', 0, 360, null, null);", db);
    criar_quartos(20, "insert into quartos values (null, 4, 'Luxo triplo', 0, 620, null, null);", db);
    criar_quartos(15, "insert into quartos values (null, 5, 'Luxo duplo', 0, 570, null, null);", db);
    criar_quartos(5, "insert into quartos values (null, 6, 'Luxo simples', 0, 520, null, null);", db);
    criar_quartos(5, "insert into quartos values (null, 7, 'Presidencial', 0, 1200, null, null);", db);

    sqlite3_exec(db, reservas, NULL, NULL, &error_msg2);

    puts(error_msg);
    puts(error_msg1);
    puts(error_msg2);
}

int criar_banco() {
    char *error_msg, *error_msg1, *error_msg2;
    sqlite3 *db;
    sqlite3_open(DB_PATH, &db);


    char *table_clientes =
            "create table clientes ( id integer constraint clientes_pk primary key autoincrement, nome char(15), cpf char(11), id_reserva integer constraint clientes_reservas_id_fk references reservas (id), id_quarto integer); create unique index clientes_id_uindex on clientes (id);";
    char *table_quartos =
            "create table quartos ( id integer constraint quarto_pk primary key autoincrement, tipo integer, descricao char(15), ocupado integer, valor real, id_cliente integer constraint quarto_clientes_id_fk references clientes (id), id_reserva integer constraint quarto_reserva_id_fk references reservas (id)); create unique index quartos_id_uindex on quartos (id);";
    char *table_reservas =
            "create table reservas ( id integer constraint reservas_pk primary key autoincrement, id_cliente integer \tconstraint reservas_clientes_id_fk references clientes, id_quarto integer constraint reservas_quartos_id_fk references quartos, inicio text, fim text ); create unique index reservas_id_uindex on reservas (id);\n";
    int created;
    if (sqlite3_exec(db, table_clientes, NULL, NULL, &error_msg) == SQLITE_OK &&
        sqlite3_exec(db, table_quartos, NULL, NULL, &error_msg1) == SQLITE_OK &&
        sqlite3_exec(db, table_reservas, NULL, NULL, &error_msg2) == SQLITE_OK) {
        created = 1;
    } else {
        created = 0;
    }
    gerar_dados(db);
    sqlite3_close(db);

    return created;
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
    free(query);
    return 0;
}

int mostrar_resultados(void *ptr, int resultados, char **STR1, char **STR2) {
    int i = 0;
    while (STR1[i]) {
        printf("%s ", STR1[i]);
        i++;
    }
    putchar('\n');

    return 0;
}

int listar_clientes(char *column, char *filter, int limit) {
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
    executar_query(query, mostrar_resultados);

    free(query);

    return 0;
}

int listar_reservas(char *column, char *filter, int limit) {
    char *query = (char *) malloc(sizeof(char) * 150);
    char char_limit[3];
    snprintf(char_limit, 3, "%d", limit);

    strcpy(query, "select * from reservas where ");

    if (strcmp(column, "id") == 0 || strcmp(column, "id_cliente") == 0) {
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
    executar_query(query, mostrar_resultados);

    free(query);

    return 0;
}

int listar_quartos(char *column, char *filter, int limit) {
    char *query = (char *) malloc(sizeof(char) * 150);
    char char_limit[3];
    snprintf(char_limit, 3, "%d", limit);

    strcpy(query, "select * from quartos where ");

    if (strcmp(column, "id") == 0 || strcmp(column, "valor") == 0) {
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
    executar_query(query, mostrar_resultados);

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
    executar_query(query, mostrar_resultados);

    free(query);

    return 0;
}

int inserir_reserva(RESERVA *r) {
    return 0;
}

