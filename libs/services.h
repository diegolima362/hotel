//
// Created by diego on 03/09/2019.
//

#include <time.h>

#ifndef HOTEL_SERVICES_H
#define HOTEL_SERVICES_H

#endif //HOTEL_SERVICES_H

typedef struct {
    int id; // identificador do serviço
    char nome[31]; // nome do serviço
    char descricao[71]; // descrição do serviço
    float valor; // preço do serviço
    time_t data; // data da realização do serviço

} SERVICE;

/**
 * mostrar detalhes de um serviço
 * @param service
 */
void mostrar_service(SERVICE service);