//
// Created by diego on 03/09/2019.
//

#include "services.h"
#include <stdio.h>

void mostrar_service(SERVICE service) {
    printf("\n\t\tID: %d\n\n", service.id);
    printf("\t\tNOME: %s\n", service.nome);
    printf("\n\t\t    %s\n", service.descricao);
    printf("\n\t\tVALOR: R$ %.2f\n\n", service.valor);
    printf("\t\t--------------------------------------------------------------------\n");
}
