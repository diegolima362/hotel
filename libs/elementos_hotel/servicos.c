//
// Created by diego on 07/01/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../extrafuncs.h"
#include "../database.h"
#include "../browserdb.h"

#define STR_SIZE 1000
#define PATH_FATURAS "data/faturas/"

#define SQL_SIZE 1000

void exibir_fatura(void *io);

int montar_fatura(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna);

int s_exibir_resultados(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna) {

    for (int i = 0; i < qtd_colunas; i++) {
        upper(valor_na_coluna[i]);
        upper(nome_da_coluna[i]);
        fprintf(ptr, "\t\t%s ", nome_da_coluna[i]);
        fprintf(ptr, "%s\n", valor_na_coluna[i]);
        fprintf(stdout, "\t\t%s ", nome_da_coluna[i]);
        fprintf(stdout, "%s\n", valor_na_coluna[i]);
    }

    return 0;
}

void testar_services() {
//    char path[50];
//    strcpy(path, PATH_FATURAS);
//    strcat(path, "diego.txt");
//    puts(path);
//
//    FILE *fatura = fopen(path, "w+");
//
//
//    exibir_fatura(fatura);
//    exibir_fatura(stdout);
//    fclose(fatura);

    FILE *f = fopen("data/faturas/diego.txt", "w");

    char sql[SQL_SIZE];

    strcpy(sql,
           "select date('now') as '\n\t\tdata de finalizacao: ', c.nome || ' ' || c.sobrenome as '\n\t\tnome:' , c.cpf || '\n' as 'cpf:', "
           "c.id_reserva as 'reserva:', c.id_quarto  || '\n' as 'num. quarto:', "
           "r.inicio || ' ' || r.fim || '\n' as 'periodo da reserva:', 'detalhamento de debitos -\n' as '-'"
           "from clientes c join reservas r on c.id_reserva = r.id where c.id = 1;");
    executar_sql(sql, s_exibir_resultados, f);

    strcpy(sql,
           "select p.id as 'id pedido: ', s.descricao || ' *' || d.quantidade as 'servico: ', s.valor as 'valor: ', p.data as 'data: ', ' ' as '-----------------------------------'"
           "from servicos s join detalhes_pedido d on d.id_servico = s.id join pedidos p on d.id_pedido = p.id "
           "join reservas r on p.id_reserva = r.id where r.id_cliente = 1;");
    executar_sql(sql, s_exibir_resultados, f);

    strcpy(sql,
           "select tota_dias as '\n\t\tdiarias: ', valor as 'valor da diaria: ', (tota_dias * valor) as 'total da reserva: ', sum(subtotal) as '\n\t\tvalor dos servicos contratados: ', "
           "sum(subtotal + (tota_dias * valor)) || '\n' as '\n\t\t-------------------------------------------\n\n\t\ttotal da fatura: ' from (select s.valor * d.quantidade as subtotal, r.fim, r.inicio, q.valor, julianday(fim) - julianday(inicio) as tota_dias "
           "from servicos s join detalhes_pedido d on d.id_servico = s.id join pedidos p on d.id_pedido = p.id join reservas r on p.id_reserva = r.id join quartos q on r.id_quarto = q.id where r.id_cliente = 1);");
    executar_sql(sql, s_exibir_resultados, f);

    fclose(f);
}

int montar_fatura(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna) {
    return 0;
}

void exibir_fatura(void *io) {
    fprintf(io, "hello");
}

void exibir_menu_gerenciar_servicos() {
    int opcao;
    do {
        mostrar_titulo();
        printf("\n\t\tSERVICOS\n");
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
