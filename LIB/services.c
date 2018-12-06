#include "includes.h"

void listar_srvc(){
	for(int i = 0; i<5; i++){
		mostrar_srvc(srvcs[i]);
	}

}

void mostrar_srvc(SERVICE srvc){
	printf("\n\t\tID DO SERIVICO: %d\n\n", srvc.id);
	printf("\t\tSERIVICO: %s\n", srvc.nome);
	printf("\n\t\t    %s\n", srvc.dscric);
	printf("\n\t\tVALOR: R$ %.2f - R$ %.2f\n\n", srvc.prc_norm, srvc.prc_alta);
	printf("\t\t--------------------------------------------------------------------\n");
}

void criar_services(){
			
	strcpy(srvcs[0].nome, "CARRO DE LUXO");
	strcpy(srvcs[0].dscric, "VEICULOS DE LUXO OU ESPOTIVO FORNECIDOS POR EMPRESA PARCEIRA");
	srvcs[0].prc_norm = 100;
	srvcs[0].prc_alta = 125;
	srvcs[0].id = 1;

	strcpy(srvcs[1].nome, "CARRO EXECUTIVO");
	strcpy(srvcs[1].dscric, "VEICULOS POPULARES OU MINIVANS FORNECIDOS POR EMPRESA PARCEIRA");
	srvcs[1].prc_norm = 60;
	srvcs[1].prc_alta = 75;
	srvcs[1].id = 2;

	strcpy(srvcs[2].nome, "TANQUE CHEIO");
	strcpy(srvcs[2].dscric, "CASO O CLIENTE QUEIRA, PODE RECEBER O VEICULO COM TANQUE CHEIO");
	srvcs[2].prc_norm = 300;
	srvcs[2].prc_alta = 375;
	srvcs[2].id = 3;

	strcpy(srvcs[3].nome, "CARRO ASSEGURADO");
	strcpy(srvcs[3].dscric, "CASO O CLIENTE QUEIRA, PODE RECEBER O VEICULO COM SEGURO");
	srvcs[3].prc_norm = 250;
	srvcs[3].prc_alta = 300;
	srvcs[3].id = 4;

	strcpy(srvcs[3].nome, "BABYSITTER");
	strcpy(srvcs[3].dscric, "SERVICO DE BABA OFERECIDO PELO HOTEL PARA CRIANCAS DE 2 A 9 ANOS");
	srvcs[3].prc_norm = 45;
	srvcs[3].prc_alta = 60;
	srvcs[3].id = 4;

	strcpy(srvcs[4].nome, "MULTIMIDIA PREMIUM");
	strcpy(srvcs[4].dscric, "SERVICOS DE STREAMING, PACOTE DE ESPORTES E VIDEO GAME NO QUARTO");
	srvcs[4].prc_norm = 20;
	srvcs[4].prc_alta = 25;
	srvcs[4].id = 5;

}