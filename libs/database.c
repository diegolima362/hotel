//
// Created by Administrador on 14/11/2019.
//
#include "database.h"
#include "datas.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sqlite3.h>

int executar_sql(char *sql, int (*callback)(void *, int, char **, char **), void *ptr);

void executar_sql_externa(char *sql) {
    executar_sql(sql, NULL, NULL);
}

int executar_sql(char *sql, int (*callback)(void *, int, char **, char **), void *ptr) {
    char *error_msg;
    sqlite3 *db;

    sqlite3_open(DB_PATH, &db);
    sqlite3_exec(db, sql, callback, ptr, &error_msg);
    if (error_msg != NULL)
        puts(error_msg);
    sqlite3_close(db);

    return ptr != NULL ? ((int *) ptr)[0] : 0;
}

void criar_quartos(int n, char *sql, sqlite3 *db) {
    char *error_msg;
    for (int i = 0; i < n; i++)
        sqlite3_exec(db, sql, NULL, NULL, &error_msg);
}

void gerar_dados(sqlite3 *db) {
    sqlite3_open(DB_PATH, &db);
    char *error_msg, *error_msg1;

    puts("QUARTOS ...");
    criar_quartos(20, "insert into quartos values (null, 1, 'Executivo triplo', 440);", db);
    criar_quartos(15, "insert into quartos values (null, 2, 'Executivo duplo', 385);", db);
    criar_quartos(5, "insert into quartos values (null, 3, 'Executivo simples', 360);", db);
    criar_quartos(20, "insert into quartos values (null, 4, 'Luxo triplo', 620);", db);
    criar_quartos(15, "insert into quartos values (null, 5, 'Luxo duplo', 570);", db);
    criar_quartos(5, "insert into quartos values (null, 6, 'Luxo simples', 520);", db);
    criar_quartos(5, "insert into quartos values (null, 7, 'Presidencial', 1200);", db);
    puts("QUARTOS OK");

}

int criar_banco() {
    char *error_msg, *error_msg1, *error_msg2;
    sqlite3 *db;
    sqlite3_open(DB_PATH, &db);

    char *table_clientes = "create table clientes ( "
                           "id integer constraint clientes_pk primary key autoincrement, "
                           "nome text, sobrenome text, cpf text, phone text, "
                           "id_quarto integer constraint clientes_id_quarto_fk  references reservas (id_quarto), "
                           "id_reserva integer constraint clientes_id_reserva_fk references reservas);"
                           "create unique index clientes_id_uindex on clientes (id);";

    char *table_quartos = "create table quartos ( "
                          "id integer constraint quarto_pk primary key autoincrement, tipo integer, "
                          "descricao char(15), valor real);"
                          "create unique index quartos_id_uindex on quartos (id);";

    char *table_quartos_reservados = "create table quartos_reservados( "
                                     "\"id\" integer constraint quartos_registrados_pk primary key autoincrement, "
                                     "id_quarto  integer constraint quartos_registrados_id_quarto_fk references reservas (id_quarto), "
                                     "id_reserva integer references reservas);"
                                     "create unique index quartos_registrados_is_uindex on quartos_reservados (\"id\");";

    char *table_reservas = "create table reservas ( "
                           "id integer constraint reservas_pk primary key autoincrement, "
                           "id_cliente integer constraint reservas_clientes_id_fk references clientes, "
                           "id_quarto integer constraint reservas_quartos_id_fk references quartos, "
                           "inicio text, fim text ); "
                           "create unique index reservas_id_uindex on reservas (id);\n";

    char *table_reservas_inativas = "create table reservas_inativas( "
                                    "id integer constraint reservas_inativas_pk primary key autoincrement, "
                                    "id_cliente integer constraint reservas_inativas_clientes_id_fk references clientes, "
                                    "id_quarto integer constraint reservas_inativas_quartos_id_fk references quartos, "
                                    "inicio text, fim text ); "
                                    "create unique index reservas_inativas_id_uindex on reservas_inativas (id);\n";

    int created;

    if (sqlite3_exec(db, table_clientes, NULL, NULL, &error_msg) == SQLITE_OK &&
        sqlite3_exec(db, table_quartos, NULL, NULL, &error_msg1) == SQLITE_OK &&
        sqlite3_exec(db, table_quartos_reservados, NULL, NULL, &error_msg1) == SQLITE_OK &&
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

int listar_quartos_ocupados(char *inicio, char *fim, char *tipo, int ocupado, int *ids,
                            int (*callback)(void *, int, char **, char **)) {

    char *sql = (char *) malloc(sizeof(char) * 350);
    strcpy(sql, "SELECT q.id, q.tipo, q.descricao, q.valor FROM quartos q WHERE ");

    if (tipo != NULL) {
        strcat(sql, "q.tipo = ");
        strcat(sql, tipo);
        strcat(sql, " and ");
    }

    strcat(sql, "q.id ");

    if (ocupado == 0)
        strcat(sql, " NOT ");

    strcat(sql, "IN ( SELECT r.id_quarto FROM reservas r "
                "JOIN quartos_reservados qr ON r.id_quarto = qr.id WHERE (inicio <= '");
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
    strcat(sql, "' >= inicio));");

    executar_sql(sql, callback, ids);
    free(sql);

    return 0;
}

int
db_listar_clientes(char *column, char *filter, int limit, char *order_by, void *ids,
                   int (*callback)(void *, int, char **, char **)) {

    char *sql = (char *) malloc(sizeof(char) * 500);
    char char_limit[5];

    strcpy(sql, "SELECT count(id) as 'qtd results', group_concat(id,',') as 'ids', group_concat(concat, "
                "'\n\t\t-----------------------------------------------\n\t\t') as result "
                "FROM ("
                "SELECT id, 'ID: ' || id || '\n\t\t' || 'NOME: ' || nome || ' ' || sobrenome || '\n\t\t' ||"
                "'CPF: ' || cpf || '\n\t\t' ||"
                "'PHONE: ' || phone || '\n\t\t' ||"
                "'RESERVA: ' || id_reserva || '\n\t\t' ||"
                "'QUARTO: ' || id_quarto"
                " as concat FROM clientes ");

    if (strcmp(column, "NULL") != 0) {
        strcat(sql, " where ");

        if (strcmp(column, "id") == 0 || strcmp(column, "id_quarto") == 0 || strcmp(column, "id_reserva") == 0 ||
            strcmp(column, "id_reserva!") == 0) {
            strcat(sql, column);
            strcat(sql, "= ");
            strcat(sql, filter);
        } else {
            if (strcmp(column, "fullname") == 0) {
                strcat(sql, "nome || ' ' || sobrenome LIKE '%");
                strcat(sql, filter);
                strcat(sql, "%' ");
            } else {
                strcat(sql, column);
                strcat(sql, " like '");
                strcat(sql, filter);
                strcat(sql, "' ");
            }
        }
    }

    if (order_by != NULL) {
        strcat(sql, " order by ");
        strcat(sql, order_by);
    }

    if (limit > 0) {
        snprintf(char_limit, 5, "%d", limit);
        strcat(sql, " limit ");
        strcat(sql, char_limit);
    }

    strcat(sql, ");");

    int qtd_resultados = executar_sql(sql, callback, ids);

    free(sql);

    return qtd_resultados;
}

int
db_listar_reservas(char *column, char *filter, int limit, char *order_by, void *ids,
                   int (*callback)(void *, int, char **, char **)) {

    char *sql = (char *) malloc(sizeof(char) * 500);
    char char_limit[5];

    strcpy(sql,
           "SELECT count(id), group_concat(id, ','), group_concat(concat, '\t\t-----------------------------------------------\n\t\t') as result "
           "FROM (SELECT id, 'RESERVA: ' || id || '\n\t\t' || 'CLIENTE: ' || id_cliente || '\n\t\t' || 'QUARTO: ' || id_quarto || '\n\t\t' || "
           "'INICIO: ' || inicio || '\n\t\t' || 'FIM: ' || fim as concat FROM reservas ");

    if (strcmp(column, "NULL") != 0) {
        strcat(sql, " where ");
        strcat(sql, column);
        strcat(sql, "= ");
        strcat(sql, filter);
    }

    if (order_by != NULL) {
        strcat(sql, " order by ");
        strcat(sql, order_by);
    }

    if (limit > 0) {
        snprintf(char_limit, 5, "%d", limit);
        strcat(sql, " limit ");
        strcat(sql, char_limit);
    }

    strcat(sql, ");");

    int qtd_resultados = executar_sql(sql, callback, ids);

    free(sql);

    return qtd_resultados;
}

int
db_listar_quartos(char *column, char *filter, int limit, char *order_by, void *ids,
                  int (*callback)(void *, int, char **, char **)) {

    char *sql = (char *) malloc(sizeof(char) * 500);
    char char_limit[5];

    strcpy(sql,
           "SELECT count(id), group_concat(id, ','), group_concat(concat, '\t\t-----------------------------------------------\n\t\t') as result "
           "FROM (SELECT id, 'NUMERO: ' || id || '\n\t\t' || 'CLIENTE: ' || id_cliente || '\n\t\t' || 'QUARTO: ' || id_quarto || '\n\t\t' || "
           "'INICIO: ' || inicio || '\n\t\t' || 'FIM: ' || fim as concat FROM reservas ");

    if (strcmp(column, "NULL") != 0) {
        strcat(sql, " where ");
        strcat(sql, column);
        strcat(sql, "= ");
        strcat(sql, filter);
    }

    if (order_by != NULL) {
        strcat(sql, " order by ");
        strcat(sql, order_by);
    }

    if (limit > 0) {
        snprintf(char_limit, 5, "%d", limit);
        strcat(sql, " limit ");
        strcat(sql, char_limit);
    }

    strcat(sql, ");");

    int qtd_resultados = executar_sql(sql, callback, ids);

    free(sql);

    return qtd_resultados;
}

int montar_qtd(void *ptr, int resultados, char **STR1, char **STR2) {
    *((int *) ptr) = (int) strtol(STR1[0], NULL, 10);
    return 0;
}

int get_qtd_clientes() {
    int total;
    char *sql = (char *) malloc(sizeof(char) * 150);

    strcpy(sql, "select count(id) from clientes;");

    executar_sql(sql, montar_qtd, &total);
    free(sql);

    return total;
}

int get_qtd_reservas() {
    int total;
    char *sql = (char *) malloc(sizeof(char) * 150);
    strcpy(sql, "select count(id) from reservas;");
    executar_sql(sql, montar_qtd, &total);
    free(sql);

    return total;
}

int db_remover_cliente(char *column, char *filter) {
    char *sql = (char *) malloc(sizeof(char) * 150);

    strcpy(sql, "delete from clientes where ");

    if (strcmp(column, "id") == 0) {
        strcat(sql, column);
        strcat(sql, " = ");
        strcat(sql, filter);
    } else {
        strcat(sql, column);
        strcat(sql, " like '");
        strcat(sql, filter);
        strcat(sql, "' ");
    }

    strcat(sql, ";");
    executar_sql(sql, mostrar_resultados, NULL);

    free(sql);

    return 0;
}

int remover_reserva(char *column, char *filter) {
    char *sql = (char *) malloc(sizeof(char) * 150);

    strcpy(sql, "insert into reservas_inativas select * from reservas where id = ");
    strcat(sql, filter);
    strcat(sql, " ;");
    executar_sql(sql, NULL, NULL);

    strcpy(sql, "delete from reservas where id = ");
    strcat(sql, filter);
    strcat(sql, " ;");
    executar_sql(sql, NULL, NULL);

    free(sql);

    return 0;
}

int reservar_quarto(int id_quarto, int id_reserva) {
    char *sql = (char *) malloc(sizeof(char) * 200);
    char str[100];

    strcpy(sql, "insert into quartos_reservados (id_quarto, id_reserva) values(");
    snprintf(str, 10, "%d", id_quarto);
    strcat(sql, str);
    strcat(sql, ", ");
    snprintf(str, 10, "%d", id_reserva);
    strcat(sql, str);
    strcat(sql, ");");

    executar_sql(sql, NULL, NULL);
    free(sql);

    return 0;
}

int gerar_id(char *tabela, int *id) {
    char *sql = (char *) malloc(sizeof(char) * 150);

    strcpy(sql, "SELECT seq FROM SQLITE_SEQUENCE WHERE name LIKE '");
    strcat(sql, tabela);
    strcat(sql, "';");

    executar_sql(sql, montar_qtd, id);
    free(sql);

    return ++(*id);
}

int get_id_cliente() {
    int id;
    char *sql = (char *) malloc(sizeof(char) * 150);

    strcpy(sql, "SELECT id FROM clientes where clientes.id_quarto = -1;");

    executar_sql(sql, montar_qtd, &id);
    free(sql);

    return id;
}

int testar_id(int id, char *table) {
    char sql[100];
    char id_char[5];
    int ids[10] = {0};

    strcpy(sql, "select count(id) from ");
    strcat(sql, table);
    strcat(sql, " where id = ");

    snprintf(id_char, 5, "%d", id);
    strcat(sql, id_char);
    strcat(sql, ";");

    int resultado = executar_sql(sql, montar_qtd, ids);
    return resultado;
}
