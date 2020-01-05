//
// Created by diego on 03/09/2019.
//

#ifndef HOTEL_LOGIN_H
#define HOTEL_LOGIN_H

#endif //HOTEL_LOGIN_H

#define PATH_LOGIN "data/usr/"
#define PATH_USER_FILE "data/usr/data.pwd"

typedef struct {
    char usr[21];
    char pwd[21];
} LOGIN;

int existe_usuario_cadastrado();

int validar_login(LOGIN *login_comparacao);

void pegar_dados_arquivo_login(LOGIN *login);

int gravar_dados_arquivo_login(LOGIN *login);