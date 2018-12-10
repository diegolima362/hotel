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

void adicionar_valor_fatura(SERVICE srv, int qtd, int alt, char *fat){
	
	FILE *fatura;
	fatura = fopen(fat, "r+b");

	if(alt == 1){
		srv.alt = true;
	}
	
	int i;

	if(fatura == NULL){
		printf("\n\t\tERRO AO ENCONTRAR FATURA\n");
		return;
	}

	for(i=0; i<qtd; i++){
		fseek(fatura, 0L, SEEK_END);
		fwrite(&srv, sizeof(srv),1, fatura);
	}

	fclose(fatura);

}

void fechar_fatura(CONTRATO *p){
	SERVICE srv;
	FILE *fatura;
	float vlr = 0, vlra = 0;

	vlr = p->dias_reserva * p->qrt.vlr_nrm;
	vlra = p->dias_alt_tmp * (p->qrt.vlr_nrm * 0.25);

	fatura = fopen(p->fat, "r+b");

	while(fread(&srv, sizeof(SERVICE), 1, fatura)){
		printf("SERVICO: %s\n", srv.nome);
		printf("DATA: "); mostrar_dat(srv.data);putchar('\n');
		vlr += srv.prc;
		if(srv.alt == true)
			vlr += srv.prc*0.25;
	}
	
	p->fatura = vlr+vlra;
	
	char op[2];
	limpar_tela();
	printf("\n\tRESERVA FINALIZADA !\n");
	printf("\n\tFATURA DETALHADA SALVA NA PASTA 'FATURAS' COM O NOME %.lf\n", p->id);
		
	imprimir_fatura(*p);
	remove(p->fat);
}

void imprimir_fatura(CONTRATO p){

	FILE* fatura;
	FILE* srvs;
	SERVICE srv;	
	char pasta[]="FATURAS/"; 
	char tipo[]=".txt";
	
	char *fat;
	char nome[13];
	nome_fatura(nome, p.id);

	float alt = 0;

	fat = (char *) malloc(sizeof(nome)+sizeof(pasta)+sizeof(tipo));
	
	strcpy(fat, pasta);
	strcat(fat, nome);
	strcat(fat, tipo);
	
	fatura = fopen(fat, "w+");
	srvs = fopen(p.fat, "r+b");

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

	DATE *data = localtime(&p.res.ini);
	fprintf(fatura,"\nPERIODO HOSPEDADO: %2d/%2d/%4d - ", data->tm_mday, data->tm_mon + 1, data->tm_year + 1900);
	data = localtime(&p.res.fim);
	fprintf(fatura,"%2d/%2d/%4d\n", data->tm_mday, data->tm_mon + 1, data->tm_year + 1900);
	fprintf(fatura,"\nDADOS CLIENTE\n");
	fprintf(fatura,"ENDERECO: ");
	fprintf(fatura,"%s, %d, %s\n", p.cliente.end.bairro, p.cliente.end.num, p.cliente.end.rua);
	fprintf(fatura,"%s - %s - %s\n", p.cliente.end.cidade, p.cliente.end.estado, p.cliente.end.pais);
	fprintf(fatura,"----------------------------------------------------------------------------------------------------------");
	fprintf(fatura,"\n\nVALOR TOTAL DA FATURA: R$ %.2f\n", p.fatura);
	fprintf(fatura,"\nTIPO DE RESERVA: %s\n", p.qrt.classe);
	fprintf(fatura,"\nVALOR DA DIARIA: R$ %.2f\nQUANTIDADE DE DIAS %d\nVALOR DA RESERVA R$ %.2f\n", p.qrt.vlr_nrm, p.dias_reserva, p.qrt.vlr_nrm * p.dias_reserva);
	fprintf(fatura,"\nACRESCIMO DE ALTA TEMPORADA\nDIAS EM ALTA TEMPORADA: %d \tAUMENTO DE R$ %.2f\n", p.dias_alt_tmp, p.dias_alt_tmp * (p.qrt.vlr_nrm*0.25));
	fprintf(fatura,"\nSERVICOS ADICIONAIS CONTRATADOS: \n\n");

	while(fread(&srv, sizeof(SERVICE), 1, srvs)){
		
		DATE *data = localtime(&srv.data);
		
		fprintf(fatura,"%s - ", srv.nome);
		
		if(srv.alt == true)
			alt = srv.prc*0.25;
		else
			alt = 0;
		
		fprintf(fatura,"DATA: %2d/%2d/%4d\t- R$ %.2f (+ R$ %.2f *ALTA TEMPORADA)\n", data->tm_mday,data->tm_mon + 1,data->tm_year + 1900, srv.prc, alt);
	}

	free(fat);
	fclose(fatura);
	fclose(srvs);
	return;
}