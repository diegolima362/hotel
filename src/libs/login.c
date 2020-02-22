//
// Created by diego on 03/09/2019.
//

#include "login.h"
#include "extrafuncs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int autenticar() {
    LOGIN *login = (LOGIN *) calloc(1, sizeof(LOGIN *));

    if (existe_usuario_cadastrado() == 0) {
        criar_login(login);
    }
    limpar_tela();
    printf("\n\t\tINSIRA O LOGIN E SENHA\n\n");
    tela_pegar_login(login);

    int status = validar_login(login);
    free(login);

    return status;
}

int criar_login(LOGIN *login) {

    char senha_confirmacao[21];

    printf("\n\n\n\tCADASTRAR ADMIN: ");
    tela_pegar_login(login);

    printf("\n\n\n\tINSIRA A SENHA NOVAMENTE: ");
    fgets(senha_confirmacao, 21, stdin);
    remover_quebra(senha_confirmacao);

    if (strcmp(login->pwd, senha_confirmacao) == 0) {
        if (gravar_dados_arquivo_login(login)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        printf("\n\n\t\t\tSENHAS INCOMPATIVEIS !!!\n");
        pausa();
        return criar_login(login);
    }
}

void alterar_login() {
    LOGIN *login = (LOGIN *) calloc(1, sizeof(LOGIN *));
    if (criar_login(login)) {

    }
}

void tela_pegar_login(LOGIN *login) {
    printf("\n\n\n\t\t\tUSUARIO: ");
    limpar_teclado();
    fgets(login->usr, 21, stdin);
    remover_quebra(login->usr);
    printf("\n\t\t\tSENHA: ");
    limpar_teclado();
    fgets(login->pwd, 21, stdin);
    remover_quebra(login->pwd);
}

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
