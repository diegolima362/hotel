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

void montar_cliente_sql(char *str, CLIENTE *c);

int busca_cliente(char *coluna, char *valor, int *ids);

char *formatar_cliente(CLIENTE *c);

void listar_todos_clientes();

void pegar_dados_cliente(CLIENTE *c);