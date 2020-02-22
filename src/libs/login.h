//
// Created by diego on 03/09/2019.
//

#ifndef HOTEL_LOGIN_H
#define HOTEL_LOGIN_H

#endif //HOTEL_LOGIN_H

#if defined(_WIN32)
#define PATH_USER_FILE "data\\usr\\datawin.pwd"
#else
#define PATH_USER_FILE "data/usr/dataunix.pwd"
#endif

typedef struct {
    char usr[21];
    char pwd[21];
} LOGIN;

int autenticar();

int criar_login(LOGIN *login);

void alterar_login();

void tela_pegar_login(LOGIN *login);

int validar_login(LOGIN *login_comparacao);
