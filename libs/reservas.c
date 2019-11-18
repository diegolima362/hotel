//
// Created by Diego on 02/11/2019.
//

#include "reservas.h"
#include <stdlib.h>
#include <time.h>

RESERVA *criar_reserva(int id, int status, int id_cliente) {
    RESERVA *r = (RESERVA *) calloc(1, sizeof(RESERVA));
    r->id = id;
    r->status = status;
    r->id_cliente = id_cliente;
    return r;
}

CLIENTE *criar_cliente() {
    CLIENTE *c = (CLIENTE *) calloc(1, sizeof(CLIENTE));
    return c;
}