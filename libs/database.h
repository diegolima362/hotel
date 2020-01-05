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

typedef struct end {
    char rua[60 + 1];
    int num;
    char bairro[60 + 1];
    char cidade[60 + 1];
    char estado[30 + 1];
    char pais[30 + 1];
} ENDERECO;

typedef struct cliente {
    int id;
    int id_reserva;
    int id_quarto;
    char nome[31];
    char sobrenome[31];
    char cpf[15];
    char cred_card[20];
    char phone[15];
    //struct end end;
    //int ativo;
} CLIENTE;

typedef struct reserva {
    int id;
    int status;
    int id_cliente;
    int id_quarto;
    struct tm inicio;
    struct tm fim;
} RESERVA;

int retorno(void *ptr, int resultados, char **STR1, char **STR2);

void teste_int();

char *executar_sql(char *sql, int (*callback)(void *, int, char **, char **), void *ptr);

int criar_banco();

int mostrar_resultados(void *ptr, int resultados, char **STR1, char **STR2);

int listar_quartos_ocupados(char *inicio, char *fim, char *tipo, int ocupado,
                            int (*callback)(void *, int, char **, char **), int *index);

int listar_clientes(char *column, char *filter, int limit, void *ptr, int(*callback)(void *, int, char **, char **));

int listar_reservas(char *column, char *filter, int limit, void *ptr, int(*callback)(void *, int, char **, char **));

int listar_quartos(char *column, char *filter, int limit, void *ptr, int(*callback)(void *, int, char **, char **));

int montar_cliente(void *ptr, int resultados, char **STR1, char **STR2);

CLIENTE *recuperar_clientes(CLIENTE *c, char *id);

int montar_qtd(void *ptr, int resultados, char **STR1, char **STR2);

int get_qtd_reservas();

int remover_cliente(char *column, char *filter);

int remover_reserva(char *column, char *filter);

int registrar_cliente(CLIENTE *c);

int reservar_quarto(int id_quarto, int id_reserva);

int registrar_reserva(RESERVA *r);

int gerar_id(char *tabela, int *id);

int get_id_cliente();