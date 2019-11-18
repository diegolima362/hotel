#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "libs/extrafuncs.h"
#include "libs/login.h"
#include "libs/datas.h"
#include "libs/database.h"
#include "libs/sqlite/sqlite3.h"

#define PATH_BKP ".bkp/"
#define PATH_BKP_ACTIVE ".bkp/usr/.bkpativo"

void checar_diretorios();

int autenticar();

void criar_login(LOGIN *login);

void tela_pegar_login(LOGIN *login);

void menu_principal();

void mostrar_data();

void menu_reservas();

void menu_dados();

void menu_configuracao();

void mostrar_titulo();

void alterar_login();

void fazer_bkp();

void remover_dados();

void restaurar_bkp();

void remover_bkp();

void nova_reserva();

void novo_cliente(CLIENTE *c);

int gerar_id(int tipo);

int gravar_dados_arquivo_reserva(RESERVA *r);

int gravar_dados_arquivo_cliente(CLIENTE *c);

void listar_reservas();

void mostrar_reserva(RESERVA *r, CLIENTE *c);

void busca_cliente_id(int id_cliente, CLIENTE *cliente);

int main(int argc, char *argv[]) {
    buscar_cliente("id", "8", -1);
    buscar_cliente("nome", "joao", -1);
    buscar_cliente("cpf", "123", -1);
    remover_cliente("id", "8");
    buscar_cliente("id", "8", -1);

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
    printf("%02d/%02d/%04d \t", date->tm_mday, date->tm_mon + 1, date->tm_year + 1900);
    printf("%02d:%02d", date->tm_hour, date->tm_min);
}

void mostrar_titulo() {
    printf("\n\n\t\t\t---- CAMPINA  COMFORT  PREMIUM ----\n\t\t\t\t\t");
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
                menu_reservas();
                break;
            case 2:
                menu_dados();
                break;
            case 3:
                menu_configuracao();
                break;
            case 0:
                limpar_tela();
                printf("SAINDO...");
                exit(0);

            default:
                printf("\n\nOPCAO INVALIDA!\n\n");
                getchar();
                getchar();
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
                fazer_bkp();
                break;
            case 3:
                remover_dados();
                break;
            case 4:
                restaurar_bkp();
                break;
            case 5:
                remover_bkp();
                break;
            case 0:
                return;
            default:
                printf("\n\nOPCAO INVALIDA!\n\n");
                getchar();
                getchar();
                break;
        }
    } while (opcao != 0);

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
                getchar();
                getchar();
                break;
        }
    } while (opcao != 0);
}

void menu_reservas() {
    int opcao;
    do {
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
                break;
            case 0:
                return;
            default:
                printf("\n\nOPCAO INVALIDA!\n\n");
                getchar();
                getchar();
                break;
        }
    } while (opcao != 0);
}

void nova_reserva() {
    CLIENTE *c = (CLIENTE *) calloc(1, sizeof(CLIENTE));
    //novo_cliente(c);
    //inserir_cliente(c);
    recuperar_clientes(NULL);

    //RESERVA *r = (RESERVA *) malloc(sizeof(RESERVA));
}

void novo_cliente(CLIENTE *c) {
    limpar_tela();
    mostrar_titulo();
    printf("\n\n\t\t\t-------- ADICIONAR DADOS DO CLIENTE --------\n\n");
    c->id = gerar_id(1);
    printf("\n\t\tID: %d\n", c->id);
    printf("\n\t\tNOME DO CLIENTE: ");
    limpar_teclado();
    fgets(c->nome, 101, stdin);
    remover_quebra(c->nome);
    printf("\t\tINSIRA O CPF (SOMENTE NUMEROS): ");
    limpar_teclado();
    fgets(c->cpf, 15, stdin);
    remover_quebra(c->cpf);
    printf("\t\tCARTAO DE CREDITO: ");
    limpar_teclado();
    fgets(c->cred_card, 21, stdin);
    remover_quebra(c->cred_card);

    printf("\t\tTELEFONE DE CONTATO: ");
    limpar_teclado();
    fgets(c->phone, 20, stdin);
    remover_quebra(c->phone);

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

void listar_reservas() {
    FILE *reservas = fopen("data/usr/.reservas", "r+b");
    RESERVA r;
    CLIENTE c;
//    while (fread(&r, sizeof(RESERVA *), 1, reservas) != 1) {
//        puts("aq");
//        mostrar_reserva(&r);
//    }
    fread(&r, sizeof(RESERVA *), 1, reservas);
    busca_cliente_id(r.id_cliente, &c);
    mostrar_reserva(&r, &c);
    fclose(reservas);
}

void busca_cliente_id(int id_cliente, CLIENTE *cliente) {
    FILE *clientes = fopen("data/usr/.clientes", "r+b");
    CLIENTE c;
    rewind(clientes);

    while (fread(&c, sizeof(RESERVA *), 1, clientes) != 1) {
        if (c.id == id_cliente) {
            *cliente = c;
            break;
        }
    }
    fclose(clientes);
}

void mostrar_reserva(RESERVA *r, CLIENTE *c) {
    printf("\t\tID: %04d\n", r->id);
    printf("\t\t NOME DO CLIENTE: %s\n", c->nome);
    printf("\t\t  CPF: %s\n", c->cpf);
    // printf("\t\t   QUARTO: %d\n\n", r->qrt->id);
    printf("\t\t    RESERVA: ");
    puts("\t-----------------------------------------------------------------------------------\n");
}

int gravar_dados_arquivo_reserva(RESERVA *r) {
    FILE *reservas = fopen("data/usr/.reservas", "a+b");
    fseek(reservas, 0L, SEEK_END);
    if (fwrite(r, sizeof(RESERVA *), 1, reservas) != 1) {
        return 0;
    }
    fclose(reservas);

    return 1;
}

int gravar_dados_arquivo_cliente(CLIENTE *c) {
    FILE *clientes = fopen("data/usr/.clientes", "a+b");
    fseek(clientes, 0L, SEEK_END);
    if (fwrite(c, sizeof(RESERVA *), 1, clientes) != 1) {
        return 0;
    }
    fclose(clientes);

    return 1;
}

int gerar_id(int tipo) {
    FILE *id_files = fopen("data/usr/.ids", "r+b");
    // [0] -> reserva; [1] ->cliente
    int id_registrados[2] = {0};

    if (id_files != NULL) {
        fread(id_registrados, sizeof(int), 2, id_files);
        fclose(id_files);
        fopen("data/usr/.ids", "w+b");
    } else {
        fopen("data/usr/.ids", "w+b");
    }
    id_registrados[tipo]++;
    fwrite(id_registrados, 2, sizeof(int), id_files);
    fclose(id_files);
    return id_registrados[tipo];
}

void checar_diretorios() {
    FILE *ativo = fopen("data/usr/.ativo", "r+b");

    if (ativo != NULL) {
        fclose(ativo);
        return;
    }

    // criar diretorios
    mkdir("data/", 0700);
    mkdir("data/usr/", 0700);
    ativo = fopen("data/usr/.ativo", "w+b");

    fclose(ativo);
}

int autenticar() {
    LOGIN *login = (LOGIN *) calloc(1, sizeof(LOGIN *));

    if (existe_usuario_cadastrado() == 0) {
        criar_login(login);
    }

    tela_pegar_login(login);

    int status = validar_login(login);
    free(login);

    return status;
}

void criar_login(LOGIN *login) {

    char senha_confirmacao[21];

    printf("CRIAR LOGIN\n");
    tela_pegar_login(login);

    printf("DIGITAR SENHA NOVAMENTE: ");
    fgets(senha_confirmacao, 21, stdin);
    remover_quebra(senha_confirmacao);

    if (strcmp(login->pwd, senha_confirmacao) == 0) {
        if (gravar_dados_arquivo_login(login)) {
            printf("LOGIN CRIADO COM SUCESSO\n");
        } else {
            printf("NAO FOI POSSIVEL CRIAR O LOGIN");
        }
    } else {
        printf("SENHAS INCOMPATIVEIS\n");
        criar_login(login);
    }
}

void alterar_login() {
    LOGIN *login = (LOGIN *) calloc(1, sizeof(LOGIN *));
    criar_login(login);
}

void tela_pegar_login(LOGIN *login) {
    limpar_tela();
    printf("\nUSUARIO: ");
    limpar_teclado();
    fgets(login->usr, 21, stdin);
    remover_quebra(login->usr);
    printf("\nSENHA: ");
    limpar_teclado();
    fgets(login->pwd, 21, stdin);
    remover_quebra(login->pwd);

}

void fazer_bkp() {
    FILE *ativo = fopen(PATH_BKP_ACTIVE, "r+b");

    if (ativo == NULL) {
        mkdir(PATH_BKP, 0700);
        ativo = fopen(PATH_BKP_ACTIVE, "w+b");
    }

    fclose(ativo);
    system("cp -r data/ .bkp/ \n");
}

void restaurar_bkp() {
    system("cp -r .bkp/ data/");
}

void remover_bkp() {
    system("rm -r .bkp/");
}

void remover_dados() {
    system("rm -r data/");
}