//
// Created by Administrador on 14/11/2019.
//
#include "database.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sqlite3.h>

char *executar_query(char *query, int (*callback)(void *, int, char **, char **), void *ptr) {
    char *error_msg;
    sqlite3 *db;

    sqlite3_open(DB_PATH, &db);
    sqlite3_exec(db, query, callback, ptr, &error_msg);
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
    sqlite3_open(DB_PATH, &db);
    char *error_msg, *error_msg1;

    char *cliente = "insert into clientes values (null, 'joao', '123','3115', 0, 0);"
                    "insert into clientes values (null, 'jose', '321','3115', 0, 0);"
                    "insert into clientes values (null, 'lucas', '111', '3115', 0, 0);"
                    "insert into clientes values (null, 'mateus', '122', '3115',0, 0);"
                    "insert into clientes values (null, 'pedro', '112', '3115',0, 0);"
                    "insert into clientes values (null, 'seinfeld', '311','3115', 0, 0);"
                    "insert into clientes values (null, 'kramer', '254', '3115', 0, 0);"
                    "insert into clientes values (null, 'elane', '678','3115', 0, 0);"
                    "insert into clientes values (null, 'george', '158', '3115', 0, 0);"
                    "insert into clientes values (null, 'newman', '187', '3115', 0, 0);"
                    "insert into clientes values (null, 'leo', '877', '3115', 0, 0);";

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
    puts("CLIENTES ...");
    sqlite3_exec(db, cliente, NULL, NULL, &error_msg);
    puts("CLIENTES OK");

    puts("QUARTOS ...");
    criar_quartos(20, "insert into quartos values (null, 1, 'Executivo triplo', 0, 440, null, null);", db);
    criar_quartos(15, "insert into quartos values (null, 2, 'Executivo duplo', 0, 385, null, null);", db);
    criar_quartos(5, "insert into quartos values (null, 3, 'Executivo simples', 0, 360, null, null);", db);
    criar_quartos(20, "insert into quartos values (null, 4, 'Luxo triplo', 0, 620, null, null);", db);
    criar_quartos(15, "insert into quartos values (null, 5, 'Luxo duplo', 0, 570, null, null);", db);
    criar_quartos(5, "insert into quartos values (null, 6, 'Luxo simples', 0, 520, null, null);", db);
    criar_quartos(5, "insert into quartos values (null, 7, 'Presidencial', 0, 1200, null, null);", db);
    puts("QUARTOS OK");

    puts("RESERVAS ...");
    sqlite3_exec(db, reservas, NULL, NULL, &error_msg1);
    puts("RESERVAS OK");

    if (error_msg && error_msg1) {
        puts(error_msg);
        puts(error_msg1);
    }

}

int criar_banco() {
    char *error_msg, *error_msg1, *error_msg2;
    sqlite3 *db;
    sqlite3_open(DB_PATH, &db);

    char *table_clientes =
            "create table clientes ( id integer constraint clientes_pk primary key autoincrement, nome char(15), cpf char(11), "
            "phone char(15), id_reserva integer constraint clientes_reservas_id_fk references reservas (id), id_quarto integer); "
            "create unique index clientes_id_uindex on clientes (id);";
    char *table_quartos =
            "create table quartos ( id integer constraint quarto_pk primary key autoincrement, tipo integer, descricao char(15), "
            "ocupado integer, valor real, id_cliente integer constraint quarto_clientes_id_fk references clientes (id), "
            "id_reserva integer constraint quarto_reserva_id_fk references reservas (id)); "
            "create unique index quartos_id_uindex on quartos (id);";

    char *table_reservas =
            "create table reservas ( id integer constraint reservas_pk primary key autoincrement, "
            "id_cliente integer constraint reservas_clientes_id_fk references clientes, "
            "id_quarto integer constraint reservas_quartos_id_fk references quartos, "
            "inicio text, fim text ); "
            "create unique index reservas_id_uindex on reservas (id);\n";

    char *table_reservas_inativas =
            "create table reservas_inativas( id integer constraint reservas_inativas_pk primary key autoincrement, "
            "id_cliente integer constraint reservas_inativas_clientes_id_fk references clientes, "
            "id_quarto integer constraint reservas_inativas_quartos_id_fk references quartos, "
            "inicio text, fim text ); "
            "create unique index reservas_inativas_id_uindex on reservas_inativas (id);\n";

    int created;

    if (sqlite3_exec(db, table_clientes, NULL, NULL, &error_msg) == SQLITE_OK &&
        sqlite3_exec(db, table_quartos, NULL, NULL, &error_msg1) == SQLITE_OK &&
        sqlite3_exec(db, table_reservas, NULL, NULL, &error_msg2) == SQLITE_OK &&
        sqlite3_exec(db, table_reservas_inativas, NULL, NULL, &error_msg2) == SQLITE_OK) {
        created = 1;
    } else {
        created = 0;
    }


    sqlite3_close(db);

    gerar_dados(db);
    return created;
}

int inserir_cliente(CLIENTE *c) {
    char *query = (char *) malloc(sizeof(char) * 150);
    strcpy(query, "insert into clientes values (null, '");
    strcat(query, c->nome);
    strcat(query, "', '");
    strcat(query, c->cpf);
    strcat(query, "', '");
    strcat(query, c->phone);
    strcat(query, "', 0, 0);");
    puts(query);
    char *erro = executar_query(query, NULL, NULL);
    if (erro)puts(erro);
    free(query);
    return 0;
}

int mostrar_resultados(void *ptr, int resultados, char **STR1, char **STR2) {
    int i = 0;
    printf("int = %d\n", resultados);
    while (STR1[i]) {
        printf("%s ", STR1[i]);
        i++;
    }
    putchar('\n');

    return 0;
}

int listar_clientes(char *column, char *filter, int limit, int (*callback)(void *, int, char **, char **)) {
    char *query = (char *) malloc(sizeof(char) * 150);
    char char_limit[3];
    snprintf(char_limit, 3, "%d", limit);

    strcpy(query, "select * from clientes ");

    if (strcmp(column, "NULL") != 0) {
        strcat(query, " where ");

        if (strcmp(column, " id ") == 0) {
            strcat(query, column);
            strcat(query, " = ");
            strcat(query, filter);
        } else {
            strcat(query, column);
            strcat(query, " like '");
            strcat(query, filter);
            strcat(query, "' ");
        }
    }

    if (limit > 0) {
        strcat(query, " limit ");
        strcat(query, char_limit);
    }

    strcat(query, ";");
    puts(query);
    executar_query(query, callback, NULL);

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
    executar_query(query, mostrar_resultados, NULL);

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
    executar_query(query, mostrar_resultados, NULL);

    free(query);
    return 0;
}

int montar_cliente(void *ptr, int resultados, char **STR1, char **STR2) {
    ((CLIENTE *) ptr)->id = (int) strtol(STR1[0], NULL, 10);
    strcpy(((CLIENTE *) ptr)->nome, STR1[1]);
    strcpy(((CLIENTE *) ptr)->cpf, STR1[2]);

    return 0;
}

CLIENTE *recuperar_clientes(CLIENTE *c, char *id) {
    char *error_msg;
    char *query = (char *) malloc(sizeof(char) * 150);
    strcpy(query, "select * from clientes where id = ");
    strcat(query, id);
    executar_query(query, montar_cliente, c);
    free(query);

    return c;

}

int montar_qtd(void *ptr, int resultados, char **STR1, char **STR2) {
    *((int *) ptr) = (int) strtol(STR1[0], NULL, 10);
    return 0;
}

int get_qtd_clientes() {
    int total;
    char *query = (char *) malloc(sizeof(char) * 150);

    strcpy(query, "select count(id) from clientes;");

    executar_query(query, montar_qtd, &total);
    free(query);

    return total;
}

int get_qtd_reservas() {
    int total;
    char *query = (char *) malloc(sizeof(char) * 150);
    strcpy(query, "select count(id) from reservas;");
    executar_query(query, montar_qtd, &total);
    free(query);

    return total;
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
    executar_query(query, mostrar_resultados, NULL);

    free(query);

    return 0;
}

int remover_reserva(char *column, char *filter) {
    char *query = (char *) malloc(sizeof(char) * 150);

    strcpy(query, "insert into reservas_inativas select * from reservas where id = ");
    strcat(query, filter);
    strcat(query, " ;");
    executar_query(query, NULL, NULL);

    strcpy(query, "delete from reservas where id = ");
    strcat(query, filter);
    strcat(query, " ;");
    executar_query(query, NULL, NULL);

    free(query);

    return 0;
}

int inserir_reserva(RESERVA *r) {
    return 0;
}

