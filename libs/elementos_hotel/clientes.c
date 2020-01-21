//
// Created by diego on 07/01/2020.
//

#include <stdio.h>
#include <string.h>

#include "clientes.h"
#include "../extrafuncs.h"
#include "../database.h"
#include "../browserdb.h"


CLIENTE criar_novo_cliente() {
    char sql[300];
    CLIENTE c;

    c.id_reserva = 0;
    c.id_quarto = 0;

    pegar_dados_cliente(&c);
    formatar_insert_cliente(&c, sql);
    registrar_cliente(sql);

    return c;
}

int montar_cliente_sql(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna) {
    CLIENTE *c = (CLIENTE *) ptr;
    strcpy(c->nome, valor_na_coluna[2]);
    return 0;
}

int busca_cliente(char *coluna, char *valor, int *ids) {
    int qtd_resultados;
    qtd_resultados = db_listar_clientes(coluna, valor, -1, NULL, ids, exibir_resultados);
    return qtd_resultados;
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

void listar_clientes(char *filter) {
    db_listar_clientes(str_null, str_null, -1, NULL, NULL, exibir_resultados);
}

void pegar_dados_cliente(CLIENTE *c) {
    limpar_tela();
    printf("\n\n\t\t\t-------- ADICIONAR DADOS DO CLIENTE --------\n\n");
    printf("\n\t\tNOME DO CLIENTE: ");
    limpar_teclado();
    fgets(c->nome, 31, stdin);
    remover_quebra(c->nome);
    printf("\t\tSOBRENOME DO CLIENTE: ");
    limpar_teclado();
    fgets(c->sobrenome, 31, stdin);
    remover_quebra(c->sobrenome);
    printf("\t\tCPF (SOMENTE NUMEROS): ");
    limpar_teclado();
    fgets(c->cpf, 15, stdin);
    remover_quebra(c->cpf);
    printf("\t\tTELEFONE DE CONTATO: ");
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

void buscar_cliente_edicao(int id) {
    CLIENTE c;
    char id_char[6];
    snprintf(id_char, 6, "%d", id);

    db_listar_clientes("id", id_char, 1, NULL, &c, montar_cliente_sql);
    printf("\n\nnome: %s\n\n", c.nome);
    pausa();
}

void exibir_menu_clientes() {
    int opcao;
    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tCLIENTES\n\n");
        printf("\t\t(1) REGISTRAR CLIENTE\n\n");
        printf("\t\t (2) EDITAR CLIENTE REGISTRADO\n\n");
        printf("\t\t  (3) REMOVER CLIENTE\n\n");
        printf("\t\t   (4) BUSCAR CLIENTE REGISTRADO\n\n");
        printf("\t\t    (5) LISTAR CLIENTES\n\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                criar_novo_cliente();
                break;
            case 2:
                exibir_menu_editar_cliente();
                break;
            case 3:
                exibir_menu_remover_cliente();
                break;
            case 4:
                limpar_tela();
                buscar_cliente();
                break;
            case 5:
                limpar_tela();
                exibir_menu_listar_clientes();
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

void buscar_cliente() {
    char filter[50];
    char value[50];
    int ids_encontrados[100] = {0};
    int id;

    if (montar_busca_cliente(filter, value) == 1) {
        limpar_tela();

        int total_resultados = db_listar_clientes(filter, value, -1, "nome", ids_encontrados, exibir_resultados);

        if (total_resultados == 0) {
            printf("\n\t\tNENHUM RESULTADO ENCONTRADO\n");
            pausa();
            return;
        } else {
            printf("\n\t\t(0) VOLTAR\n\t\tINSERIR ID: ");
            scanf(" %d", &id);

//            for (int i = 0; ids_encontrados[i] != 0; i++)printf(" %d ", ids_encontrados[i]);

            if (id <= 0)
                return;
            else {
                ids_encontrados[0] = -1;
                if (is_in(id, ids_encontrados, total_resultados + 1)) {
                    buscar_cliente_edicao(id);
                } else {
                    printf("\n\t\tID NAO LISTADO\n");
                    pausa();
                    return;
                }
            }
        }
    }
}

int exibir_menu_listar_clientes() {
    int opcao;
    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tLISTAR CLIENTES\n\n");
        printf("\t\t(1) LISTAR TODOS OS CLIENTES REGISTRADOS\n");
        printf("\t\t (2) LISTAR CLIENTES COM RESERVA ATIVA\n");
        printf("\t\t  (3) REMOVER CLIENTES SEM RESERVA ATIVA\n\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                db_listar_clientes(str_null, str_null, -1, "nome", NULL, exibir_resultados);
                break;
            case 2:
                db_listar_clientes("id_reserva!", "0", -1, "nome", NULL, exibir_resultados);
                break;
            case 3:
                db_listar_clientes("id_reserva", "0", -1, "nome", NULL, exibir_resultados);
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


void exibir_menu_remover_cliente() {

}

void exibir_menu_editar_cliente() {
    int opcao;
    int id;
    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tEDITAR CLIENTE\n\n");
        printf("\t\t(1) BUSCAR CLIENTE PARA EDICAO\n");
        printf("\t\t (2) LISTAR CLIENTES\n");
        printf("\t\t  (3) INSERIR ID CLIENTES\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                montar_busca_cliente(NULL, NULL);
                break;
            case 2:
                exibir_menu_listar_clientes();
                break;
            case 3:
                printf("\n\n\t\tID: ");
                scanf(" %d", &id);
                buscar_cliente_edicao(id);
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

int montar_busca_cliente(char *filter, char *value) {
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