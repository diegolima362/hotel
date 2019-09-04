//
// Created by diego on 03/09/2019.
//

#include "login.h"
#include "extrafuncs.h"

#include <stdio.h>
#include <string.h>

int existe_usuario_cadastrado() {
    FILE *teste;
    if (teste = fopen(PATHUSERFILE, "r+b")) {
        fclose(teste);
        return 1;
    }

    return 0;
}

int validar_login(LOGIN *login_comparacao) {
    LOGIN *login_certo;
    pegar_dados_arquivo_login(login_certo);

    int user_certo = strcmp(login_certo->user, login_comparacao->user);
    int senha_certa = strcmp(login_certo->senha, login_comparacao->senha);

    if (user_certo == 0 && senha_certa == 0)
        return 1;
    else
        return 0;
}

void pegar_dados_arquivo_login(LOGIN *login) {
    FILE *arquivo_login;
    arquivo_login = fopen(PATHUSERFILE, "r+b");
    fread(login, sizeof(LOGIN), 1, arquivo_login);
    fclose(arquivo_login);
}

int gravar_dados_arquivo_login(LOGIN *login) {
    FILE *arquivo_login = fopen(PATHUSERFILE, "w+b");

    int login_gravado = fwrite(login, sizeof(LOGIN), 1, arquivo_login);

    fclose(arquivo_login);

    if (login_gravado)
        return 1;
    else
        return 0;
}