#include "includes.h"


void nome_fatura(char *str, double id){
	char id_s [13];
	snprintf(id_s, 13, "%.lf", id);
	strcpy(str, id_s);
}


void criar_fatura(char *fat, double pid){
	
	FILE *fatura;

	char pasta[]="FATURAS/ABERTAS/"; 
	char tipo[]=".dat";
	
	char *nome;
	char id[13];
	nome_fatura(id, pid);

	nome = (char *) malloc(sizeof(id)+sizeof(pasta)+sizeof(tipo));
	
	strcpy(nome, pasta);
	strcat(nome, id);
	strcat(nome, tipo);
	strcpy(fat, nome);
	
	fatura = fopen(nome, "w+b");
	fclose(fatura);
}

void adicionar_valor_fatura(SERVICE srv, char *fat){
	FILE *fatura;

	fatura = fopen(fat, "r+b");
	
	if(fatura == NULL){
		printf("\n\t\tERRO AO ENCONTRAR FATURA\n");
		return;
	}

	fseek(fatura, 0L, SEEK_END);

	fwrite(&srv, sizeof(srv),1, fatura);

	fclose(fatura);
}

void fechar_fatura(CONTRATO *p){
	SERVICE srv;
	FILE *fatura;
	float vlr = 0;

	fatura = fopen(p->fat, "r+b");

	while(fread(&srv, sizeof(SERVICE), 1, fatura)){
		vlr += srv.prc_norm * srv.prc_alta;
	}

	remove(p->fat);
}

void mostrar_fatura(CONTRATO p){
	limpar_tela();

	printf("\t\t\tCAMPINA CONFORT PREMIUM\n");
	printf("\t\t\t%s - %s\n", __DATE__, __TIME__ );
	printf("\n---------------------------------------------------------\n");
	printf("\t\tID: %.lf\n\n", p.cliente.id);
	printf("\t\tNOME DO CLIENTE: %s\n", p.cliente.nome);
	printf("\t\tCPF: %s\n", p.cliente.cpf);
	printf("\t\tCARTAO DE CREDITO: %s\n", p.cliente.cred_card);
	printf("\t\tTELEFONE DE CONTATO: %s\n", p.cliente.cel);
	printf("\n\t\tQUARTO: %d\n", p.r.num);
	printf("\n\t\tRESERVA: "); mostrar_dat(p.res.ini); printf(" - "); mostrar_dat(p.res.fim); putchar('\n');
	printf("\n\t\tDADOS CLIENTE\n");
	printf("\t\tENDERECO: ");
	printf("\t\t%s, %d, %s\n", p.cliente.end.bairro, p.cliente.end.num, p.cliente.end.rua);
	printf("\t\t%s - %s - %s\n", p.cliente.end.cidade, p.cliente.end.estado, p.cliente.end.pais);
	printf("\n---------------------------------------------------------\n");
	
}

void imprimir_fatura(CONTRATO p){

	FILE *fatura;	
	char pasta[]="FATURAS/"; 
	char tipo[]=".txt";
	
	char *fat;
	char nome[13];
	nome_fatura(nome, p.id);

	fat = (char *) malloc(sizeof(nome)+sizeof(pasta)+sizeof(tipo));
	
	strcpy(fat, pasta);
	strcat(fat, nome);
	strcat(fat, tipo);
	
	fatura = fopen(fat, "w+");

	fprintf(fatura, "\t\t\t\t\t\tCAMPINA CONFORT PREMIUM\n\t\t\t\t\t\t\t");
	fputs(__TIME__, fatura);
	fputs("   -   ", fatura);
	fputs(__DATE__, fatura);
	fprintf(fatura,"\n----------------------------------------------------------------------------------------------------------\n");
	fprintf(fatura,"ID: %.lf\n\n", p.cliente.id);
	fprintf(fatura,"NOME DO CLIENTE: %s\n", p.cliente.nome);
	fprintf(fatura,"CPF: %s\n", p.cliente.cpf);
	fprintf(fatura,"CARTAO DE CREDITO: %s\n", p.cliente.cred_card);
	fprintf(fatura,"TELEFONE DE CONTATO: %s\n", p.cliente.cel);
	fprintf(fatura,"\nQUARTO: %d\n", p.r.num);
	fprintf(fatura,"\nDADOS CLIENTE\n");
	fprintf(fatura,"ENDERECO: ");
	fprintf(fatura,"%s, %d, %s\n", p.cliente.end.bairro, p.cliente.end.num, p.cliente.end.rua);
	fprintf(fatura,"%s - %s - %s\n", p.cliente.end.cidade, p.cliente.end.estado, p.cliente.end.pais);
	fprintf(fatura,"----------------------------------------------------------------------------------------------------------");

	free(fat);
	fclose(fatura);
}