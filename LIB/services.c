#include "includes.h"

void listar_srvc(){
	for(int i = 0; i<5; i++){
		mostrar_srvc(srvcs[i]);
	}

	getchar(); 

}

void mostrar_srvc(SERVICE srvc){
	printf("\n\t\tID DO SERIVICO: %d\n\n", srvc.id);
	printf("\t\tSERIVICO: %s\n", srvc.nome);
	printf("\n\t\t    %s\n", srvc.dscric);
	printf("\n\t\tVALOR: R$ %.2f - R$ %.2f\n\n", srvc.prc, srvc.prc*1.25);
	printf("\t\t--------------------------------------------------------------------\n");
}

void contratar_srvc(){
	
	if(contar_clientes()==0){
		printf("\n\n\t\tNAO EXITEM HOSPEDES REGISTRADOS!!!\n");
		getchar();
		return;
	}

	CONTRATO p;
	
	double c_id;
	int i = 0;
	int qtd;
	int op;
	
	limpar_tela();
	mostrar_texto(0);
	printf("\n\n\t\t(1) LISTAR HOSPEDES");
	printf("\n\t\t (2) DIGITAR ID\n");
	printf("\n\t\tOPCAO: ");
	scanf("%d", &op);

	if(op < 1 || op > 2)
		return;

	if(op == 1){
		listar_clientes();
		printf("\n\n\tDIGITE O ID DO CLIENTE: ");
		scanf("%lf", &c_id);
	}

	if(op == 2){
		printf("\n\n\tDIGITE O ID DO CLIENTE: ");
		scanf("%lf", &c_id);
	}

	ler_arquivos();

	while(fread(&p, sizeof(p),1,database)){		
		if(p.id == c_id){
			i=1;
			break;
		}					
	}

	if(i==0){
		printf("\n\tID INVALIDO!\n");
		pausa();
		return;
	}

	limpar_tela();
	listar_srvc();

	int id;
	puts("\t<ENTER>"); getchar();
	
	printf("\n\t\tDIGITE O ID DO SERIVICO: "); limpar_teclado();
	scanf(" %d", &id);

	if(id < 1 || id > 5){
		printf("\n\t\tCODIGO DE SERIVICO INVALIDO!\n");
		return;
	}

	printf("\n\t\tQUANTIDADE DE HORAS / DIARIAS : "); limpar_teclado();
	scanf("%d", &qtd);
	printf("\n\t\tVALOR ADICIONAL (ALTA TEMPORADA)? (1) SIM (0) NAO : ");
	scanf("%d", &i);
	pegar_dat(&srvcs[id-1].data);

	adicionar_valor_fatura(srvcs[id-1], qtd, i , p.fat);
}

void criar_services(){
			
	strcpy(srvcs[0].nome, "CARRO DE LUXO");
	strcpy(srvcs[0].dscric, "VEICULOS DE LUXO OU ESPOTIVO FORNECIDOS POR EMPRESA PARCEIRA");
	srvcs[0].prc = 100;
	srvcs[0].id = 1;

	strcpy(srvcs[1].nome, "CARRO EXECUTIVO");
	strcpy(srvcs[1].dscric, "VEICULOS POPULARES OU MINIVANS FORNECIDOS POR EMPRESA PARCEIRA");
	srvcs[1].prc = 60;
	srvcs[1].id = 2;

	strcpy(srvcs[2].nome, "TANQUE CHEIO");
	strcpy(srvcs[2].dscric, "CASO O CLIENTE QUEIRA, PODE RECEBER O VEICULO COM TANQUE CHEIO");
	srvcs[2].prc = 300;
	srvcs[2].id = 3;

	strcpy(srvcs[3].nome, "CARRO ASSEGURADO");
	strcpy(srvcs[3].dscric, "CASO O CLIENTE QUEIRA, PODE RECEBER O VEICULO COM SEGURO");
	srvcs[3].prc = 250;
	srvcs[3].id = 4;

	strcpy(srvcs[3].nome, "BABYSITTER");
	strcpy(srvcs[3].dscric, "SERVICO DE BABA OFERECIDO PELO HOTEL PARA CRIANCAS DE 2 A 9 ANOS");
	srvcs[3].prc = 45;
	srvcs[3].id = 4;

	strcpy(srvcs[4].nome, "MULTIMIDIA PREMIUM");
	strcpy(srvcs[4].dscric, "SERVICOS DE STREAMING, PACOTE DE ESPORTES E VIDEO GAME NO QUARTO");
	srvcs[4].prc = 20;
	srvcs[4].id = 5;

}