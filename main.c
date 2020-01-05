#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "libs/extrafuncs.h"
#include "libs/login.h"
#include "libs/datas.h"
#include "libs/browserdb.h"
#include "libs/database.h"

int imprimir_resultados(void *ptr, int resultados, char **STR1, char **STR2);

void mostrar_hora(struct tm *hora);

void mostrar_data(struct tm *date);

void mostrar_data_hora();

void mostrar_titulo();

void menu_principal();

void menu_configuracao();

void exibir_qtd_reservas();

void menu_dados();

int busca_cliente(char *coluna, char *valor, int *ids);

int busca_reserva(char *coluna, char *valor, int *ids);

int busca_quarto(char *coluna, char *valor, int *ids);

char *pegar_dado_pesquisa(char *valor, int size);

void buscar_reserva();

void buscar_cliente();

void menu_buscas();

void menu_reservas();

int mostrar_quartos_disponiveis(struct tm *data_inicio, struct tm *data_final, int tipo, int *index);

int selecionar_quarto(struct tm *data_inicio, struct tm *data_final, int *id_quarto);

int selecionar_tipo_quarto();

void inserir_data_reserva(struct tm *data_inicio, struct tm *data_final);

void nova_reserva();

void listar_todos_clientes();

int mostrar_cliente_recuperado(CLIENTE *c);

void pegar_dados_cliente(CLIENTE *c);

void mostrar_reserva(RESERVA *r, CLIENTE *c);

int criar_banco_de_dados();

int checar_diretorios();

int autenticar();

int criar_login(LOGIN *login);

void alterar_login();

void tela_pegar_login(LOGIN *login);

int main(int argc, char *argv[]) {

//    if (checar_diretorios() == 1 && criar_banco_de_dados() == 1) {
//        printf("\n\n\t\tBASE DE DADOS CRIADA ...\n\t\tEXECUTE O PROGRAMA NOVAMENTE\n\n");
//        exit(0);
//    }
//
//    if (autenticar()) {
//        menu_principal();
//    }
    int ids[100] = {0};
    int qtd = busca_cliente("id_quarto", "85", ids);

    printf("\nqtd: %d\n\n", qtd);
    for (int i = 0; ids[i] != 0; i++)
        printf(" %d ", ids[i]);
    return 0;
}

int imprimir_resultados(void *ptr, int resultados, char **STR1, char **STR2) {
    int i;

    for (i = 0; STR1[i] != NULL; i++) {
        printf("%s = %s\n", STR2[i], STR1[i]);
    }
    return 0;
}

void mostrar_hora(struct tm *hora) {
    struct tm t;

    if (hora == NULL) {
        t = ler_data();
    } else {
        t = *hora;
    }

    printf("%02d:%02d", t.tm_hour, t.tm_min);
}

void mostrar_data(struct tm *date) {
    struct tm t;

    if (date == NULL) {
        t = ler_data();
    } else {
        t = *date;
    }

    printf("%02d/%02d/%04d ", t.tm_mday, t.tm_mon, t.tm_year);
}

void mostrar_data_hora() {
    mostrar_data(NULL);
    mostrar_hora(NULL);
}

void mostrar_titulo() {
    printf("\n\n\t\t---- CAMPINA  COMFORT  PREMIUM ----\n\t\t\t  ");
    mostrar_data_hora();
}

void menu_principal() {

    int opcao;

    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tMENU INICIAL\n");
        printf("\n\t\t(1) GERENCIAR RESERVAS\n");
        printf("\t\t  (2) GERENCIAR DADOS DO SISTEMA\n");
        printf("\t\t    (3) MANUTENCAO\n");
        printf("\n\t\t(0) SAIR\n");
        printf("\n\t\tOPÇÃO: ");
        limpar_teclado();
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                limpar_tela();
                menu_reservas();
                break;
            case 2:
                limpar_tela();
                menu_dados();
                break;
            case 3:
                limpar_tela();
                menu_configuracao();
                break;
            case 0:
                limpar_tela();
                printf("SAINDO...\n\n");
                exit(0);

            default:
                printf("\n\nOPCAO INVALIDA!\n\n");
                pausa();
                break;
        }
    } while (opcao != 0);
}

void menu_configuracao() {
    int opcao;

    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tMANUTENCAO\n");
        printf("\n\t\t(1) ALTERAR LOGIN\n");
        printf("\t\t  (2) FAZER BACKUP DOS ARQUIVOS\n");
        printf("\t\t    (3) REMOVER TODOS OS DADOS DO SISTEMA\n");
        printf("\t\t      (4) RESTAURAR BACKUP\n");
        printf("\t\t        (5) REMOVER BACKUP\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");

        limpar_teclado();
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                alterar_login();
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

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

void exibir_qtd_reservas() {

}

void menu_dados() {
    int opcao;
    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tDADOS DO SISTEMA\n");
        printf("\n\t\t(1) QUANTIDADE DE RESERVAS ATIVAS \n");
        printf("\t\t  (2) HISTORICO DE HOSPEDES\n");
        printf("\t\t   (3) LISTAR QUARTOS\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                exibir_qtd_reservas();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
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

int busca_cliente(char *coluna, char *valor, int *ids) {
    int qtd_resultados;
    qtd_resultados = listar_clientes(coluna, valor, -1, ids, exibir_resultados);
    return qtd_resultados;
}

int busca_reserva(char *coluna, char *valor, int *ids) {
    int qtd_resultados;
    qtd_resultados = listar_clientes(coluna, valor, -1, ids, exibir_resultados);
    return qtd_resultados;
}

int busca_quarto(char *coluna, char *valor, int *ids) {
    int qtd_resultados;
    qtd_resultados = listar_clientes(coluna, valor, -1, ids, exibir_resultados);
    return qtd_resultados;
}

char *pegar_dado_pesquisa(char *valor, int size) {
    limpar_teclado();
    fgets(valor, size, stdin);
    remover_quebra(valor);
    return valor;
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

void buscar_cliente() {
    int opcao;
    char dado_busca[50];

    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tBUSCAR CLIENTE\n\n");
        printf("\t\t(1) BUSCAR POR NOME\n");
        printf("\t\t  (2) BUSCAR POR CPF\n");
        printf("\t\t    (3) BUSCAR POR ID\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n\t\tINSIRA O NOME: ");
                pegar_dado_pesquisa(dado_busca, 50);
                busca_cliente("nome", dado_busca, NULL);
                break;
            case 2:
                printf("\n\t\tINSIRA O CPF: ");
                pegar_dado_pesquisa(dado_busca, 50);
                busca_cliente("cpf", dado_busca, NULL);
                break;
            case 3:
                printf("\n\t\tINSIRA O ID: ");
                pegar_dado_pesquisa(dado_busca, 50);
                busca_cliente("id", dado_busca, NULL);
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

void menu_buscas() {
    int opcao;
    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tBUSCAR\n\n");
        printf("\t\t(1) BUSCAR CLIENTE\n");
        printf("\t\t  (2) BUSCAR RESERVA\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                buscar_cliente();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                limpar_tela();
                menu_buscas();
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

void menu_reservas() {
    int opcao;
    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tRESERVAS\n\n");
        printf("\t\t(1) NOVA RESERVA\n");
        printf("\t\t  (2) EDITAR RESERVA\n");
        printf("\t\t    (3) ENCERRAR RESERVA\n\n");
        printf("\t\t(4) BUSCAR\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                nova_reserva();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                limpar_tela();
                menu_buscas();
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

int mostrar_quartos_disponiveis(struct tm *data_inicio, struct tm *data_final, int tipo, int *index) {
    char inicio[15], fim[15], tipo_quarto[3];

    formatar_data_sql(data_inicio, inicio);
    formatar_data_sql(data_final, fim);
    snprintf(tipo_quarto, 3, "%d", tipo);

    printf("\n\t\t%6s%7s%11s%12s", "NUM", "TIPO", "DESCRICAO", "VALOR");

    listar_quartos_ocupados(inicio, fim, tipo_quarto, 0, index, exibir_resultados);

    return 0;
}

int selecionar_quarto(struct tm *data_inicio, struct tm *data_final, int *id_quarto) {
    int total_quartos = 25;
    int index[25] = {0};

    int tipo = selecionar_tipo_quarto();
    if (tipo == 0)
        return -1;
    do {
        mostrar_quartos_disponiveis(data_inicio, data_final, tipo, index);
        printf("\n\n\t\tNUMERO DO QUARTO: ");
        scanf(" %d", id_quarto);

        index[0] = 0;
        if (*id_quarto != 0 && is_in(*id_quarto, index, total_quartos)) {
            return *id_quarto;
        } else {
            printf("\n\n\t\tNUMERO INVALIDO!\n");
            pausa();
        }
    } while (1);
}

int selecionar_tipo_quarto() {
    int tipo;
    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tSELECIONAR QUARTO\n");
        printf("\n\t\t(7) PRESIDENCIAL\n");
        printf("\n\t\t (6) LUXO SIMPLES");
        printf("\n\t\t  (5) LUXO DUPLO");
        printf("\n\t\t   (4) LUXO TRIPLO\n");
        printf("\n\t\t  (3) EXECUTIVO SIMPLES");
        printf("\n\t\t (2) EXECUTIVO DUPLO");
        printf("\n\t\t(1) EXECUTIVO TRIPLO\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        limpar_teclado();
        scanf(" %d", &tipo);

        if (tipo >= 0 && tipo <= 7)
            break;
        else {
            printf("\n\n\t\tOPCAO INVALIDA!\n");
            pausa();
        }
    } while (1);

    return tipo;
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

void listar_todos_clientes() {
    limpar_tela();
    mostrar_titulo();
    puts("\n\n\tCLIENTES REGISTRADOS");
    printf("\n\t\t%3s%20s%20s", "ID", "NOME", "CPF");
    listar_clientes(str_null, str_null, -1, NULL, exibir_resultados);
}


int mostrar_cliente_recuperado(CLIENTE *c) {
    printf("\n\t\t%3d%20s%20s", c->id, c->nome, c->cpf);
    return 0;
}

void pegar_dados_cliente(CLIENTE *c) {
    limpar_tela();
    mostrar_titulo();
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

void mostrar_reserva(RESERVA *r, CLIENTE *c) {
    printf("\t\tID: %04d\n", r->id);
    printf("\t\t NOME DO CLIENTE: %s\n", c->nome);
    printf("\t\t  CPF: %s\n", c->cpf);
    // printf("\t\t   QUARTO: %d\n\n", r->qrt->id);
    printf("\t\t    RESERVA: ");
    puts("\t-----------------------------------------------------------------------------------\n");
}

int criar_banco_de_dados() {
    FILE *db = fopen(DB_PATH, "r+b");
    int criacao__banco_dados = 0;

    if (db == NULL) {
        db = fopen(DB_PATH, "w+b");
        fclose(db);
        printf("\n\n\t\tCRIANDO BANCO DE DADOS ... \n");
        criar_banco();
        criacao__banco_dados = 1;
    } else { fclose(db); }

    return criacao__banco_dados;
}

int checar_diretorios() {
    FILE *ativo = fopen("data/usr/.ativo", "r+b");
    int criacao_de_diretorios = 0;

    if (ativo == NULL) {
        mkdir("data/", 0700);
        mkdir("data/usr/", 0700);
        ativo = fopen("data/usr/.ativo", "w+b");
        criacao_de_diretorios = 1;
    }
    fclose(ativo);
    return criacao_de_diretorios;
}

int autenticar() {
    LOGIN *login = (LOGIN *) calloc(1, sizeof(LOGIN *));

    if (existe_usuario_cadastrado() == 0) {
        criar_login(login);
    }
    limpar_tela();
    printf("\n\t\tINSIRA O LOGIN E SENHA\n\n");
    tela_pegar_login(login);

    int status = validar_login(login);
    free(login);

    return status;
}

int criar_login(LOGIN *login) {

    char senha_confirmacao[21];

    printf("\n\n\n\tCADASTRAR ADMIN: ");
    tela_pegar_login(login);

    printf("\n\n\n\tINSIRA A SENHA NOVAMENTE: ");
    fgets(senha_confirmacao, 21, stdin);
    remover_quebra(senha_confirmacao);

    if (strcmp(login->pwd, senha_confirmacao) == 0) {
        if (gravar_dados_arquivo_login(login)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        printf("\n\n\t\t\tSENHAS INCOMPATIVEIS !!!\n");
        pausa();
        return criar_login(login);
    }
}

void alterar_login() {
    LOGIN *login = (LOGIN *) calloc(1, sizeof(LOGIN *));
    if (criar_login(login)) {

    }
}

void tela_pegar_login(LOGIN *login) {
    printf("\n\n\n\t\t\tUSUARIO: ");
    limpar_teclado();
    fgets(login->usr, 21, stdin);
    remover_quebra(login->usr);
    printf("\n\t\t\tSENHA: ");
    limpar_teclado();
    fgets(login->pwd, 21, stdin);
    remover_quebra(login->pwd);

}
