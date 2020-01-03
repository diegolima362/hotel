//
// Created by Diego on 02/11/2019.
//

#ifndef HOTEL_RESERVAS_H
#define HOTEL_RESERVAS_H

#endif //HOTEL_RESERVAS_H

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

RESERVA *criar_reserva(int id, int status, int id_cliente);

CLIENTE *criar_cliente();

void inserir_contrato();

void alterar_contrato();

void remover_contrato();
