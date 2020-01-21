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


int retorno(void *ptr, int resultados, char **STR1, char **STR2);

void teste_int();

int criar_banco();

int mostrar_resultados(void *ptr, int resultados, char **STR1, char **STR2);

int listar_quartos_ocupados(char *inicio, char *fim, char *tipo, int ocupado, int *ids,
                            int (*callback)(void *, int, char **, char **));

int db_listar_clientes(char *column, char *filter, int limit, char *order_by, void *ids,
                       int (*callback)(void *, int, char **, char **));

int db_listar_reservas(char *column, char *filter, int limit, void *ids, int(*callback)(void *, int, char **, char **));

int db_listar_quartos(char *column, char *filter, int limit, void *ids, int(*callback)(void *, int, char **, char **));

int montar_qtd(void *ptr, int resultados, char **STR1, char **STR2);

int get_qtd_reservas();

int remover_cliente(char *column, char *filter);

int remover_reserva(char *column, char *filter);

int registrar_cliente(char *cliente_formatado);

int reservar_quarto(int id_quarto, int id_reserva);

int registrar_reserva(char *reserva_formatada);

int gerar_id(char *tabela, int *id);

int get_id_cliente();