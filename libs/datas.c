//
// Created by Diego on 02/11/2019.
//
#include <time.h>
#include <stdlib.h>
#include "datas.h"

DATE *ler_data() {
    DATE *date;
    time_t t = time(NULL);
    date = localtime(&t);
    return date;
}