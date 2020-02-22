//
// Created by Administrador on 14/11/2019.
//

#ifndef HOTEL_DATABASE_H
#define HOTEL_DATABASE_H

#endif //HOTEL_DATABASE_H

#include <time.h>

#define DB_PATH "data/hotel.db"
#define BKP_DB_PATH "data/hotel_bkp.db"

int criar_banco_de_dados();

int executar_sql(char *sql, int (*callback)(void *, int, char **, char **), void *ptr);

int criar_tabelas();

int mostrar_resultados(void *ptr, int resultados, char **STR1, char **STR2);

int db_listar_clientes(char *column, char *filter, int limit, char *order_by, void *ids,
                       int (*callback)(void *, int, char **, char **));

int db_listar_reservas(char *column, char *filter, int limit, char *order_by, void *ids,
                       int (*callback)(void *, int, char **, char **));

int montar_qtd(void *ptr, int resultados, char **STR1, char **STR2);

int get_qtd_reservas();

int db_remover_dado(char *table, char *column, char *filter);

int db_remover_reserva(char *id);

int reservar_quarto(int id_quarto, int id_reserva);

int gerar_id(char *tabela, int *id);

int testar_id(int id, char *table);

void bkp_db(int isSave);

void db_listar_dados_registrados();

void db_listar_clientes_detalhado();

void db_listar_quartos_detalhado();

int check_bkp_file();

void db_deletar_dados();

void db_reset_db();

int db_exibir_resultados(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna);