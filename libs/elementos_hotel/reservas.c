//
// Created by diego on 07/01/2020.
//

#include "reservas.h"
#include "../datas.h"
#include "../extrafuncs.h"
#include "../database.h"
#include "quartos.h"
#include "../browserdb.h"
#include "servicos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT_BUSCA 1000

void registrar_reserva();

void exibir_menu_editar_reserva();

void exibir_menu_finalizar_reserva();

int exibir_menu_buscar_reservas(char *filter, char *value);

int exibir_menu_listar_reservas(char *column, char *filter);

void exibir_struct_reserva(RESERVA *r);

void visualizar_reservas(int (*pFunction)(char *, char *));

void finalizar_reserva_id(int id);

int exibir_reservas(int (*pFunction)(char *, char *), RESERVA *reserva);

void editar_dados_reserva(RESERVA *r);

char *formatar_insert_reserva(RESERVA *r, char *sql);

void formatar_update_reservas(RESERVA *r, char *sql);

int pegar_data_reserva(RESERVA *r);

int pegar_cliente_reserva(RESERVA *r);

int pegar_quarto_reserva(RESERVA *r);

void alocar_cliente_reserva(int cliente, int reserva, int quarto);

int testar_reserva_ativa(int cliente);

void montar_reserva_busca(int id, RESERVA *reserva);

int montar_reserva_sql(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna);


void exibir_menu_gerenciar_reservas() {
    int opcao;

    do {
        mostrar_titulo();
        printf("\n\t\tRESERVAS\n\n");
        printf("\t\t(1) REGISTRAR RESERVA\n\n");
        printf("\t\t (2) EDITAR RESERVA\n\n");
        printf("\t\t  (3) FINALIZAR RESERVA\n\n");
        printf("\t\t   (4) BUSCAR RESERVAS\n\n");
        printf("\t\t    (5) LISTAR RESERVAS\n\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPCAO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                registrar_reserva();
                break;
            case 2:
                exibir_menu_editar_reserva();
                break;
            case 3:
                exibir_menu_finalizar_reserva();
                break;
            case 4:
                visualizar_reservas(exibir_menu_buscar_reservas);
                break;
            case 5:
                visualizar_reservas(exibir_menu_listar_reservas);
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

int selecionar_reserva() {
    int opcao;
    int id;

    do {
        mostrar_titulo();
        printf("\n\n\t\tSELECIONAR RESERVA\n\n");
        printf("\t\t(1) BUSCAR RESERVA\n\n");
        printf("\t\t (2) LISTAR RESERVA\n\n");
        printf("\t\t  (3) INSERIR ID DA RESERVA\n\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPCAO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                id = exibir_reservas(exibir_menu_buscar_reservas, NULL);
                return id;
            case 2:
                id = exibir_reservas(exibir_menu_listar_reservas, NULL);
                return id;
            case 3:
                printf("\n\n\t\tID: ");
                scanf(" %d", &id);
                if (testar_id(id, "reservas"))
                    return id;
                else {
                    printf("\n\t\tID INVALIDO\n");
                    pausa();
                }
                break;
            case 0:
                return 0;
            default:
                printf("\n\nOPCAO INVALIDA!\n\n");
                pausa();
                break;
        }
    } while (opcao != 0);
}

void registrar_reserva() {
    char sql[500];
    int op;
    int ok = 0;
    RESERVA r;
    gerar_id("reservas", &r.id);

    while (1) {
        if (pegar_data_reserva(&r) == 0)
            return;

        while (1) {
            if (pegar_quarto_reserva(&r) == 0)
                break;
            if (pegar_cliente_reserva(&r) != 0) {
                ok = 1;
                break;
            }
        }

        if (ok) break;
    }

    formatar_insert_reserva(&r, sql);

    while (1) {
        mostrar_titulo();

        printf("\n\t\tREGISTRAR RESERVA\n");
        exibir_struct_reserva(&r);

        printf("\n\n\t\t(1) CONFIRMAR DADOS");
        printf("\n\n\t\t (2) EDITAR");
        printf("\n\n\t\t  (3) REINICIAR");
        printf("\n\n\t\t   (0) CANCELAR\n");
        printf("\n\n\t\tOPCAO: ");
        scanf(" %d", &op);

        if (op == 1) {
            executar_sql(sql, NULL, NULL);
            reservar_quarto(r.id_quarto, r.id);
            alocar_cliente_reserva(r.id_cliente, r.id, r.id_quarto);
            return;
        } else if (op == 2) {
            editar_dados_reserva(&r);
        } else if (op == 3) {
            registrar_reserva();

            return;
        } else return;
    }
}

void alocar_cliente_reserva(int cliente, int reserva, int quarto) {
    char sql[200];
    char str[10];

    strcpy(sql, "update clientes set id_reserva = ");
    snprintf(str, 10, "%d", reserva);
    strcat(sql, str);

    strcat(sql, ", id_quarto = ");
    snprintf(str, 10, "%d", quarto);
    strcat(sql, str);

    strcat(sql, " where id = ");
    snprintf(str, 10, "%d", cliente);
    strcat(sql, str);
    strcat(sql, ";");
    executar_sql(sql, NULL, NULL);
}

void exibir_menu_editar_reserva() {
    RESERVA r;
    int opcao;
    int id;

    do {
        mostrar_titulo();
        printf("\n\t\tEDITAR RESERVA\n\n");
        printf("\t\t(1) BUSCAR RESERVA PARA EDICAO\n");
        printf("\t\t (2) LISTAR RESERVAS\n");
        printf("\t\t  (3) INSERIR ID DA RESERVA\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPCAO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                id = exibir_reservas(exibir_menu_buscar_reservas, &r);
                editar_dados_reserva(&r);
                break;
            case 2:
                id = exibir_reservas(exibir_menu_listar_reservas, &r);
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

void exibir_menu_finalizar_reserva() {
    int op;
    int id;
    while (1) {
        id = selecionar_reserva();
        if (id != 0) {
            printf("\n\t\t(1) CONFIRMAR (0) CANCELAR : ");
            scanf(" %d", &op);

            if (op == 1) {
                finalizar_reserva_id(id);

                mostrar_titulo();
                printf("\n\n\t\tRESERVA FINALIZADA!\n\n");
                pausa();

            } else if (op == 0) {
                printf("\n\t\tCANCELADO!\n");
                pausa();
                return;
            }

        } else return;

    }
}

int exibir_menu_buscar_reservas(char *filter, char *value) {
    int opcao;
    char dado_busca[50], aux[50];
    struct tm inicio, fim;
    int id;

    while (1) {
        mostrar_titulo();
        printf("\n\t\tBUSCAR RESERVA\n\n");
        printf("\t\t(1) BUSCAR POR ID\n\n");
        printf("\t\t (2) BUSCAR POR DATA\n\n");
        printf("\t\t  (3) BUSCAR POR QUARTO\n\n");
        printf("\t\t   (4) BUSCAR POR CLIENTE\n\n");
        printf("\n\t\t(0) VOLTAR\n\n");
        printf("\n\t\tOPCAO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n\n\t\tINSIRA O ID: ");
                scanf(" %d", &id);
                snprintf(dado_busca, 10, "%d", id);
                strcpy(filter, "id");
                strcpy(value, dado_busca);
                return 1;

            case 2:
                inserir_data_reserva(&inicio, &fim);
                formatar_data_sql(&inicio, dado_busca);
                formatar_data_sql(&fim, aux);
                strcat(dado_busca, ",");
                strcat(dado_busca, aux);
                strcpy(filter, "data");
                strcpy(value, dado_busca);
                return 1;

            case 3:
                printf("\n\t\tINSIRA O NUMERO DO QUARTO: ");
                limpar_teclado();
                fgets(dado_busca, 50, stdin);
                remover_quebra(dado_busca);
                strcpy(filter, "id_quarto");
                strcpy(value, dado_busca);
                return 1;

            case 4:
                id = buscar_clientes();
                snprintf(dado_busca, 10, "%d", id);
                strcpy(filter, "id_cliente");
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
        mostrar_titulo();
        printf("\n\n\t\tLISTAR RESERVAS\n\n");
        printf("\n\t\t(1) LISTAR RESERVAS ATIVAS\n");
        printf("\n\t\t (2) LISTAR RESERVAS FINALIZADAS\n\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPCAO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                strcpy(column, "NULL");
                strcpy(filter, "NULL");
                return 1;
            case 2:
                strcpy(column, "inativa");
                strcpy(filter, "NULL");
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
        id = exibir_reservas(pFunction, &r);

        if (id == 0)
            break;

        printf("\n\t\t(1) EDITAR RESERVA (2) REMOVER RESERVA (3) VOLTAR (0) SAIR\n\t\tOPCAO: ");
        scanf(" %d", &op);

        if (op == 1)
            editar_dados_reserva(&r);
        else if (op == 2)
            finalizar_reserva_id(id);
        else if (op == 3)
            continue;
        else break;
    }
}

void finalizar_reserva_id(int id) {
    char id_char[5];
    snprintf(id_char, 5, "%d", id);

    char aux[10];
    char nome_fatura[100];
    snprintf(aux, 10, "%d", id);
    strcpy(nome_fatura, "data/faturas/fatura_id_reserva_");
    strcat(nome_fatura, aux);
    strcat(nome_fatura, ".txt");

    mostrar_titulo();
    printf("\n\n\t\t\tRESERVA FINALIZADA\n");
    printf("\n\n\t\tFATURA SALVA EM %s\n\n", nome_fatura);
    pausa();

    gerar_fatura_reserva_finalizada(id);
    db_remover_reserva(id_char);

    pausa();
}

int exibir_reservas(int (*pFunction)(char *, char *), RESERVA *reserva) {
    char column[50];
    char filter[50];
    int ids_encontrados[LIMIT_BUSCA] = {0};
    int id;

    if (pFunction(column, filter)) {
        mostrar_titulo();
        puts("\n\n\t\tRESULTADOS\n\n");

        int total_resultados = db_listar_reservas(column, filter, LIMIT_BUSCA, "id", ids_encontrados,
                                                  exibir_resultados);


        if (total_resultados == 0) {
            printf("\n\n\t\tNENHUM RESULTADO ENCONTRADO\n");
            pausa();
            return 0;

        } else if (strcmp(column, "inativa") == 0) {
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

                    mostrar_titulo();
                    montar_reserva_busca(id, reserva);

                    printf("\n\n\t\t(1) CONFIRMAR RESERVA (0) VOLTAR :  ");
                    scanf(" %d", &confirm);

                    return confirm == 1 ? id : exibir_reservas(pFunction, NULL);

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
    int op;

    do {
        mostrar_titulo();
        printf("\n\n\t\tEDITAR RESERVA\n\n");
        printf("\n\t\t(1) EDITAR DATA\n");
        printf("\n\t\t (2) EDITAR CLIENTE\n");
        printf("\n\t\t  (3) EDITAR QUARTO\n");
        printf("\n\t\t   (0) VOLTAR\n");
        printf("\n\t\tOPCAO: ");
        scanf(" %d", &op);
        switch (op) {
            case 1:
                pegar_data_reserva(r);
                op = 0;
                break;
            case 2:
                pegar_cliente_reserva(r);
                op = 0;
                break;
            case 3:
                pegar_quarto_reserva(r);
                op = 0;
                break;
            case 0:
                return;
            default:
                printf("\n\n\t\tOPCAO INVALIDA\n");
                pausa();
                break;
        }
    } while (op != 0);

    mostrar_titulo();
    printf("\n\n\t\tEDITAR RESERVA\n\n");
    exibir_struct_reserva(r);

    printf("\n\n\t\t(1) CONFIRMAR  (2) REINICIAR EDICAO  (0) CANCELAR\n\t\tOPCAO: ");
    scanf(" %d", &op);

    char sql[500];

    if (op == 1) {
        formatar_update_reservas(r, sql);
        executar_sql(sql, NULL, NULL);

        mostrar_titulo();
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

}

int pegar_data_reserva(RESERVA *r) {
    int op;

    do {
        mostrar_titulo();
        printf("\n\n\n\t\tPERIODO DE HOSPEDAGEM\n\n");

        inserir_data_reserva(&r->inicio, &r->fim);

        printf("\n\n\t\t(1) CONFIRMAR DADOS (2) EDITAR DATA (0) CANCELAR: ");
        scanf(" %d", &op);
        if (op == 1) return 1;
        else if (op == 0) return 0;
    } while (1);
}

int pegar_quarto_reserva(RESERVA *r) {
    int op;

    do {
        mostrar_titulo();
        printf("\n\n\n\t\tDEFINIR QUARTO\n\n");

        int id_quarto = selecionar_quarto(&r->inicio, &r->fim, &r->id_quarto);
        if (id_quarto == 0)
            return 0;

        printf("\n\n\t\t(1) CONFIRMAR (2) ALTERAR QUARTO (0) VOLTAR: ");
        scanf(" %d", &op);
        if (op == 1)
            return id_quarto;
        else if (op == 0)
            return 0;

    } while (1);
}

int pegar_cliente_reserva(RESERVA *r) {
    int op;
    int id;
    int confirm;

    do {
        mostrar_titulo();
        printf("\n\n\t\t(1) CLIENTE EXISTENTE\n");
        printf("\n\t\t (2) NOVO CLIENTE\n");
        printf("\n\t\t  (0) VOLTAR\n");
        printf("\n\n\t\tOPCAO: ");
        scanf(" %d", &op);

        switch (op) {
            case 1: {
                do {
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
                                mostrar_titulo();

                                if (testar_reserva_ativa(r->id_cliente) != 0) {
                                    printf("\n\n\tCLIENTE POSSUI RESERVA ATIVA E SERA ALTERADA PARA A ATUAL!\n");
                                }

                                printf("\n\t\t(1) CONFIRMAR CLIENTE (0) CANCELAR : ");
                                scanf(" %d", &confirm);

                                if (confirm == 1) return r->id_cliente;

                            } else break;
                        }
                        case 2: {
                            r->id_cliente = listar_clientes();

                            if (r->id_cliente) {
                                mostrar_titulo();

                                if (testar_reserva_ativa(r->id_cliente) != 0) {
                                    printf("\n\n\tCLIENTE POSSUI RESERVA ATIVA E SERA ALTERADA PARA A ATUAL!\n");
                                }

                                printf("\n\t\t(1) CONFIRMAR CLIENTE (0) CANCELAR : ");
                                scanf(" %d", &confirm);

                                if (confirm == 1) return r->id_cliente;

                            } else continue;
                        }
                        case 3: {
                            printf("\n\t\tINSIRA O ID: ");
                            scanf(" %d", &id);

                            if (testar_id(id, "clientes")) {
                                mostrar_titulo();

                                montar_cliente_busca(id, NULL);

                                if (testar_reserva_ativa(r->id_cliente) != 0) {
                                    printf("\n\n\tCLIENTE POSSUI RESERVA ATIVA E SERA ALTERADA PARA A ATUAL!\n");
                                }

                                printf("\n\n\t\t(1) CONFIRMAR CLIENTE (0) CANCELAR : ");
                                scanf(" %d", &confirm);

                                if (confirm == 1) {
                                    r->id_cliente = id;

                                    return r->id_cliente;
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
                return r->id_cliente;
            }
            case 0: {
                return 0;
            }
            default: {
                printf("\n\t\tOPCAO INVALIDA");
                pausa();
                break;
            }
        }
    } while (1);

}

int testar_reserva_ativa(int cliente) {
    char sql[200];
    char str[10];
    int reserva;

    strcpy(sql, "select id_reserva from clientes where id = ");
    snprintf(str, 10, "%d", cliente);
    strcat(sql, str);
    strcat(sql, ";");

    executar_sql(sql, montar_qtd, &reserva);

    return reserva;
}

void montar_reserva_busca(int id, RESERVA *reserva) {
    RESERVA r;
    char id_char[6];
    snprintf(id_char, 6, "%d", id);

    db_listar_reservas("id", id_char, 1, "id", &r, montar_reserva_sql);
    exibir_struct_reserva(&r);

    if (reserva != NULL)
        *reserva = r;
}

int montar_reserva_sql(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna) {
    if (ptr == NULL) return -1;

    RESERVA *r = (RESERVA *) ptr;
    char reserva[10][50] = {0};
    int index = 0;
    char *pt;

    pt = strtok(valor_na_coluna[2], " ");

    while (pt != NULL) {
        pt = strtok(NULL, "\n\t\t");
        strcpy(reserva[index], pt);
        index++;
        pt = strtok(NULL, " ");
    }

    int id_tmp;

    id_tmp = (int) strtol(reserva[0], NULL, 10);
    r->id = id_tmp;

    id_tmp = (int) strtol(reserva[1], NULL, 10);
    r->id_cliente = id_tmp;

    id_tmp = (int) strtol(reserva[2], NULL, 10);
    r->id_quarto = id_tmp;

    formatar_data_struct(&r->inicio, reserva[3]);
    formatar_data_struct(&r->fim, reserva[4]);

    return 0;
}
