//
// Created by diego on 03/09/2019.
//

#include "extrafuncs.h"

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

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