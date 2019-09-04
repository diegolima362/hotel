//
// Created by diego on 03/09/2019.
//

#ifndef HOTEL_LOGIN_H
#define HOTEL_LOGIN_H

#endif //HOTEL_LOGIN_H

#define PATHLOGIN "data/usr/"
#define PATHUSERFILE "data/usr/hotel.psswd"

typedef struct {
    char user[20];
    char senha[20];
} LOGIN;

int validar_login(LOGIN *login_comparacao);

int existe_usuario_cadastrado();

void pegar_dados_arquivo_login(LOGIN *login);

int gravar_dados_arquivo_login(LOGIN *login);
