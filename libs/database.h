//
// Created by Administrador on 14/11/2019.
//

#ifndef HOTEL_DATABASE_H
#define HOTEL_DATABASE_H

#endif //HOTEL_DATABASE_H

#include <time.h>

#define DB_PATH "data/hotel.db"
#define str_null "NULL"

typedef struct quarto {
    int id;
    int tipo;
    char descricao[18];
    float valor;
} QUARTO;

int executar_sql(char *sql, int (*callback)(void *, int, char **, char **), void *ptr);

int criar_banco();

int mostrar_resultados(void *ptr, int resultados, char **STR1, char **STR2);

int
db_listar_quartos_reservar(char *inicio, char *fim, int ocupado, void *ids,
                           int (*callback)(void *, int, char **, char **));

int db_listar_clientes(char *column, char *filter, int limit, char *order_by, void *ids,
                       int (*callback)(void *, int, char **, char **));

int db_listar_reservas(char *column, char *filter, int ativa, int limit, char *order_by, void *ids,
                       int (*callback)(void *, int, char **, char **));

int montar_qtd(void *ptr, int resultados, char **STR1, char **STR2);

int get_qtd_reservas();

int db_remover_cliente(char *column, char *filter);

int remover_reserva(char *column, char *filter);

int reservar_quarto(int id_quarto, int id_reserva);

int gerar_id(char *tabela, int *id);

int get_id_cliente();

int testar_id(int id, char *table);