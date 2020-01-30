//
// Created by diego on 03/09/2019.
//

#include "extrafuncs.h"
#include "datas.h"

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void pausa() {
    printf("\n\t\t<ENTER> PARA CONTINUAR");
    getchar();
    getchar();
}

char *upper(char *str) {
    for (int i = 0; str[i] != '\0'; i++)
        str[i] = toupper(str[i]);

    return str;
}

void remover_quebra(char *str) {
    str[strcspn(str, "\n")] = 0;
}

void limpar_teclado() {
    setbuf(stdin, NULL);
    setbuf(stdin, NULL);
    setbuf(stdin, NULL);
}

void limpar_tela() {
    system("clear");
}

int is_in(int valor, const int *array, int tamanho) {
    for (int i = 0; i < tamanho; i++) if (array[i] == valor) return 1;
    return 0;
}

void mostrar_titulo() {
    limpar_tela();
    limpar_tela();
    printf("\n\n\t\t---- CAMPINA  COMFORT  PREMIUM ----\n\t\t\t  ");
    mostrar_data_hora();
    puts("\n");
}

char *strrstr(char *s1, char *s2) {
    char *ss1;
    char *sss1;
    char *sss2;

    if (*(s2) == '\0') {
        return s1;
    }

    ss1 = s1 + strlen(s1);

    while (ss1 != s1) {
        --ss1;

        for (sss1 = ss1, sss2 = s2;;) {
            if (*(sss1++) != *(sss2++)) {
                break;
            } else if (*sss2 == '\0') {
                return ss1;
            }
        }
    }

    return NULL;
}