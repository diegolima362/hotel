//
// Created by diego on 07/01/2020.
//

#if defined(_WIN32)
#define PATH_FATURA "data\\faturas\\"
#else
#define PATH_FATURA "data/faturas/"
#endif

#include <time.h>
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

void exibir_menu_gerenciar_reservas();

int selecionar_reserva();