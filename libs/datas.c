//
// Created by Diego on 02/11/2019.
//
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datas.h"

struct tm *ler_data() {
    struct tm *date;
    time_t t = time(NULL);
    date = localtime(&t);
    return date;
}

struct tm *formatar_data_struct(struct tm *date, char *str) {
    const char s[2] = "-";
    int i;
    int campos[3];
    char *token;

    token = strtok(str, s);
    i = 0;
    while (token != NULL) {
        campos[i] = (int) strtol(token, NULL, 10);
        token = strtok(NULL, s);
        i++;
    }

    date->tm_year = campos[0];
    date->tm_mon = campos[1];
    date->tm_mday = campos[2];

    return date;
}

char *formatar_data_sql(struct tm *date, char *str) {
    char campo[5];

    // ano
    snprintf(campo, 5, "%d", date->tm_year);
    strcpy(str, campo);
    strcat(str, "-");

    // mes
    snprintf(campo, 3, "%d", date->tm_mon);
    strcat(str, campo);
    strcat(str, "-");

    // dia
    snprintf(campo, 3, "%d", date->tm_mday);
    strcat(str, campo);;

    return str;
}