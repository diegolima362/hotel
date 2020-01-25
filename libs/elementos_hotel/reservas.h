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

void teste_reserva();

void exibir_menu_gerenciar_reservas();