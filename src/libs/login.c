//
// Created by diego on 03/09/2019.
//

#include "login.h"
#include "extrafuncs.h"
#include "database.h"

#include <stdio.h>
#include <string.h>

int autenticar() {
    LOGIN login;
    limpar_tela();
    if (existe_usuario_cadastrado() == 0) {
        criar_login(&login);
    }

    mostrar_titulo();
    printf("\n\t\tINSIRA O LOGIN E SENHA\n");
    tela_pegar_login(&login);

    int status = validar_login(&login);

    return status;
}

int criar_login(LOGIN *login) {

    char senha_confirmacao[21];

    mostrar_titulo();
    printf("\n\n\n\tCADASTRAR ADMIN: ");
    tela_pegar_login(login);

    printf("\n\n\n\tINSIRA A SENHA NOVAMENTE: ");
    fgets(senha_confirmacao, 21, stdin);
    remover_quebra(senha_confirmacao);

    if (strcmp(login->pwd, senha_confirmacao) == 0) {
        if (db_gravar_login(login->usr, login->pwd)) {
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
    LOGIN login;

    mostrar_titulo();
    printf("\n\t\tLOGIN ATUAL\n");
    tela_pegar_login(&login);

    if (validar_login(&login) == 0) {
        printf("\n\n\t\tLOGIN INCORRETO!\n");
        pausa();
        return;
    }

    mostrar_titulo();
    printf("\n\t\tNOVO LOGIN\n");
    tela_pegar_login(&login);
    printf("\n\t\t(1) CONFIRMAR (0) CANCELAR : ");
    int op;
    scanf(" %d", &op);
    if (op == 1) {
        db_alterar_dados_login(login.usr, login.pwd);
        mostrar_titulo();
        printf("\n\t\tLOGIN ALTERADO!\n");
        pausa();
        return;
    } else {
        printf("\n\n\t\t\tCANCELADO!\n");
        pausa();
        return;
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


int validar_login(LOGIN *login_comparacao) {
    LOGIN login_certo;

    db_montar_dados_login(login_certo.usr, login_certo.pwd);

    int user_certo = strcmp(login_certo.usr, login_comparacao->usr);
    int senha_certa = strcmp(login_certo.pwd, login_comparacao->pwd);

    if (user_certo == 0 && senha_certa == 0)
        return 1;
    else
        return 0;
}
