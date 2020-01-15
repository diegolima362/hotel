//
// Created by diego on 07/01/2020.
//

#include <bits/types/struct_tm.h>

#include "../datas.h"
#include "clientes.h"

#ifndef HOTEL_RESERVAS_H
#define HOTEL_RESERVAS_H

#endif //HOTEL_RESERVAS_H

typedef struct reserva {
    int id;
    int status;
    int id_cliente;
    int id_quarto;
    struct tm inicio;
    struct tm fim;
} RESERVA;

void inserir_data_reserva(struct tm *data_inicio, struct tm *data_final);

void criar_nova_reserva(CLIENTE *c);

void mostrar_reserva(RESERVA *r, CLIENTE *c);

int busca_reserva(char *coluna, char *valor, int *ids);

char* formatar_reserva(RESERVA *r);

void exibir_qtd_reservas();

void buscar_reserva();