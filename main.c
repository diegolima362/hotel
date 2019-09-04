#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include "libs/login.h"
#include "libs/extrafuncs.h"

#define PATHDATA "data/"
#define PATHATIVO "data/usr/.ativo"

void criar_diretorios();

int fazer_login();

void criar_login(LOGIN *login);

void tela_pegar_login(LOGIN *login);

void tela_menu();

int main(int argc, char *argv[]) {
    criar_diretorios();

    if (fazer_login() == 1)
        tela_menu();

    return 0;
}


int fazer_login() {
    LOGIN *login;
    if (existe_usuario_cadastrado() == 0) {
        criar_login(login);
    }
    tela_pegar_login(login);
    return validar_login(login);

}

void tela_menu() {
    printf("\n\n\t\t\t---- CAMPINA  CONFORT  PREMIUM ----\n\t\t\t\t");
    printf("\n\tMENU INICIAL\n");
    printf("\n\t\t(1) GERENCIAR RESERVAS\n");
    printf("\t\t  (2) GERENCIAR DADOS DO SISTEMA\n");
    printf("\t\t    (3) MANUTENCAO\n");
    printf("\n\t\t(X) SAIR\n");
    printf("\n\t\tOPÇÃO: ");
}

void tela_pegar_login(LOGIN *login) {

    printf("\nUSUARIO: ");
    limpar_teclado();
    scanf("%s", login->user);
    printf("\nSENHA: ");
    limpar_teclado();
    scanf("%s", login->senha);

}

void criar_diretorios() {
    FILE *ativo = fopen(PATHATIVO, "r+b");

    if (ativo != NULL) {
        fclose(ativo);
        return;
    }

    // criar diretorios

    mkdir(PATHDATA, 0700);
    mkdir(PATHLOGIN, 0700);

    ativo = fopen(PATHATIVO, "w+b");
    fclose(ativo);
}

void criar_login(LOGIN *login) {

    char senha_confirmacao[20];

    printf("CRIAR LOGIN\n");
    tela_pegar_login(login);

    printf("DIGITAR SENHA NOVAMENTE: ");
    scanf("%s", senha_confirmacao);

    if (strcmp(login->senha, senha_confirmacao) == 0) {
        if (gravar_dados_arquivo_login(login)) {
            printf("LOGIN CRIADO COM SUCESSO\n");
        } else {
            printf("NAO FOI POSSIVEL CRIAR O LOGIN");
        }
    } else {
        printf("SENHAS INCOMPATIVEIS\n");
        criar_login(login);
    }
}