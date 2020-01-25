//
// Created by diego on 07/01/2020.
//

#include "reservas.h"
#include "../datas.h"
#include "../extrafuncs.h"
#include "../database.h"
#include "quartos.h"
#include "../browserdb.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT_BUSCA 1000

void registrar_reserva();

void exibir_menu_editar_reserva();

void exibir_menu_remover_reserva();

int exibir_menu_buscar_reservas(char *filter, char *value);

int exibir_menu_listar_reservas(char *column, char *filter);

void exibir_struct_reserva(RESERVA *r);

void visualizar_reservas(int (*pFunction)(char *, char *));

void remover_reserva_id(int id);

int selecionar_reserva(int (*pFunction)(char *, char *), RESERVA *reserva);

void editar_dados_reserva(RESERVA *r);

char *formatar_insert_reserva(RESERVA *r, char *sql);

void formatar_update_reservas(RESERVA *r, char *sql);

void inserir_data_reserva(struct tm *data_inicio, struct tm *data_final);

void pegar_data_reserva(RESERVA *r);

void mostrar_reserva(RESERVA *r, CLIENTE *c);

int busca_reserva(char *coluna, char *valor, int *ids);

void exibir_qtd_reservas();

void buscar_reserva();

void pegar_cliente_reserva(RESERVA *r);

void pegar_quarto_reserva(RESERVA *r);

void teste_reserva() {
    RESERVA r;
    pegar_cliente_reserva(&r);
}

void exibir_menu_gerenciar_reservas() {
    int opcao;

    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\n\t\tRESERVAS\n\n");
        printf("\t\t(1) REGISTRAR RESERVA\n\n");
        printf("\t\t (2) EDITAR RESERVA\n\n");
        printf("\t\t  (3) FINALIZAR RESERVA\n\n");
        printf("\t\t   (4) BUSCAR RESERVAS\n\n");
        printf("\t\t    (5) LISTAR RESERVAS\n\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                registrar_reserva();
                break;
            case 2:
                exibir_menu_editar_reserva();
                break;
            case 3:
                exibir_menu_remover_reserva();
                break;
            case 4:
                limpar_tela();
                selecionar_reserva(exibir_menu_buscar_reservas, NULL);
                break;
            case 5:
                limpar_tela();
                selecionar_reserva(exibir_menu_listar_reservas, NULL);
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

void registrar_reserva() {
    char sql[300];
    RESERVA r;

    pegar_data_reserva(&r);

    formatar_insert_reserva(&r, sql);
    executar_sql_externa(sql);
}

void exibir_menu_editar_reserva() {
    RESERVA r;
    int opcao;
    int id;

    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\n\t\tEDITAR CLIENTE\n\n");
        printf("\t\t(1) BUSCAR CLIENTE PARA EDICAO\n");
        printf("\t\t (2) LISTAR CLIENTES\n");
        printf("\t\t  (3) INSERIR ID CLIENTES\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                id = selecionar_reserva(exibir_menu_buscar_reservas, &r);
                editar_dados_reserva(&r);
                break;
            case 2:
                id = selecionar_reserva(exibir_menu_listar_reservas, &r);
                editar_dados_reserva(&r);
                break;
            case 3:
                printf("\n\n\t\tID: ");
                scanf(" %d", &id);
                if (testar_id(id, "reserva"))
                    editar_dados_reserva(&r);
                else {
                    printf("\n\t\tID INVALIDO\n");
                    pausa();
                }
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

void exibir_menu_remover_reserva() {
    int opcao;
    int id;
    do {
        mostrar_titulo();
        printf("\n\n\t\tREMOVER CLIENTE\n\n");
        printf("\t\t(1) BUSCAR CLIENTES PARA REMOCAO\n");
        printf("\t\t (2) LISTAR CLIENTES PARA REMOCAO\n");
        printf("\t\t  (3) INSERIR ID DO CLIENTE\n\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                id = selecionar_reserva(exibir_menu_buscar_reservas, NULL);
                remover_reserva_id(id);
                break;
            case 2:
                id = selecionar_reserva(exibir_menu_listar_reservas, NULL);
                remover_reserva_id(id);
                break;
            case 3:
                printf("\n\n\t\tID: ");
                scanf(" %d", &id);
                if (testar_id(id, "reserva"))
                    remover_reserva_id(id);
                else {
                    printf("\n\t\tID INVALIDO\n");
                    pausa();
                }
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

int exibir_menu_buscar_reservas(char *filter, char *value) {
    int opcao;
    char dado_busca[50];
    int ativo = 0;

    while (1) {
        limpar_tela();
        printf("\n\tBUSCAR CLIENTE\n\n");
        printf("\t\t(1) BUSCAR POR NOME\n\n");
        printf("\t\t  (2) BUSCAR POR CPF\n\n");
        printf("\t\t    (3) BUSCAR POR ID\n\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n\t\tINSIRA O NOME: ");
                limpar_teclado();
                fgets(dado_busca, 50, stdin);
                remover_quebra(dado_busca);
                strcpy(filter, "nome");
                strcpy(value, dado_busca);
                return 1;
            case 2:
                printf("\n\t\tINSIRA O CPF: ");
                limpar_teclado();
                fgets(dado_busca, 50, stdin);
                remover_quebra(dado_busca);
                strcpy(filter, "cpf");
                strcpy(value, dado_busca);
                return 1;
            case 3:
                printf("\n\t\tINSIRA O ID: ");
                limpar_teclado();
                fgets(dado_busca, 50, stdin);
                remover_quebra(dado_busca);
                strcpy(filter, "id");
                strcpy(value, dado_busca);
                return 1;
            case 0:
                return 0;
            default:
                printf("\n\nOPCAO INVALIDA!\n\n");
                pausa();
        }
    }
}

int exibir_menu_listar_reservas(char *column, char *filter) {
    int opcao;
    while (1) {
        limpar_tela();
        mostrar_titulo();
        printf("\n\n\t\tLISTAR CLIENTES\n\n");
        printf("\t\t(1) LISTAR TODOS OS CLIENTES REGISTRADOS\n");
        printf("\n\t\t (2) LISTAR CLIENTES COM RESERVA ATIVA\n");
        printf("\n\t\t  (3) LISTAR CLIENTES SEM RESERVA ATIVA\n\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                strcpy(column, "NULL");
                strcpy(filter, "NULL");
                return 1;
            case 2:
                strcpy(column, "id_reserva!");
                strcpy(filter, "0");
                return 1;
            case 3:
                strcpy(column, "id_reserva");
                strcpy(filter, "0");
                return 1;
            case 0:
                return 0;
            default:
                printf("\n\nOPCAO INVALIDA!\n\n");
                pausa();
        }
    }
}

void exibir_struct_reserva(RESERVA *r) {
    printf("\n\t\tID: %d", r->id);
    printf("\n\t\tID CLIENTE: %d", r->id_cliente);
    printf("\n\t\tQUARTO: %d", r->id_quarto);
    printf("\n\t\tINICIO: %0d-%0d-%0d", r->inicio.tm_mday, r->inicio.tm_mon, r->inicio.tm_year);
    printf("\n\t\tFIM: %0d-%0d-%0d", r->fim.tm_mday, r->fim.tm_mon, r->fim.tm_year);
}

void visualizar_reservas(int (*pFunction)(char *, char *)) {
    RESERVA r;
    int op;
    int id;

    while (1) {
        id = selecionar_reserva(pFunction, &r);

        if (id == 0)
            break;

        printf("\n\t\t(1) EDITAR CLIENTE (2) REMOVER CLIENTE (3) VOLTAR (0) SAIR\n\t\tOPCAO: ");
        scanf(" %d", &op);

        if (op == 1)
            editar_dados_reserva(&r);
        else if (op == 2)
            remover_reserva_id(id);
        else if (op == 3)
            continue;
        else break;
    }
}

void remover_reserva_id(int id) {
    char id_char[5];
    snprintf(id_char, 5, "%d", id);
    db_remover_cliente("id", id_char);
}

int selecionar_reserva(int (*pFunction)(char *, char *), RESERVA *reserva) {
    char column[50];
    char filter[50];
    int ids_encontrados[LIMIT_BUSCA] = {0};
    int id;

    if (pFunction(column, filter)) {
        limpar_tela();
        mostrar_titulo();
        puts("\n\n\t\tRESULTADOS\n\n");

        int total_resultados = db_listar_reservas(column, filter, LIMIT_BUSCA, "nome", ids_encontrados,
                                                  exibir_resultados);

        if (total_resultados == 0) {
            printf("\n\n\t\tNENHUM RESULTADO ENCONTRADO\n");
            pausa();
            return 0;

        } else {
            printf("\n\n\t\t(0) VOLTAR OU INSERIR UM ID: ");
            scanf(" %d", &id);

            if (id <= 0)
                return 0;
            else {
                ids_encontrados[0] = -1;

                if (is_in(id, ids_encontrados, total_resultados + 1)) {
                    int confirm;

                    limpar_tela();
//                    montar_cliente_busca(id, reserva);

                    printf("\n\n\t\t(1) CONFIRMAR CLIENTE (0) VOLTAR :  ");
                    scanf(" %d", &confirm);

                    return confirm == 1 ? id : selecionar_reserva(pFunction, NULL);

                } else {
                    printf("\n\t\tID NAO LISTADO\n");
                    pausa();
                    return -1;
                }
            }
        }
    }
    return 0;
}

void editar_dados_reserva(RESERVA *r) {
    limpar_tela();
    mostrar_titulo();
    printf("\n\n\t\tEDITAR RESERVA\n\n");
    pegar_data_reserva(r);

    limpar_tela();
    mostrar_titulo();
    printf("\n\n\t\tEDITAR RESERVA\n\n");
    exibir_struct_reserva(r);

    int op;
    printf("\n\t\t(1) CONFIRMAR  (2) REINICIAR EDICAO  (0) CANCELAR\n\t\tOPCAO: ");
    scanf(" %d", &op);

    char sql[500];

    if (op == 1) {
        formatar_update_reservas(r, sql);
        executar_sql_externa(sql);

        limpar_tela();
        printf("\n\t\tFINALIZADO\n");
        pausa();
    } else if (op == 2) {
        editar_dados_reserva(r);
    } else return;

}

char *formatar_insert_reserva(RESERVA *r, char *sql) {
    char str[50];

    strcpy(sql, "insert into reservas values (null, '");

    snprintf(str, 10, "%d", r->id_cliente);
    strcat(sql, str);
    strcat(sql, "', '");

    snprintf(str, 10, "%d", r->id_quarto);
    strcat(sql, str);
    strcat(sql, "', '");

    formatar_data_sql(&r->inicio, str);
    strcat(sql, str);
    strcat(sql, "', '");

    formatar_data_sql(&r->fim, str);
    strcat(sql, str);
    strcat(sql, "');");

    puts(sql);

    return sql;
}

void formatar_update_reservas(RESERVA *r, char *sql) {
    char str[50];

    strcpy(sql, "update reservas set id_cliente = '");
    snprintf(str, 10, "%d", r->id_cliente);
    strcat(sql, str);

    strcat(sql, "', id_quarto = '");
    snprintf(str, 10, "%d", r->id_quarto);
    strcat(sql, str);

    strcat(sql, "', inicio = '");
    formatar_data_sql(&r->inicio, str);
    strcat(sql, str);

    strcat(sql, "', fim = '");
    formatar_data_sql(&r->fim, str);
    strcat(sql, str);

    strcat(sql, "' where id = ");
    snprintf(str, 10, "%d", r->id);
    strcat(sql, str);
    strcat(sql, ";");

    puts(sql);
}

void inserir_data_reserva(struct tm *data_inicio, struct tm *data_final) {
    do {
        printf("\n\n\t\tDATA DE ENTRADA (EX.: DD-MM-AAAA): ");
        scanf(" %d %d %d", &data_inicio->tm_mday, &data_inicio->tm_mon, &data_inicio->tm_year);

        printf("\n\t\tDATA DE SAIDA (EX.: DD-MM-AAAA): ");
        scanf(" %d %d %d", &data_final->tm_mday, &data_final->tm_mon, &data_final->tm_year);

        if (validar_periodo(data_inicio, data_final) == 0) {
            printf("\n\nDATA OU PERIODO INVALIDO\n");
            pausa();
        } else
            break;

    } while (1);

}

void pegar_data_reserva(RESERVA *r) {
    int op;

    do {
        printf("\n\n\n\t\tPERIODO DE HOSPEDAGEM\n\n");
        inserir_data_reserva(&r->inicio, &r->fim);
        printf("\n\n\t\t(1) CONFIRMAR DADOS (0) CANCELAR: ");
        scanf(" %d", &op);
        if (op == 1) break;
    } while (1);
}

void pegar_quarto_reserva(RESERVA *r) {
    int op;

    do {
        printf("\n\n\n\t\tDEFINIR QUARTO\n\n");

        selecionar_quarto(&r->inicio, &r->fim, &r->id_quarto);

        printf("\n\n\t\t(1) CONFIRMAR DADOS (0) CANCELAR: ");
        scanf(" %d", &op);
        if (op == 1) break;
    } while (1);
}

void pegar_cliente_reserva(RESERVA *r) {
    int op;
    int id;
    int confirm;

    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\n\t\t(1) CLIENTE EXISTENTE\n");
        printf("\n\t\t (2) NOVO CLIENTE\n");
        printf("\n\t\t  (0) VOLTAR\n");
        printf("\n\n\t\tOPCAO: ");
        scanf(" %d", &op);

        switch (op) {
            case 1: {
                do {
                    limpar_tela();
                    mostrar_titulo();
                    printf("\n\n\t\t(1) BUSCAR CLIENTE\n");
                    printf("\n\t\t (2) LISTAR CLIENTES\n");
                    printf("\n\t\t  (3) INSERIR ID DO CLIENTE\n");
                    printf("\n\t\t   (0) VOLTAR");
                    printf("\n\n\t\tOPCAO: ");
                    scanf(" %d", &op);

                    switch (op) {
                        case 1: {
                            r->id_cliente = buscar_clientes();
                            if (r->id_cliente) {
                                printf("\n\t\t(1) CONFIRMAR CLIENTE (0) CANCELAR : ");
                                scanf(" %d", &confirm);
                                if (confirm == 1) return;
                            } else break;
                        }
                        case 2: {
                            r->id_cliente = listar_clientes();
                            if (r->id_cliente) {
                                printf("\n\t\t(1) CONFIRMAR CLIENTE (0) CANCELAR : ");
                                scanf(" %d", &confirm);
                                if (confirm == 1) return;
                            } else continue;
                        }
                        case 3: {
                            printf("\n\t\tINSIRA O ID: ");
                            scanf(" %d", &id);

                            if (testar_id(id, "clientes")) {
                                montar_cliente_busca(id, NULL);

                                printf("\n\n\t\t(1) CONFIRMAR CLIENTE (0) CANCELAR : ");
                                scanf(" %d", &confirm);
                                if (confirm == 1) {
                                    r->id_cliente = id;
                                    return;
                                } else break;

                            } else {
                                printf("\n\t\tID INVALIDO");
                                pausa();
                                break;
                            }
                        }
                        case 0: {
                            break;
                        }
                        default: {
                            printf("\n\t\tOPCAO INVALIDA");
                            pausa();
                            break;
                        }
                    }
                } while (op != 0);
                continue;
            }
            case 2: {
                r->id_cliente = registrar_cliente();
                break;
            }
            case 0: {
                break;
            }
            default: {
                printf("\n\t\tOPCAO INVALIDA");
                pausa();
                break;
            }
        }
    } while (op != 0);
}

void mostrar_reserva(RESERVA *r, CLIENTE *c) {
    printf("\t\tID: %04d\n", r->id);
    printf("\t\t NOME DO CLIENTE: %s\n", c->nome);
    printf("\t\t  CPF: %s\n", c->cpf);
    // printf("\t\t   QUARTO: %d\n\n", r->qrt->id);
    printf("\t\t    RESERVA: ");
    puts("\t-----------------------------------------------------------------------------------\n");
}

int busca_reserva(char *coluna, char *valor, int *ids) {
    int qtd_resultados;
    qtd_resultados = db_listar_clientes(coluna, valor, -1, NULL, ids, exibir_resultados);
    return qtd_resultados;
}

void exibir_qtd_reservas() {

}

void buscar_reserva() {
    int opcao;

    char dados_busca[50];

    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tBUSCAR RESERVA\n\n");
        printf("\t\t(1) BUSCAR POR CLIENTE DA RESERVA\n");
        printf("\t\t  (2) BUSCAR POR QUARTO DA RESERVA\n");
        printf("\t\t    (3) BUSCAR POR DATA DA RESERVA\n");
        printf("\t\t      (4) BUSCAR POR ID DA RESERVA\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n\t\tINSIRA O NOME: ");
                break;
            case 2:
                printf("\n\t\tINSIRA O CPF: ");
                break;
            case 3:
                printf("\n\t\tINSIRA O ID: ");
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