//
// Created by Administrador on 14/11/2019.
//

#ifndef HOTEL_DATABASE_H
#define HOTEL_DATABASE_H

#endif //HOTEL_DATABASE_H

#include <time.h>

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
    char nome[100 + 1];
    char cpf[15];
    char cred_card[30];
    char phone[20];
    struct end end;
    int ativo;
} CLIENTE;

typedef struct reserva {
    int id;
    int status;
    int id_cliente;
    int id_quarto;
    time_t inicio;
    time_t fim;
} RESERVA;

char *executar_query(char *query, int (*callback)(void *, int, char **, char **));

int inserir_cliente(CLIENTE *c);

int mostrar_clientes(void *ptr, int resultados, char **STR1, char **STR2);

int listar_clientes(char *filtro, int limit);

int montar_cliente(void *ptr, int resultados, char **STR1, char **STR2);

int recuperar_clientes(CLIENTE *c);

int buscar_cliente(char *column, char *filter, int limit);

int montar_qtd(void *ptr, int resultados, char **STR1, char **STR2);

int qtd_clientes();

int remover_cliente(char *column, char *filter);

int inserir_reserva(RESERVA *r);
