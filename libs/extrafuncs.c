//
// Created by diego on 03/09/2019.
//

#include "extrafuncs.h"

#include <string.h>
#include <ctype.h>
#include <stdio.h>

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
    int i = 0;
    while (i < 10) {
        printf("\n\n\n");
        i++;
    }

}