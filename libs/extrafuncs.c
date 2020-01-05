//
// Created by diego on 03/09/2019.
//

#include "extrafuncs.h"

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void pausa() {
    printf("\n\t\t<ENTER> PARA CONTINUAR");
    getchar();
    getchar();
}

void upper(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
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