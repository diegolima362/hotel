//
// Created by diego on 07/01/2020.
//

#include "reservas.h"

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

void nova_reserva() {
    RESERVA r;
    CLIENTE c;

    char opcao[2];

    limpar_tela();
    mostrar_titulo();

    do {
        printf("\n\n\n\t\tPERIODO DE HOSPEDAGEM\n\n");
        inserir_data_reserva(&r.inicio, &r.fim);

        selecionar_quarto(&r.inicio, &r.fim, &r.id_quarto);

        printf("\n\n\t\tCONFIRMAR DADOS (S) (N): ");
        scanf(" %s", opcao);
        if (opcao[0] == 's' || opcao[0] == 'S') break;
    } while (1);

    pegar_dados_cliente(&c);

    gerar_id("clientes", &c.id);
    gerar_id("reservas", &r.id);

    r.id_cliente = c.id;
    c.id_reserva = r.id;
    c.id_quarto = r.id_quarto;

    registrar_cliente(&c);
    registrar_reserva(&r);
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
    qtd_resultados = listar_clientes(coluna, valor, -1, ids, exibir_resultados);
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
                pegar_dado_pesquisa(dados_busca, 50);
                busca_cliente("NOME", dados_busca, NULL);
                break;
            case 2:
                printf("\n\t\tINSIRA O CPF: ");
                pegar_dado_pesquisa(dados_busca, 50);
                busca_cliente("NOME", dados_busca, NULL);
                break;
            case 3:
                printf("\n\t\tINSIRA O ID: ");
                pegar_dado_pesquisa(dados_busca, 50);
                busca_cliente("NOME", dados_busca, NULL);
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