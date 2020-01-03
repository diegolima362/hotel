//
// Created by diego on 03/09/2019.
//

#include "login.h"
#include "extrafuncs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int existe_usuario_cadastrado() {
    FILE *test = fopen(PATH_USER_FILE, "r+b");

    if (test) {
        fclose(test);
        return 1;
    }

    return 0;
}

int validar_login(LOGIN *login_comparacao) {
    LOGIN *login_certo = (LOGIN *) calloc(1, sizeof(LOGIN *));
    pegar_dados_arquivo_login(login_certo);

    int user_certo = strcmp(login_certo->usr, login_comparacao->usr);
    int senha_certa = strcmp(login_certo->pwd, login_comparacao->pwd);

    free(login_certo);

    if (user_certo == 0 && senha_certa == 0)
        return 1;
    else
        return 0;
}

void pegar_dados_arquivo_login(LOGIN *login) {
    FILE *arquivo_login;
    arquivo_login = fopen(PATH_USER_FILE, "r+b");
    fread(login, sizeof(LOGIN), 1, arquivo_login);
    fclose(arquivo_login);
}

int gravar_dados_arquivo_login(LOGIN *login) {
    FILE *arquivo_login = fopen(PATH_USER_FILE, "w+b");

    int login_gravado = (int) fwrite(login, sizeof(LOGIN), 1, arquivo_login);

    fclose(arquivo_login);

    if (login_gravado)
        return 1;
    else
        return 0;
}