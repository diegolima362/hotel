#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "libs/extrafuncs.h"
#include "libs/login.h"
#include "libs/datas.h"
#include "libs/database.h"

int criar_banco_de_dados();

int checar_diretorios();

int autenticar();

int criar_login(LOGIN *login);

void tela_pegar_login(LOGIN *login);

void menu_principal();

void mostrar_data();

void menu_reservas();

void buscar_cliente_cpf();

void buscar_cliente_nome();

void buscar_cliente();

void menu_buscas();

void menu_dados();

void menu_configuracao();

void mostrar_titulo();

void alterar_login();

void nova_reserva();

void pegar_dados_cliente(CLIENTE *c);

int mostrar_cliente(void *ptr, int resultados, char **STR1, char **STR2);

void listar_todos_clientes();

int mostrar_cliente_recuperado(CLIENTE *c);

int main(int argc, char *argv[]) {

    if (checar_diretorios() == 1 && criar_banco_de_dados() == 1) {
        printf("\n\n\t\tBASE DE DADOS CRIADA ...\n\t\tEXECUTE O PROGRAMA NOVAMENTE\n\n");
        exit(0);
    }
//
//    if (autenticar()) {
//        menu_principal();
//    }

    buscar_cliente_nome();
    pausa();
    buscar_cliente_cpf();
//    remover_reserva(NULL, "2");
    pausa();
    return 0;
}

int imprimir_resultados(void *ptr, int resultados, char **STR1, char **STR2) {
    int i;

    for (i = 0; STR1[i] != NULL; i++) {
        printf("%s = %s\n", STR2[i], STR1[i]);
    }
    return 0;
}

void mostrar_data() {
    DATE *date = ler_data();
    printf("%02d/%02d/%04d ", date->tm_mday, date->tm_mon + 1, date->tm_year + 1900);
    printf("%02d:%02d", date->tm_hour, date->tm_min);
}

void mostrar_titulo() {
    printf("\n\n\t\t---- CAMPINA  COMFORT  PREMIUM ----\n\t\t\t  ");
    mostrar_data();
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

void buscar_cliente_cpf() {
    char cpf[15];
    limpar_tela();
    printf("INSIRA O CPF (SOMENTE NUMEROS): ");
    limpar_teclado();
    fgets(cpf, 12, stdin);
    remover_quebra(cpf);
    listar_clientes("cpf", cpf, -1, mostrar_cliente);

}

void buscar_cliente_nome() {
    char nome[51];
    limpar_tela();
    printf("INSIRA O NOME: ");
    limpar_teclado();
    fgets(nome, 51, stdin);
    remover_quebra(nome);
    listar_clientes("nome", nome, -1, mostrar_cliente);

}

void buscar_cliente() {
    int opcao;
    do {
        limpar_tela();
        mostrar_titulo();
        printf("\n\tBUSCAR CLIENTE\n\n");
        printf("\t\t(1) BUSCAR POR NOME\n");
        printf("\t\t  (2) BUSCAR POR CPF\n");
        printf("\n\t\t(0) VOLTAR\n");
        printf("\n\t\tOPÇÃO: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                buscar_cliente_nome();
                break;
            case 2:
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

void nova_reserva() {
    CLIENTE c;
    pegar_dados_cliente(&c);
    inserir_cliente(&c);
}

void listar_todos_clientes() {
    limpar_tela();
    mostrar_titulo();
    puts("\n\n\tCLIENTES REGISTRADOS");
    printf("\n\t\t%3s%20s%20s", "ID", "NOME", "CPF");
    listar_clientes(str_null, str_null, -1, mostrar_cliente);
}

int mostrar_cliente(void *ptr, int resultados, char **STR1, char **STR2) {
    printf("\n\t\t%3s%20s%20s", STR1[0], STR1[1], STR1[2]);
    return 0;
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
    printf("\t\tINSIRA O CPF (SOMENTE NUMEROS): ");
    limpar_teclado();
    fgets(c->cpf, 15, stdin);
    remover_quebra(c->cpf);
    printf("\t\tTELEFONE DE CONTATO: ");
    limpar_teclado();
    fgets(c->phone, 20, stdin);
    remover_quebra(c->phone);
    printf("\t\tCARTAO DE CREDITO: ");
    limpar_teclado();
    fgets(c->cred_card, 21, stdin);
    remover_quebra(c->cred_card);

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
