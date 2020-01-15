//
// Created by diego on 07/01/2020.
//

#include <stdio.h>
#include "cliente.h"
#include "../extrafuncs.h"
#include "../database.h"
#include "../browserdb.h"

CLIENTE criar_novo_cliente(){
    CLIENTE c;
    pegar_dados_cliente(&c);

    return c;
}

void montar_cliente_sql(char*str, CLIENTE* c){

}

int busca_cliente(char *coluna, char *valor, int *ids) {
    int qtd_resultados;
    qtd_resultados = db_listar_clientes(coluna, valor, -1, ids, exibir_resultados);
    return qtd_resultados;
}

void listar_todos_clientes() {
    limpar_tela();
    puts("\n\n\tCLIENTES REGISTRADOS");
    printf("\n\t\t%3s%20s%20s", "ID", "NOME", "CPF");
    db_listar_clientes(str_null, str_null, -1, NULL, exibir_resultados);
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