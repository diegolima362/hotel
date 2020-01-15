#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "libs/extrafuncs.h"
#include "libs/login.h"
#include "libs/datas.h"
#include "libs/browserdb.h"
#include "libs/database.h"
#include "libs/elementos_hotel/reservas.h"

void exibir_menu_principal();

void exibir_menu_reservas();

void exibir_menu_clientes();

void exibir_menu_quartos();

void exibir_menu_servicos();

void exibir_menu_configuracoes();

void exibir_menu_dados_sistema();

// menus de busca

void exibir_menu_busca_cliente();

// diretorios e base de dados

int criar_banco_de_dados();

int checar_diretorios();

int main(int argc, char *argv[]) {

//    if (checar_diretorios() == 1 && criar_banco_de_dados() == 1) {
//        printf("\n\n\t\tBASE DE DADOS CRIADA ...\n\t\tEXECUTE O PROGRAMA NOVAMENTE\n\n");
//        exit(0);
//    }
//
//    if (autenticar()) {
//        exibir_menu_principal();
//    }
    int id[10] = {0};
    int qtd = db_listar_clientes("id_reserva", "1", 10, id, exibir_resultados);

    printf("\n\n resutados %d\n\n", qtd);

    for (int i = 1; i <= qtd; i++) {
        printf("%d, ", id[i]);
    }

    return 0;
}

void exibir_menu_principal() {

    int opcao;

    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tMENU INICIAL\n");
        printf("\n\t\t(1) GERENCIAR RESERVAS\n");
        printf("\n\t\t (2) GERENCIAR CLIENTES\n");
        printf("\n\t\t  (3) GERENCIAR QUARTOS\n");
        printf("\n\t\t   (4) GERENCIAR SERVICOS\n");
        printf("\n\t\t    (5) GERENCIAR DADOS DO SISTEMA\n");
        printf("\n\t\t     (7) MANUTENCAO\n");
        printf("\n\t\t(0) SAIR\n");
        printf("\n\t\tOPÇÃO: ");
        limpar_teclado();
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                limpar_tela();
                exibir_menu_reservas();
                break;
            case 2:
                limpar_tela();
                exibir_menu_dados_sistema();
                break;
            case 3:
                limpar_tela();
                exibir_menu_configuracoes();
                break;
            case 0:
                limpar_tela();
                printf("SAINDO...\n\n");
                exit(0);

            default:
                printf("\n\nOPCAO INVALIDA!\n\n");
                pausa();
                break;
        }
    } while (opcao != 0);
}

void exibir_menu_reservas() {
    int opcao;
    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tRESERVAS\n\n");
        printf("\t\t(1) NOVA RESERVA\n");
        printf("\t\t (2) EDITAR RESERVA\n");
        printf("\t\t  (3) ENCERRAR RESERVA\n\n");
        printf("\t\t   (4) BUSCAR RESERVA\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                criar_nova_reserva(NULL);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                limpar_tela();
                break;
            case 0:
                return;
            default:
                printf("\n\nOPCAO INVALIDA!\n\n");
                pausa();
                break;
        }
    } while (opcao != 0);
}

void exibir_menu_clientes() {
    int opcao;
    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tCLIENTES\n\n");
        printf("\t\t(1) NOVO CLIENTE\n");
        printf("\t\t (2) EDITAR CLIENTE\n");
        printf("\t\t  (3) REMOVER CLIENTE\n\n");
        printf("\t\t   (4) BUSCAR CLIENTE\n\n");
        printf("\t\t    (4) LISTAR CLIENTES\n\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                criar_novo_cliente();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                limpar_tela();
                break;
            case 0:
                return;
            default:
                printf("\n\nOPCAO INVALIDA!\n\n");
                pausa();
                break;
        }
    } while (opcao != 0);
}

void exibir_menu_quartos() {
    int opcao;
    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tQUARTOS\n\n");
        printf("\t\t (2) EDITAR DADOS DO QUARTO\n");
        printf("\t\t   (4) BUSCAR QUARTO\n\n");
        printf("\t\t    (4) LISTAR QUARTOS\n\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                limpar_tela();
                break;
            case 0:
                return;
            default:
                printf("\n\nOPCAO INVALIDA!\n\n");
                pausa();
                break;
        }
    } while (opcao != 0);
}

void exibir_menu_servicos() {
    int opcao;
    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tCLIENTES\n\n");
        printf("\t\t(1) NOVO CLIENTE\n");
        printf("\t\t (2) EDITAR CLIENTE\n");
        printf("\t\t  (3) REMOVER CLIENTE\n\n");
        printf("\t\t   (4) BUSCAR CLIENTE\n\n");
        printf("\t\t    (4) LISTAR CLIENTES\n\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                limpar_tela();
                break;
            case 0:
                return;
            default:
                printf("\n\nOPCAO INVALIDA!\n\n");
                pausa();
                break;
        }
    } while (opcao != 0);
}

void exibir_menu_configuracoes() {
    int opcao;

    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tMANUTENCAO\n");
        printf("\n\t\t(1) ALTERAR LOGIN\n");
        printf("\t\t  (2) FAZER BACKUP DOS ARQUIVOS\n");
        printf("\t\t    (3) REMOVER TODOS OS DADOS DO SISTEMA\n");
        printf("\t\t      (4) RESTAURAR BACKUP\n");
        printf("\t\t        (5) REMOVER BACKUP\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");

        limpar_teclado();
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                alterar_login();
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            case 0:
                return;
            default:
                printf("\n\nOPCAO INVALIDA!\n\n");
                pausa();
                break;
        }
    } while (opcao != 0);

}

void exibir_menu_dados_sistema() {
    int opcao;
    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tDADOS DO SISTEMA\n");
        printf("\n\t\t(1) QUANTIDADE DE RESERVAS ATIVAS \n");
        printf("\t\t  (2) HISTORICO DE HOSPEDES\n");
        printf("\t\t   (3) LISTAR QUARTOS\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                exibir_qtd_reservas();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                return;
            default:
                printf("\n\nOPCAO INVALIDA!\n\n");
                pausa();
                break;
        }
    } while (opcao != 0);
}

// menus de busca

void exibir_menu_busca_cliente() {
    int opcao;
    char dado_busca[50];

    do {
        limpar_tela();
        printf("\n\tBUSCAR CLIENTE\n\n");
        printf("\t\t(1) BUSCAR POR NOME\n");
        printf("\t\t  (2) BUSCAR POR CPF\n");
        printf("\t\t    (3) BUSCAR POR ID\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n\t\tINSIRA O NOME: ");
                break;
            case 2:
                printf("\n\t\tINSIRA O CPF: ");
                busca_cliente("cpf", dado_busca, NULL);
                break;
            case 3:
                printf("\n\t\tINSIRA O ID: ");
                busca_cliente("id", dado_busca, NULL);
                break;
            case 0:
                return;
            default:
                printf("\n\nOPCAO INVALIDA!\n\n");
                pausa();
                break;
        }
    } while (opcao != 0);
}

// diretorios e base de dados

int criar_banco_de_dados() {
    FILE *db = fopen(DB_PATH, "r+b");
    int criacao__banco_dados = 0;

    if (db == NULL) {
        db = fopen(DB_PATH, "w+b");
        fclose(db);
        printf("\n\n\t\tCRIANDO BANCO DE DADOS ... \n");
        criar_banco();
        criacao__banco_dados = 1;
    } else { fclose(db); }

    return criacao__banco_dados;
}

int checar_diretorios() {
    FILE *ativo = fopen("data/usr/.ativo", "r+b");
    int criacao_de_diretorios = 0;

    if (ativo == NULL) {
        mkdir("data/", 0700);
        mkdir("data/usr/", 0700);
        ativo = fopen("data/usr/.ativo", "w+b");
        criacao_de_diretorios = 1;
    }
    fclose(ativo);
    return criacao_de_diretorios;
}
