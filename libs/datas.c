//
// Created by Diego on 02/11/2019.
//
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datas.h"

struct tm ler_data() {
    struct tm date;
    time_t t = time(NULL);
    date = *localtime(&t);
    date.tm_year += 1900;
    date.tm_mon += 1;
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
    if (date->tm_mon < 10)
        strcat(str, "0");
    strcat(str, campo);
    strcat(str, "-");

    // dia
    snprintf(campo, 3, "%d", date->tm_mday);
    if (date->tm_mday < 10)
        strcat(str, "0");
    strcat(str, campo);;

    return str;
}

int comparar_data(struct tm *time_1, struct tm *time_2) {
    char inicio[15];
    char final[15];

    formatar_data_sql(time_1, inicio);
    formatar_data_sql(time_2, final);
    puts(inicio);
    puts(final);
    int comp = strcmp(inicio, final);
    printf("\nComp %d\n", comp);
    // comparar datas no formato "yyyy-mm-dd"
    return comp;
}

int bissexto(int ano) { return (((ano % 4 == 0) && (ano % 100 != 0)) || (ano % 400 == 0)) ? 1 : 0; }

int validar_data(struct tm *date) {
    int year = date->tm_year;
    int mon = date->tm_mon;
    int day = date->tm_mday;
    struct tm t = ler_data();

    if ((year < t.tm_year) ||
        (mon < 1 || mon > 12) ||
        (day < 1 || day > 31))
        return 0;

    // fevereiro
    if (mon == 2) {
        if (bissexto(year)) return (day <= 29);
        else return (day <= 28);
    }

    // meses com 30 dias
    if (mon == 4 || mon == 6 || mon == 9 || mon == 11) return (day <= 30);

    return 1;
}

int validar_periodo(struct tm *data_inicio, struct tm *data_final) {

    if (validar_data(data_inicio) != 1 || validar_data(data_final) != 1) return 0;

    return comparar_data(data_inicio, data_final) > 0 ? 0 : 1;
}