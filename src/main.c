#if defined(_WIN32)

#include <io.h>

#define PATH_ATIVO "data\\usr\\.ativowin"
#else

#include <sys/stat.h>

#define PATH_ATIVO "data/usr/.ativounix"
#endif

#include <stdio.h>
#include <stdlib.h>
#include "libs/database.h"
#include "libs/extrafuncs.h"
#include "libs/login.h"
#include "libs/home.h"

int checar_diretorios();

int main(int argc, char *argv[]) {

    if (checar_diretorios() == 1 && criar_banco_de_dados() == 1) {
        mostrar_titulo();
        printf("\n\n\t\tBASE DE DADOS CRIADA ...\n\t\tEXECUTE O PROGRAMA NOVAMENTE\n\n");
        exit(0);
    }

    if (autenticar()) {
        exibir_menu_principal();
    } else {
        mostrar_titulo();
        printf("\n\t\tLOGIN INVALIDO! FINALIZANDO ...\n");
        pausa();
    }

    return 0;
}

int checar_diretorios() {
    FILE *ativo = fopen(PATH_ATIVO, "r+b");
    int criacao_de_diretorios = 0;

    if (ativo == NULL) {

#if defined(_WIN32)
        _mkdir("data\\");
        _mkdir("data\\usr\\");
        _mkdir("data\\faturas\\");
#else
        mkdir("data/", 0700);
        mkdir("data/usr/", 0700);
        mkdir("data/faturas/", 0700);
#endif

        ativo = fopen(PATH_ATIVO, "w+b");

        criacao_de_diretorios = 1;
    }


    fclose(ativo);

    return criacao_de_diretorios;
}
