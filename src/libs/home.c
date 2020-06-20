//
// Created by diego on 20/06/2020.
//

#include "home.h"

#include "extrafuncs.h"
#include "login.h"
#include "datas.h"
#include "browserdb.h"
#include "database.h"
#include "elementos_hotel/reservas.h"
#include "elementos_hotel/quartos.h"
#include "elementos_hotel/servicos.h"

#include <stdio.h>
#include <stdlib.h>

void exibir_menu_configuracoes();

void exibir_menu_gerenciar_dados_sistema();

void fazer_bkp();

void resetar_sistema();

void restaurar_bkp();

void remover_bkp();

void reiniciar_db();

void exibir_menu_principal() {
    int opcao;

    do {
        mostrar_titulo();
        printf("\n\t\tMENU INICIAL\n");
        printf("\n\t\t(1) GERENCIAR RESERVAS\n");
        printf("\n\t\t (2) GERENCIAR CLIENTES\n");
        printf("\n\t\t  (3) GERENCIAR QUARTOS\n");
        printf("\n\t\t   (4) GERENCIAR SERVICOS\n");
        printf("\n\t\t    (5) GERENCIAR DADOS DO SISTEMA\n");
        printf("\n\t\t     (6) MANUTENCAO\n");
        printf("\n\t\t(0) SAIR\n");
        printf("\n\t\tOPCAO: ");
        limpar_teclado();
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                exibir_menu_gerenciar_reservas();
                break;
            case 2:
                exibir_menu_gerenciar_clientes();
                break;
            case 3:
                exibir_menu_gerenciar_quartos();
                break;
            case 4:
                exibir_menu_gerenciar_servicos();
                break;
            case 5:
                exibir_menu_gerenciar_dados_sistema();
                break;
            case 6:
                exibir_menu_configuracoes();
                break;
            case 0:
                mostrar_titulo();
                printf("\n\n\t\tSAINDO...\n\n");
                exit(0);

            default:
                printf("\n\n\t\tOPCAO INVALIDA!\n\n");
                pausa();
                break;
        }
    } while (opcao != 0);
}

void exibir_menu_configuracoes() {
    int opcao;

    do {
        mostrar_titulo();
        printf("\n\t\tMANUTENCAO\n");
        printf("\n\t\t(1) ALTERAR LOGIN\n\n");
        printf("\t\t (2) FAZER BACKUP DOS ARQUIVOS\n\n");
        printf("\t\t  (3) REMOVER TODOS OS DADOS DO SISTEMA\n\n");
        printf("\t\t   (4) RESTAURAR BACKUP\n\n");
        printf("\t\t    (5) REMOVER BACKUP\n\n");
        printf("\t\t     (6) REINICIAR BANCO DE DADOS\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPCAO: ");

        limpar_teclado();
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                alterar_login();
                break;
            case 2:
                fazer_bkp();
                break;
            case 3:
                resetar_sistema();
                break;
            case 4:
                restaurar_bkp();
                break;
            case 5:
                remover_bkp();
                break;
            case 6:
                reiniciar_db();
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

void reiniciar_db() {
    int opcao;

    mostrar_titulo();
    printf("\n\n\t\tTODOS OS DADOS SERAO APAGADOS\n\t\t(1) CONFIRMAR (0) CANCELAR : ");
    scanf(" %d", &opcao);
    if (opcao == 1)
        db_reset_db();

    mostrar_titulo();
    printf("\n\t\tBANCO DE DADOS REINICIADO!");
    pausa();
}

void remover_bkp() {
    int opcao;

    mostrar_titulo();
    if (check_bkp_file()) {
        printf("\n\n\t\tO BACKUP SERA APAGADO\n\t\t(1) CONFIRMAR (0) CANCELAR : ");
        scanf(" %d", &opcao);
        if (opcao == 1) bkp_db(-1);
    } else {
        puts("\n\t\tNAO FOI REALIZADO BACKUP ANTERIORMENTE\n");
    }

    pausa();
}

void restaurar_bkp() {
    mostrar_titulo();
    if (check_bkp_file()) {
        bkp_db(0);
        puts("\n\t\tBACKUP RESTAURADO\n");
    } else {
        puts("\n\t\tNAO FOI REALIZADO BACKUP ANTERIORMENTE\n");
    }

    pausa();
}

void resetar_sistema() {
    int opcao;

    mostrar_titulo();
    printf("\n\n\t\tTODOS OS DADOS SERAO APAGADOS\n\t\t(1) CONFIRMAR (0) CANCELAR : ");
    scanf(" %d", &opcao);
    if (opcao == 1)
        db_deletar_dados();

    mostrar_titulo();
    printf("\n\t\tDADOS REMOVIDOS!");
    pausa();
}

void fazer_bkp() {
    int opcao;

    mostrar_titulo();
    if (check_bkp_file()) {
        printf("\n\t\tSUBSTITUIR BACKUP ANTERIOR\n\t\t(1) CONFIRMAR (0) CANCELAR : ");
        scanf(" %d", &opcao);

        if (opcao == 1) {
            bkp_db(1);
            puts("\n\t\tBACKUP REALIZADO\n");

        } else puts("\n\t\tBACKUP NAO REALIZADO\n");
    }
    pausa();
}

void exibir_menu_gerenciar_dados_sistema() {
    int opcao;
    do {
        mostrar_titulo();
        printf("\n\t\tDADOS DO SISTEMA\n\n");
        printf("\n\t\t(1) ESTATISTICAS DE DADOS REGISTRADOS\n\n");
        printf("\t\t (2) HISTORICO DE HOSPEDES\n\n");
        printf("\t\t  (3) LISTAR QUARTOS RESERVADOS\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPCAO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                mostrar_titulo();
                db_listar_dados_registrados();
                pausa();
                break;
            case 2:
                mostrar_titulo();
                db_listar_clientes_detalhado();
                pausa();
                break;
            case 3:
                mostrar_titulo();
                db_listar_quartos_detalhado();
                pausa();
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
