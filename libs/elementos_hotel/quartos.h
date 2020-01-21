//
// Created by diego on 07/01/2020.
//

#ifndef HOTEL_QUARTOS_H
#define HOTEL_QUARTOS_H

#endif //HOTEL_QUARTOS_H

#include <bits/types/struct_tm.h>
#include "../datas.h"

int mostrar_quartos_disponiveis(struct tm *data_inicio, struct tm *data_final, int tipo, int *index);

int selecionar_quarto(struct tm *data_inicio, struct tm *data_final, int *id_quarto);

int selecionar_tipo_quarto();

int busca_quarto(char *coluna, char *valor, int *ids);