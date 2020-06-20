//
// Created by diego on 07/01/2020.
//

#include <stdio.h>
#include <string.h>
#include "../extrafuncs.h"
#include "../database.h"
#include "../browserdb.h"
#include "reservas.h"

#define SQL_SIZE 1000

#define LIMIT_BUSCA 100

void listar_servicos();

void criar_pedido();

int selecionar_servico();

int adicionar_item(int *id_item, int *qtd);

void registrar_item_pedido(int pedido, int produto, int quantidade);

void registrar_pedido(int reserva);

void gerar_extrato(FILE *file, int id_reserva);

void criar_novo_servico();

void exibir_menu_editar_servico();

void exibir_menu_remover_servico();

void exibir_dados_pedido(int pedido);

void registrar_novo_servico(char descricao[500], char valor[10]);

void remover_servico_id(int id);

void editar_servico(int id, char *column, char *valor);

int checar_servicos_contrados(int reserva);

int mostrar_fatura(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna) {

    for (int i = 0; i < qtd_colunas; i++) {
        upper(valor_na_coluna[i]);
        upper(nome_da_coluna[i]);

        if (ptr != NULL) {
            fprintf(ptr, "\t\t%s ", nome_da_coluna[i]);
            fprintf(ptr, "%s\n", valor_na_coluna[i]);
        }

        fprintf(stdout, "\t\t%s ", nome_da_coluna[i]);
        fprintf(stdout, "%s\n", valor_na_coluna[i]);
    }

    return 0;
}

int exibir_service(void *ptr, int qtd_colunas, char **valor_na_coluna, char **nome_da_coluna) {

    for (int i = 0; i < qtd_colunas; i++) {
        upper(valor_na_coluna[i]);
        upper(nome_da_coluna[i]);
        fprintf(stdout, "\t\t%s ", nome_da_coluna[i]);
        fprintf(stdout, "%s\n", valor_na_coluna[i]);
    }

    return 0;
}

void gerar_fatura_reserva_finalizada(int reserva) {
    char nome_fatura[100];
    char aux[10];

    snprintf(aux, 10, "%d", reserva);
    strcpy(nome_fatura, "data/faturas/");
    strcat(nome_fatura, "fatura_id_reserva_");
    strcat(nome_fatura, aux);
    strcat(nome_fatura, ".txt");

    FILE *f = fopen(nome_fatura, "w");
    gerar_extrato(f, reserva);
    fclose(f);
}

void gerar_extrato(FILE *file, int id_reserva) {
    char sql[SQL_SIZE];
    char aux[10];
    snprintf(aux, 10, "%d", id_reserva);

    strcpy(sql, "select ");

    if (file != NULL) {
        strcat(sql, " date('now') as '\n\t\tdata de finalizacao: ', ");
    }

    strcat(sql, " c.nome || ' ' || c.sobrenome as '\n\t\tnome:' , c.cpf || '\n' as 'cpf:', "
                "c.id_reserva as 'reserva:', c.id_quarto  || '\n' as 'num. quarto:', "
                "r.inicio || ' ' || r.fim || '\n' as 'periodo da reserva:', 'detalhamento de debitos -\n' as '-'"
                "from clientes c join reservas r on c.id_reserva = r.id where r.id = ");
    strcat(sql, aux);
    strcat(sql, " ;");
    executar_sql(sql, mostrar_fatura, file);
    int qtd = checar_servicos_contrados(id_reserva);
    if (qtd > 0) {
        strcpy(sql,
               "select p.id as 'id pedido: ', s.descricao || ' *' || d.quantidade as 'servico: ', s.valor as 'valor: ', p.data as 'data: ', ' ' as '-----------------------------------'"
               "from servicos s join detalhes_pedido d on d.id_servico = s.id join pedidos p on d.id_pedido = p.id "
               "join reservas r on p.id_reserva = r.id where r.id = ");
        strcat(sql, aux);
        strcat(sql, " ;");
        executar_sql(sql, mostrar_fatura, file);

        strcpy(sql,
               "select tota_dias as '\n\t\tdiarias: ', valor as 'valor da diaria: ', (tota_dias * valor) as 'total da reserva: ', sum(subtotal) as '\n\t\tvalor dos servicos contratados: ', "
               "sum(subtotal + (tota_dias * valor)) || '\n' as '\n\t\t-------------------------------------------\n\n\t\ttotal da fatura: ' from (select s.valor * d.quantidade as subtotal, r.fim, r.inicio, q.valor, julianday(fim) - julianday(inicio) as tota_dias "
               "from servicos s join detalhes_pedido d on d.id_servico = s.id join pedidos p on d.id_pedido = p.id join reservas r on p.id_reserva = r.id join quartos q on r.id_quarto = q.id where r.id = ");
        strcat(sql, aux);
        strcat(sql, " );");
        executar_sql(sql, mostrar_fatura, file);
    } else {
        strcpy(sql,
               "select tota_dias as '\n\t\tdiarias: ', valor as 'valor da diaria: ', (tota_dias * valor) as 'total da reserva: ', "
               "sum(tota_dias * valor) || '\n' as '\n\t\t-------------------------------------------\n\n\t\ttotal da fatura: ' from (select r.fim, r.inicio, q.valor, julianday(fim) - julianday(inicio) as tota_dias "
               "from reservas r join quartos q on r.id_quarto = q.id where r.id = ");
        strcat(sql, aux);
        strcat(sql, " );");
        executar_sql(sql, mostrar_fatura, file);
    }
}

int checar_servicos_contrados(int reserva) {
    char sql[200];
    char aux[10];
    int qtd;

    snprintf(aux, 10, "%d", reserva);
    strcpy(sql, "select count(*) from servicos s join "
                "detalhes_pedido d on d.id_servico = s.id "
                "join pedidos p on d.id_pedido = p.id "
                "join reservas r on p.id_reserva = r.id where r.id = ");
    strcat(sql, aux);
    strcat(sql, ";");

    executar_sql(sql, montar_qtd, &qtd);
    return qtd;
}

void exibir_menu_gerenciar_servicos() {
    int opcao;
    do {
        mostrar_titulo();
        printf("\n\t\tSERVICOS\n");
        printf("\n\t\t(1) CONTRATAR SERVICO\n");
        printf("\n\t\t (2) NOVO SERVICO\n");
        printf("\n\t\t  (3) EDITAR SERVICO\n");
        printf("\n\t\t   (4) LISTAR SERVICOS\n");
        printf("\n\t\t    (5) REMOVER SERVICO\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPCAO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                criar_pedido();
                break;
            case 2:
                criar_novo_servico();
                break;
            case 3:
                exibir_menu_editar_servico();
                break;
            case 4:
                listar_servicos();
                pausa();
                break;
            case 5:
                exibir_menu_remover_servico();
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

void criar_novo_servico() {
    char descricao[100];

    char valor[10];

    mostrar_titulo();
    printf("\n\t\tCRIAR NOVO SERVICO\n");

    printf("\n\t\tNOME DO SERVICO (MAX 100 CARACTERES) : ");
    limpar_teclado();
    fgets(descricao, 100, stdin);
    remover_quebra(descricao);

    printf("\n\t\tVALOR DO SERVICO: ");
    limpar_teclado();
    fgets(valor, 10, stdin);
    remover_quebra(valor);

    registrar_novo_servico(descricao, valor);

    mostrar_titulo();
    printf("\n\n\t\tSERVICO REGISTRADO!\n\n");
    pausa();
}

void registrar_novo_servico(char descricao[500], char valor[10]) {
    char sql[SQL_SIZE];
    strcpy(sql, "insert into servicos(descricao, valor) values ('");
    strcat(sql, descricao);
    strcat(sql, "', ");
    strcat(sql, valor);
    strcat(sql, ");");
    executar_sql(sql, NULL, NULL);
}

void exibir_menu_editar_servico() {
    int id;
    int op;
    char dado[100];

    while (1) {
        id = selecionar_servico();
        if (id == 0)
            return;

        while (1) {
            mostrar_titulo();
            printf("\n\n\t\t(1) EDITAR NOME");
            printf("\n\n\t\t (2) EDITAR VALOR\n");
            printf("\n\n\n\t\t(0) VOLTAR\n\n");
            printf("\t\tOPCAO: ");
            scanf(" %d", &op);

            if (op == 0)
                break;
            else if (op == 1) {
                printf("\n\n\t\tINSIRA O NOME: ");
                limpar_teclado();
                fgets(dado, 100, stdin);
                remover_quebra(dado);
                editar_servico(id, "descricao", dado);
                mostrar_titulo();
                printf("\n\n\t\tDADOS SALVOS!\n\n");
                pausa();

            } else if (op == 2) {
                printf("\n\n\t\tINSIRA O VALOR: ");
                limpar_teclado();
                fgets(dado, 100, stdin);
                remover_quebra(dado);
                editar_servico(id, "valor", dado);
                mostrar_titulo();
                printf("\n\n\t\tDADOS SALVOS!\n\n");
                pausa();

            } else {
                printf("\n\n\t\tOPCAO INVALIDA!\n\n");
                pausa();
            }
        }
    }
}

void editar_servico(int id, char *column, char *valor) {
    char sql[SQL_SIZE];
    char aux[10];

    snprintf(aux, 10, "%d", id);

    strcpy(sql, "update servicos set ");
    strcat(sql, column);
    strcat(sql, " = '");
    strcat(sql, valor);
    strcat(sql, "' where id = ");
    strcat(sql, aux);
    strcat(sql, ";");

    executar_sql(sql, NULL, NULL);
}

void listar_servicos() {
    char sql[SQL_SIZE];

    strcpy(sql,
           "select id as 'id:', descricao as 'servico:', valor as 'valor:', ' \n' as '-----------------------------------------------' from servicos");

    mostrar_titulo();

    executar_sql(sql, exibir_service, NULL);
}

void exibir_menu_remover_servico() {
    int op;
    int id;

    while (1) {

        id = selecionar_servico();

        if (id == 0)
            return;

        printf("\n\t\t(1) CONFIRMAR (0) CANCELAR : ");
        scanf(" %d", &op);

        if (op == 1) {
            remover_servico_id(id);

            mostrar_titulo();
            printf("\n\n\t\tSERVICO REMOVIDO!\n\n");
            pausa();

        } else if (op == 0) {
            printf("\n\t\tCANCELADO!\n");
            pausa();
            return;
        } else {
            mostrar_titulo();
            printf("\n\n\t\tOPCAO INVALIDA!\n\n");
            pausa();
            return;
        }
    }
}

void remover_servico_id(int id) {
    char sql[SQL_SIZE];
    char aux[10];

    snprintf(aux, 10, "%d", id);

    strcpy(sql, "delete from servicos where id = ");
    strcat(sql, aux);
    strcat(sql, " ;");
    executar_sql(sql, NULL, NULL);
}

void criar_pedido() {
    int id_reserva;
    int id_servico = 0;
    int id_pedido = 0;
    int op;
    int qtd;

    id_reserva = selecionar_reserva();

    if (id_reserva == 0)
        return;

    gerar_id("pedidos", &id_pedido);
    registrar_pedido(id_reserva);

    do {
        if (adicionar_item(&id_servico, &qtd) == 0)
            break;

        registrar_item_pedido(id_pedido, id_servico, qtd);

        mostrar_titulo();
        printf("\n\t\t(0) FINALIZAR PEDIDO (1) ADICIONAR MAIS ITENS : ");
        scanf(" %d", &op);

        if (op == 0) {
            mostrar_titulo();
            printf("\n\t\tPEDIDO FINALIZADO!\n\n");
            exibir_dados_pedido(id_pedido);
            puts("\n");
            pausa();
            break;
        }
    } while (1);
}

void exibir_dados_pedido(int pedido) {
    char sql[SQL_SIZE];
    char aux[10];

    strcpy(sql,
           "select p.id as 'id do pedido:', p.id_reserva as 'reserva: ', r.id_cliente as 'cliente:', p.data as 'data:', 'detalhamento de debitos -\n\n' as '\n\t\t-'"
           "from pedidos p join reservas r on p.id_reserva = r.id where p.id = ");
    snprintf(aux, 10, "%d", pedido);
    strcat(sql, aux);
    strcat(sql, ";");
    executar_sql(sql, exibir_service, NULL);

    strcpy(sql,
           "select s.descricao as 'servico:', s.valor as 'valor: ', d.quantidade as 'quantidade: ', ' ' as '-----------------------------------' "
           "from servicos s join detalhes_pedido d on d.id_servico = s.id join pedidos p on d.id_pedido = p.id where p.id = ");
    snprintf(aux, 10, "%d", pedido);
    strcat(sql, aux);
    strcat(sql, ";");
    executar_sql(sql, exibir_service, NULL);

    strcpy(sql, "select sum(subtotal) as '\n\t\ttotal:' from(select s.valor * d.quantidade as subtotal "
                "from servicos s join detalhes_pedido d on d.id_servico = s.id join pedidos p on d.id_pedido = p.id where p.id = ");
    snprintf(aux, 10, "%d", pedido);
    strcat(sql, aux);
    strcat(sql, " );");
    executar_sql(sql, exibir_service, NULL);

}

void registrar_pedido(int reserva) {
    char sql[SQL_SIZE];
    char aux[10];

    strcpy(sql, "insert into pedidos(id_reserva, data) values ( ");
    snprintf(aux, 10, "%d", reserva);
    strcat(sql, aux);
    strcat(sql, ", date('now'));");

    executar_sql(sql, NULL, NULL);
}

void registrar_item_pedido(int pedido, int produto, int quantidade) {
    char sql[SQL_SIZE];
    char aux[10];

    strcpy(sql, "insert into detalhes_pedido(id_pedido, id_servico, quantidade) values ( ");
    snprintf(aux, 10, "%d", pedido);
    strcat(sql, aux);
    strcat(sql, ", ");

    snprintf(aux, 10, "%d", produto);
    strcat(sql, aux);
    strcat(sql, ", ");

    snprintf(aux, 10, "%d", quantidade);
    strcat(sql, aux);
    strcat(sql, " );");

    executar_sql(sql, NULL, NULL);
}

int adicionar_item(int *id_item, int *qtd) {
    *id_item = selecionar_servico();

    if (*id_item == 0) {
        mostrar_titulo();
        printf("\n\t\tPEDIDO CANCELADO\n");
        pausa();
        return 0;
    } else {
        printf("\n\t\tQUANTIDADE: ");
        scanf(" %d", qtd);

        if (*qtd < 1) {
            printf("\n\t\tPEDIDO CANCELADO\n");
            pausa();
            return 0;
        }
    }
}

int selecionar_servico() {
    int id;
    while (1) {
        mostrar_titulo();
        listar_servicos();
        printf("\n\n\t\t(0) CANCELAR OU INSERIR ID: ");
        scanf(" %d", &id);

        if (id == 0)
            return 0;

        if (testar_id(id, "servicos"))
            return id;
        else {
            printf("\n\t\tID INVALIDO\n");
            pausa();
        }
    }
}
