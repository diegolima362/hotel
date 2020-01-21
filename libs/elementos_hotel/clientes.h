//
// Created by diego on 07/01/2020.
//

#ifndef HOTEL_CLIENTES_H
#define HOTEL_CLIENTES_H

#endif //HOTEL_CLIENTES_H

typedef struct end {
    char rua[60 + 1];
    int num;
    char bairro[60 + 1];
    char cidade[60 + 1];
    char estado[30 + 1];
    char pais[30 + 1];
} ENDERECO;

typedef struct clientes {
    int id;
    int id_reserva;
    int id_quarto;
    char nome[31];
    char sobrenome[31];
    char cpf[15];
    char cred_card[20];
    char phone[15];
    //struct end end;
    //int ativo;
} CLIENTE;

CLIENTE criar_novo_cliente();

int montar_cliente_sql(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna);

int busca_cliente(char *coluna, char *valor, int *ids);

void buscar_cliente();

char *formatar_insert_cliente(CLIENTE *c, char *sql);

void listar_clientes(char *filter);

void pegar_dados_cliente(CLIENTE *c);

void buscar_cliente_edicao(int id);

void exibir_menu_clientes();

int exibir_menu_listar_clientes();

void exibir_menu_remover_cliente();

void exibir_menu_editar_cliente();

int montar_busca_cliente(char *filter, char *value);