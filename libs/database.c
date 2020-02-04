//
// Created by Administrador on 14/11/2019.
//
#include "database.h"
#include "datas.h"
#include "extrafuncs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sqlite3.h>

/*
 * author: https://www.sqlite.org/backup.html
 */
int loadOrSaveDb(sqlite3 *pInMemory, const char *zFilename, int isSave);

int criar_banco_de_dados() {
    FILE *db = fopen(DB_PATH, "r+b");
    int criacao__banco_dados = 0;

    if (db == NULL) {

        db = fopen(DB_PATH, "w+b");

        fclose(db);

        printf("\n\n\t\tCRIANDO BANCO DE DADOS ... \n");
        criar_tabelas();

        criacao__banco_dados = 1;

    } else { fclose(db); }

    return criacao__banco_dados;
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

    puts("REGISTRANDO QUARTOS ...");
    criar_quartos(20, "insert into quartos values (null, 1, 'Executivo triplo', 440);", db);
    criar_quartos(15, "insert into quartos values (null, 2, 'Executivo duplo', 385);", db);
    criar_quartos(5, "insert into quartos values (null, 3, 'Executivo simples', 360);", db);
    criar_quartos(20, "insert into quartos values (null, 4, 'Luxo triplo', 620);", db);
    criar_quartos(15, "insert into quartos values (null, 5, 'Luxo duplo', 570);", db);
    criar_quartos(5, "insert into quartos values (null, 6, 'Luxo simples', 520);", db);
    criar_quartos(5, "insert into quartos values (null, 7, 'Presidencial', 1200);", db);
    puts("QUARTOS OK");

    puts("REGISTRANDO SERVICOS!");
    // servicos basicos
    char *sql = "insert into servicos values (null, 'Babysitter hora', 45); "
                "insert into servicos values (null, 'Diaria de automovel luxo', 100);"
                "insert into servicos values (null, 'Diaria de automovel executivo', 60);"
                "insert into servicos values (null, 'Tanque cheio', 300);"
                "insert into servicos values (null, 'Carro assegurado', 250);";
    puts("SERVICOS OK!");
    executar_sql(sql, NULL, NULL);

}

int criar_tabelas() {
    char *error_msg, *error_msg1, *error_msg2;
    sqlite3 *db;
    sqlite3_open(DB_PATH, &db);

    char *table_clientes = "create table clientes ( "
                           "id integer constraint clientes_pk primary key autoincrement, "
                           "nome text, sobrenome text, cpf text, phone text, "
                           "id_quarto integer default 0 constraint clientes_id_quarto_fk  references reservas (id_quarto), "
                           "id_reserva integer default 0 constraint clientes_id_reserva_fk references reservas);"
                           "create unique index clientes_id_uindex on clientes (id);";

    char *table_quartos = "create table quartos ( "
                          "id integer constraint quarto_pk primary key autoincrement, tipo integer, "
                          "descricao char(15), valor real);"
                          "create unique index quartos_id_uindex on quartos (id);";

    char *table_quartos_reservados = "create table quartos_reservados( "
                                     "id integer constraint quartos_registrados_pk primary key autoincrement, "
                                     "id_quarto  integer default 0 constraint quartos_registrados_id_quarto_fk references reservas (id_quarto), "
                                     "id_reserva integer default 0 references reservas);"
                                     "create unique index quartos_registrados_is_uindex on quartos_reservados (id);";

    char *table_reservas = "create table reservas ( "
                           "id integer constraint reservas_pk primary key autoincrement, "
                           "id_cliente integer constraint reservas_clientes_id_fk references clientes, "
                           "id_quarto integer constraint reservas_quartos_id_fk references quartos, "
                           "inicio text, fim text ); "
                           "create unique index reservas_id_uindex on reservas (id);";

    char *table_reservas_inativas = "create table reservas_inativas( "
                                    "id integer constraint reservas_inativas_pk primary key autoincrement, "
                                    "id_cliente integer constraint reservas_inativas_clientes_id_fk references clientes, "
                                    "id_quarto integer constraint reservas_inativas_quartos_id_fk references quartos, "
                                    "inicio text, fim text ); "
                                    "create unique index reservas_inativas_id_uindex on reservas_inativas (id);";

    char *tables_servicos = "create table servicos (id integer constraint servicos_pk primary key autoincrement, descricao text, valor real); "
                            "create unique index servicos_id_uindex on servicos (id);";

    char *tables_pedidos = "create table pedidos (id integer constraint pedidos_pk primary key autoincrement, id_reserva integer constraint pedidos_reservas_id_fk references reservas, data text);"
                           "create unique index pedidos_id_uindex on pedidos (id);";

    char *tables_detalhes = "create table detalhes_pedido (id integer constraint detalhes_pedido_pk primary key autoincrement, id_pedido  integer constraint detalhes_pedido_pedidos_id references pedidos, id_servico integer constraint detalhes_pedido_servicos_id references servicos, quantidade integer); "
                            "create unique index detalhes_pedido_id_uindex on detalhes_pedido (id);";

    int created;

    if (sqlite3_exec(db, table_clientes, NULL, NULL, &error_msg) == SQLITE_OK &&
        sqlite3_exec(db, table_quartos, NULL, NULL, &error_msg1) == SQLITE_OK &&
        sqlite3_exec(db, table_quartos_reservados, NULL, NULL, &error_msg1) == SQLITE_OK &&
        sqlite3_exec(db, table_reservas, NULL, NULL, &error_msg2) == SQLITE_OK &&
        sqlite3_exec(db, table_reservas_inativas, NULL, NULL, &error_msg2) == SQLITE_OK &&
        sqlite3_exec(db, tables_servicos, NULL, NULL, &error_msg2) == SQLITE_OK &&
        sqlite3_exec(db, tables_pedidos, NULL, NULL, &error_msg2) == SQLITE_OK &&
        sqlite3_exec(db, tables_detalhes, NULL, NULL, &error_msg2) == SQLITE_OK) {
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

    char *sql = (char *) malloc(sizeof(char) * 1000);
    char char_limit[5];

    strcpy(sql,
           "SELECT count(id), group_concat(id, ','), group_concat(concat, '\n\t\t-----------------------------------------------\n\t\t') as result "
           "FROM (SELECT id, 'RESERVA: ' || id || '\n\t\t' || 'CLIENTE: ' || id_cliente || '\n\t\t' || 'QUARTO: ' || id_quarto || '\n\t\t' || "
           "'INICIO: ' || inicio || '\n\t\t' || 'FIM: ' || fim as concat FROM reservas");

    if (strcmp(column, "inativa") == 0) {
        strcat(sql, "_inativas ");

    } else if (strcmp(column, "NULL") != 0) {
        strcat(sql, " where ");

        if (strcmp(column, "data") == 0) {
            char inicio[15], fim[15];
            char *pt = strtok(filter, ",");

            strcpy(inicio, pt);
            pt = strtok(NULL, "\0");
            strcpy(fim, pt);

            strcat(sql, " (inicio <= '");
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
            strcat(sql, "' >= inicio) ");

        } else {
            strcat(sql, column);
            strcat(sql, "= ");
            strcat(sql, filter);
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

int db_remover_dado(char *table, char *column, char *filter) {
    char *sql = (char *) malloc(sizeof(char) * 150);

    strcpy(sql, "delete from ");
    strcat(sql, table);
    strcat(sql, " where ");

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

int db_remover_reserva(char *id) {
    char *sql = (char *) malloc(sizeof(char) * 150);

    strcpy(sql, "insert into reservas_inativas select * from reservas where id = ");
    strcat(sql, id);
    strcat(sql, " ;");
    executar_sql(sql, NULL, NULL);

    strcpy(sql, "delete from reservas where id = ");
    strcat(sql, id);
    strcat(sql, " ;");
    executar_sql(sql, NULL, NULL);

    strcpy(sql, "delete from quarto_registrados where id_reserva = ");
    strcat(sql, id);
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

void bkp_db(int isSave) {
    sqlite3 *db;

    if (isSave == -1) {
        remove(BKP_DB_PATH);
        return;
    }

    if (check_bkp_file() == 0) {
        FILE *bkp = fopen(BKP_DB_PATH, "w+b");
        fclose(bkp);
    }

    sqlite3_open(DB_PATH, &db);
    loadOrSaveDb(db, BKP_DB_PATH, isSave);
    sqlite3_close(db);
}

int loadOrSaveDb(sqlite3 *pInMemory, const char *zFilename, int isSave) {
    int rc;
    sqlite3 *pFile;
    sqlite3_backup *pBackup;
    sqlite3 *pTo;
    sqlite3 *pFrom;

    rc = sqlite3_open(zFilename, &pFile);
    if (rc == SQLITE_OK) {

        pFrom = (isSave ? pInMemory : pFile);
        pTo = (isSave ? pFile : pInMemory);

        pBackup = sqlite3_backup_init(pTo, "main", pFrom, "main");
        if (pBackup) {
            (void) sqlite3_backup_step(pBackup, -1);
            (void) sqlite3_backup_finish(pBackup);
        }
        rc = sqlite3_errcode(pTo);
    }

    (void) sqlite3_close(pFile);
    return rc;
}

int db_exibir_resultados(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna) {

    for (int i = 0; i < qtd_colunas; i++) {
        upper(valor_na_coluna[i]);
        printf("\t\t%s\n", valor_na_coluna[i]);
    }

    return 0;
}

void db_listar_dados_registrados() {
    char sql[500];
    strcpy(sql,
           "SELECT group_concat(concat, '\t\t-----------------------------------------------\n\t\t') AS result "
           "FROM (SELECT IFNULL(id, 0) id, 'CLIENTES REGISTRADOS: ' || count(c.id) AS concat FROM clientes c);");
    executar_sql(sql, db_exibir_resultados, NULL);

    strcpy(sql,
           "SELECT group_concat(concat, '\t\t-----------------------------------------------\n\t\t') AS result "
           "FROM (SELECT IFNULL(id, 0) id, 'RESERVAS ATIVAS: ' || count(r.id) AS concat FROM reservas r);");
    executar_sql(sql, db_exibir_resultados, NULL);

    strcpy(sql,
           "SELECT group_concat(concat, '\t\t-----------------------------------------------\n\t\t') AS result "
           "FROM (SELECT IFNULL(id, 0) id, 'RESERVAS FINALIZADAS: ' || count(r.id) AS concat FROM reservas_inativas r);");
    executar_sql(sql, db_exibir_resultados, NULL);

    strcpy(sql,
           "SELECT group_concat(upper(concat), '\\t\\t-----------------------------------------------\\n\\t\\t') as result "
           "FROM (SELECT 'QUARTOS COM RESERVAS ATIVAS: ' || count(ids) AS concat FROM (SELECT DISTINCT q.id_quarto as ids "
           "FROM quartos_reservados q JOIN reservas r ON q.id_reserva=r.id));");
    executar_sql(sql, db_exibir_resultados, NULL);
}

void db_listar_clientes_detalhado() {
    char sql[500];
    strcpy(sql,
           "SELECT group_concat(concat, '\t\t-----------------------------------------------\n\t\t') as result "
           "FROM (SELECT 'ID CLIENTE: ' || c.id || '\n\t\t' || 'NOME: ' || c.nome || ' ' || c.sobrenome || '\n\t\t' || 'QUARTO: ' || r.id_quarto ||"
           "'\n\t\t' || 'CPF: ' || c.cpf || '\n\t\t' || 'PHONE: ' || c.phone || "
           "r.id_quarto || '\n\t\t' || 'PERIODO DA RESERVA: ' || r.inicio || ' - ' || r.fim as concat FROM clientes c JOIN reservas r on c.id_reserva = r.id);");

    executar_sql(sql, db_exibir_resultados, NULL);
}

void db_listar_quartos_detalhado() {
    char sql[500];
    strcpy(sql,
           "SELECT group_concat(concat, '\t\t-----------------------------------------------\n\t\t') as result "
           "FROM (SELECT 'NUM QUARTO: ' || q.id_quarto || '\n\t\t' || 'ID CLIENTE: ' || r.id_cliente || '\n\t\t' || 'PERIODO DA RESERVA: ' || r.inicio || ' - ' || r.fim as concat "
           "FROM quartos_reservados q JOIN reservas r on r.id_quarto = q.id_quarto);");
    executar_sql(sql, db_exibir_resultados, NULL);
}

int check_bkp_file() {
    FILE *ativo = fopen(BKP_DB_PATH, "r+b");

    if (ativo == NULL) {
        return 0;
    } else {
        fclose(ativo);
        return 1;;
    }
}

void db_deletar_dados() {
    char sql[100];

    strcpy(sql, "delete from clientes");
    executar_sql(sql, NULL, NULL);

    strcpy(sql, "delete from reservas");
    executar_sql(sql, NULL, NULL);

    strcpy(sql, "delete from reservas_inativas");
    executar_sql(sql, NULL, NULL);

    strcpy(sql, "delete from quartos");
    executar_sql(sql, NULL, NULL);

    strcpy(sql, "delete from quartos_reservados");
    executar_sql(sql, NULL, NULL);
}

void db_reset_db() {
    remove(DB_PATH);
    criar_banco_de_dados();
}