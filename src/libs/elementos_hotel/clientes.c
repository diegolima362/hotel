//
// Created by diego on 07/01/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clientes.h"
#include "../extrafuncs.h"
#include "../database.h"
#include "../browserdb.h"

#define LIMIT_BUSCA 1000

void exibir_menu_editar_cliente();

void exibir_menu_remover_cliente();

int exibir_menu_buscar_clientes(char *filter, char *value);

int exibir_menu_listar_clientes(char *column, char *filter);

int montar_cliente_sql(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna);

void pegar_dados_cliente(CLIENTE *c);

void exibir_struct_cliente(CLIENTE *c);

void visualizar_clientes(int (*pFunction)(char *, char *));

void remover_cliente_id(int id);

int selecionar_cliente(int (*pFunction)(char *, char *), CLIENTE *cliente);

void editar_dados_cliente(CLIENTE *c);

char *formatar_insert_cliente(CLIENTE *c, char *sql);

void formatar_update_cliente(CLIENTE *c, char *sql);

// menus

void exibir_menu_gerenciar_clientes() {
    int opcao;

    do {
        mostrar_titulo();
        printf("\n\n\t\tCLIENTES\n\n");
        printf("\t\t(1) REGISTRAR CLIENTE\n\n");
        printf("\t\t (2) EDITAR CLIENTE REGISTRADO\n\n");
        printf("\t\t  (3) REMOVER CLIENTE\n\n");
        printf("\t\t   (4) BUSCAR CLIENTE REGISTRADO\n\n");
        printf("\t\t    (5) LISTAR CLIENTES\n\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPCAO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                registrar_cliente();
                break;
            case 2:
                exibir_menu_editar_cliente();
                break;
            case 3:
                exibir_menu_remover_cliente();
                break;
            case 4:
                visualizar_clientes(exibir_menu_buscar_clientes);
                break;
            case 5:
                visualizar_clientes(exibir_menu_listar_clientes);
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

int registrar_cliente() {
    char sql[300];
    CLIENTE c;

    gerar_id("clientes", &c.id);
    c.id_reserva = 0;
    c.id_quarto = 0;

    pegar_dados_cliente(&c);
    formatar_insert_cliente(&c, sql);
    executar_sql(sql, NULL, NULL);

    return c.id;
}

void exibir_menu_editar_cliente() {
    CLIENTE c;
    int opcao;
    int id;

    do {
        mostrar_titulo();
        printf("\n\n\t\tEDITAR CLIENTE\n\n");
        printf("\t\t(1) BUSCAR CLIENTE PARA EDICAO\n");
        printf("\t\t (2) LISTAR CLIENTES\n");
        printf("\t\t  (3) INSERIR ID DO CLIENTES\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPCAO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                id = selecionar_cliente(exibir_menu_buscar_clientes, &c);
                editar_dados_cliente(&c);
                break;
            case 2:
                id = selecionar_cliente(exibir_menu_listar_clientes, &c);
                editar_dados_cliente(&c);
                break;
            case 3:
                printf("\n\n\t\tID: ");
                scanf(" %d", &id);
                if (testar_id(id, "cliente"))
                    editar_dados_cliente(&c);
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

void exibir_menu_remover_cliente() {
    int opcao;
    int id;
    do {
        mostrar_titulo();
        printf("\n\n\t\tREMOVER CLIENTE\n\n");
        printf("\t\t(1) BUSCAR CLIENTES PARA REMOCAO\n");
        printf("\t\t (2) LISTAR CLIENTES PARA REMOCAO\n");
        printf("\t\t  (3) INSERIR ID DO CLIENTE\n\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPCAO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                id = selecionar_cliente(exibir_menu_buscar_clientes, NULL);
                remover_cliente_id(id);
                break;
            case 2:
                id = selecionar_cliente(exibir_menu_listar_clientes, NULL);
                remover_cliente_id(id);
                break;
            case 3:
                printf("\n\n\t\tID: ");
                scanf(" %d", &id);
                if (testar_id(id, "cliente"))
                    remover_cliente_id(id);
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

int exibir_menu_buscar_clientes(char *filter, char *value) {
    int opcao;
    char dado_busca[50];

    while (1) {
        mostrar_titulo();
        printf("\n\tBUSCAR CLIENTE\n\n");
        printf("\t\t(1) BUSCAR POR NOME\n\n");
        printf("\t\t  (2) BUSCAR POR CPF\n\n");
        printf("\t\t    (3) BUSCAR POR ID\n\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPCAO: ");
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

int exibir_menu_listar_clientes(char *column, char *filter) {
    int opcao;
    while (1) {
        mostrar_titulo();
        printf("\n\n\t\tLISTAR CLIENTES\n\n");
        printf("\t\t(1) LISTAR TODOS OS CLIENTES REGISTRADOS\n");
        printf("\n\t\t (2) LISTAR CLIENTES COM RESERVA ATIVA\n");
        printf("\n\t\t  (3) LISTAR CLIENTES SEM RESERVA ATIVA\n\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPCAO: ");
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

int montar_cliente_sql(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna) {
    if (ptr == NULL) return -1;

    CLIENTE *c = (CLIENTE *) ptr;
    char cliente[10][50] = {0};
    int index = 0;
    char *pt;

    pt = strtok(valor_na_coluna[2], " ");

    while (pt != NULL) {
        pt = strtok(NULL, "\n\t\t");
        strcpy(cliente[index], pt);
        index++;
        pt = strtok(NULL, " ");
    }

    int id_tmp;
    char *nome_tmp;

    id_tmp = (int) strtol(cliente[0], NULL, 10);
    c->id = id_tmp;

    nome_tmp = strtok(cliente[1], " ");
    strcpy(c->nome, nome_tmp);

    nome_tmp = strtok(NULL, "\0");
    strcpy(c->sobrenome, nome_tmp);

    strcpy(c->cpf, cliente[2]);

    strcpy(c->phone, cliente[3]);

    id_tmp = (int) strtol(cliente[4], NULL, 10);
    c->id_reserva = id_tmp;

    id_tmp = (int) strtol(cliente[5], NULL, 10);
    c->id_quarto = id_tmp;

    return 0;
}

void pegar_dados_cliente(CLIENTE *c) {
    mostrar_titulo();
    printf("\n\n\t\t\t-------- ADICIONAR DADOS DO CLIENTE --------\n\n");
    printf("\n\n\t\tNOME DO CLIENTE: ");
    limpar_teclado();
    fgets(c->nome, 31, stdin);
    remover_quebra(c->nome);
    printf("\n\t\tSOBRENOME DO CLIENTE: ");
    limpar_teclado();
    fgets(c->sobrenome, 31, stdin);
    remover_quebra(c->sobrenome);
    printf("\n\t\tCPF (SOMENTE NUMEROS): ");
    limpar_teclado();
    fgets(c->cpf, 15, stdin);
    remover_quebra(c->cpf);
    printf("\n\t\tTELEFONE DE CONTATO: ");
    limpar_teclado();
    fgets(c->phone, 20, stdin);
    remover_quebra(c->phone);

//    printf("\t\tCARTAO DE CREDITO: ");
//    limpar_teclado();
//    fgets(c->cred_card, 21, stdin);
//    remover_quebra(c->cred_card);

//    puts("\n\t\t\t>>> INSERIR ENDERECO \n");
//    printf("\n\t\tRUA: ");
//    limpar_teclado();
//    fgets(c->end.rua, 61, stdin);
//    remover_quebra(c->end.rua);
//    printf("\t\tNUMERO: ");
//    limpar_teclado();
//    scanf(" %d", &c->end.num);
//    printf("\t\tBAIRRO: ");
//    limpar_teclado();
//    fgets(c->end.bairro, 61, stdin);
//    remover_quebra(c->end.bairro);
//    printf("\t\tCIDADE: ");
//    limpar_teclado();
//    fgets(c->end.cidade, 61, stdin);
//    remover_quebra(c->end.cidade);
//    printf("\t\tESTADO: ");
//    limpar_teclado();
//    fgets(c->end.estado, 31, stdin);
//    remover_quebra(c->end.estado);
//    printf("\t\tPAIS: ");
//    limpar_teclado();
//    fgets(c->end.pais, 31, stdin);
//    remover_quebra(c->end.pais);

}

void montar_cliente_busca(int id, CLIENTE *cliente) {
    CLIENTE c;
    char id_char[6];
    snprintf(id_char, 6, "%d", id);

    db_listar_clientes("id", id_char, 1, "id", &c, montar_cliente_sql);
    exibir_struct_cliente(&c);

    if (cliente != NULL)
        *cliente = c;
}

void exibir_struct_cliente(CLIENTE *c) {
    printf("\n\t\tID: %d", c->id);
    printf("\n\t\tNOME: %s %s", c->nome, c->sobrenome);
    printf("\n\t\tCPF: %s", c->cpf);
    printf("\n\t\tPHONE: %s", c->phone);
    printf("\n\t\tRESERVA: %d", c->id_reserva);
    printf("\n\t\tQUARTO: %d", c->id_quarto);
}

int buscar_clientes() {
    return selecionar_cliente(exibir_menu_buscar_clientes, NULL);
}

int listar_clientes() {
    return selecionar_cliente(exibir_menu_listar_clientes, NULL);
}

void visualizar_clientes(int (*pFunction)(char *, char *)) {
    CLIENTE c;
    int op;
    int id;

    while (1) {
        id = selecionar_cliente(pFunction, &c);

        if (id == 0)
            break;

        printf("\n\t\t(1) EDITAR CLIENTE (2) REMOVER CLIENTE (3) VOLTAR (0) SAIR\n\t\tOPCAO: ");
        scanf(" %d", &op);

        if (op == 1)
            editar_dados_cliente(&c);
        else if (op == 2)
            remover_cliente_id(id);
        else if (op == 3)
            continue;
        else break;
    }
}

void remover_cliente_id(int id) {
    char id_char[5];
    snprintf(id_char, 5, "%d", id);
    db_remover_dado("clientes", "id", id_char);
}

int selecionar_cliente(int (*pFunction)(char *, char *), CLIENTE *cliente) {
    char column[50];
    char filter[50];
    int ids_encontrados[LIMIT_BUSCA] = {0};
    int id;

    if (pFunction(column, filter)) {
        mostrar_titulo();
        puts("\n\n\t\tRESULTADOS\n\n");

        int total_resultados = db_listar_clientes(column, filter, LIMIT_BUSCA, "id", ids_encontrados,
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

                    mostrar_titulo();
                    montar_cliente_busca(id, cliente);

                    printf("\n\n\t\t(1) SELECIONAR CLIENTE (0) VOLTAR :  ");
                    scanf(" %d", &confirm);

                    return confirm == 1 ? id : selecionar_cliente(pFunction, NULL);

                } else {
                    printf("\n\t\tID NAO LISTADO\n");
                    pausa();
                    return 0;
                }
            }
        }
    }
    return 0;
}

void editar_dados_cliente(CLIENTE *c) {
    mostrar_titulo();
    printf("\n\n\t\tEDITAR DADOS DO CLIENTE\n\n");
    pegar_dados_cliente(c);

    mostrar_titulo();
    printf("\n\n\t\tEDITAR DADOS DO CLIENTE\n\n");
    exibir_struct_cliente(c);

    int op;
    printf("\n\t\t(1) CONFIRMAR  (2) REINICIAR EDICAO  (0) CANCELAR\n\t\tOPCAO: ");
    scanf(" %d", &op);

    char sql[500];

    if (op == 1) {
        formatar_update_cliente(c, sql);
        executar_sql(sql, NULL, NULL);

        mostrar_titulo();
        printf("\n\t\tFINALIZADO\n");
        pausa();
    } else if (op == 2) {
        editar_dados_cliente(c);
    } else return;

}

char *formatar_insert_cliente(CLIENTE *c, char *sql) {
    char str[10];
    strcpy(sql, "insert into clientes values (null, '");
    strcat(sql, c->nome);
    strcat(sql, "', '");
    strcat(sql, c->sobrenome);
    strcat(sql, "', '");
    strcat(sql, c->cpf);
    strcat(sql, "', '");
    strcat(sql, c->phone);
    strcat(sql, "', ");
    snprintf(str, 10, "%d", c->id_quarto);
    strcat(sql, str);
    strcat(sql, ", ");
    snprintf(str, 10, "%d", c->id_reserva);
    strcat(sql, str);
    strcat(sql, ");");

    return sql;
}

void formatar_update_cliente(CLIENTE *c, char *sql) {
    char str[10];

    strcpy(sql, "update clientes set nome = '");
    strcat(sql, c->nome);

    strcat(sql, "', sobrenome = '");
    strcat(sql, c->sobrenome);

    strcat(sql, "', cpf = '");
    strcat(sql, c->cpf);

    strcat(sql, "', phone = '");
    strcat(sql, c->phone);

    strcat(sql, "', where id = ");
    snprintf(str, 10, "%d", c->id);
    strcat(sql, str);
    strcat(sql, ";");
}
