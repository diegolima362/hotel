#include "includes.h"


void listar_qrts(){
	QUARTO q;
	ler_qrts();
	int i=0;
	limpar_tela();
	mostrar_texto(0);
	
	while(fread(&q, sizeof(QUARTO), 1, rooms)){
		mostrar_qrts(q);
	}
	printf("\n<ENTER> PARA CONTINUAR ");
	fechar_qrts();
}


void mostrar_qrts(QUARTO q){
	printf("\n\tNUMERO: %d\n", q.num);
	printf("\tCLASSE: %s \n", q.classe);
	
	printf("\n\t-----------------------------------");
}


int list_qrt_restrit(int tipo, int *v, int m){
	QUARTO q;
	int i=0;
	int aux = 0;
	int ret = 0;
	ler_qrts();
	
	while(fread(&q, sizeof(QUARTO), 1, rooms)){
		aux = 0;
		if(q.tipo == tipo){
			for(i=0;i<m;i++){
				if(q.num == v[i]){
					aux = 0;
					break;
				}else{
					aux = 1;
				}
			}
		}
		if(aux==1){
			mostrar_qrts_restrict(q);
			ret++;
		}
	}

	return ret;
}


void mostrar_qrts_restrict(QUARTO q){
	printf("\n\tQUARTO: %d", q.num);
}

void checar_vagas(){
	TEMPO dat;
	QUARTO qrt;
		
	int qrt_tip;
	int num;
	
	qrt_tip = escolher_tip();

	limpar_tela();
	printf("\n\n\t\t\tDATA DE ENTRADA\n");
		if(!pegar_dat(&dat.ini))
			return ;
	
	printf("\n\n\t\t\tDATA PREVISTA DE SAIDA\n");
		if(!pegar_dat(&dat.fim))
			return ;

	if(dat.fim <= dat.ini)
		return ;
	
	if(verificar_vagas(qrt_tip, dat, &num) == 0)
		return ;
	printf("\n\tQUARTO DISPONIVEL!!!\n");
	getchar();
}

int reservar_qrt(CONTRATO *p, RESERVAS *r){
	
	TEMPO dat;
		
	int qrt_tip;
	int num;
	
	qrt_tip = escolher_tip();

	if(qrt_tip == 0)
		return -1;
	
	limpar_teclado();
	limpar_tela();

	printf("\n\n\t\t\tDATA DE ENTRADA\n");
		if(!pegar_dat(&dat.ini))
			return 0;
	
	printf("\n\n\t\t\tDATA PREVISTA DE SAIDA\n");
		if(!pegar_dat(&dat.fim))
			return 0;

	if(dat.fim <= dat.ini)
		return 0;
	
	if(verificar_vagas(qrt_tip, dat, &num) == 0)
		return 0; 

	p->num = num;
	p->res = dat;

	r->num = num;
	r->tipo = qrt_tip;
	r->res = dat;
	
	return 1;	
}


int escolher_tip(){
	int l;
	limpar_tela();
	mostrar_texto(14);

	do{		
		scanf(" %d", &l);

		if(l == 0)
			return 0;
		
		if(l>=1||l<=7)
			return l;
	
	}while(1);
}


void alocar_qrt(int num, QUARTO* qrt){
	QUARTO q;
	
	ler_qrts();
	while(fread(&q, sizeof(QUARTO), 1, rooms)){
		if(q.num == num){
			*qrt = q;
			return;
		}
	}
}

int select_qrt(int tipo, int  *v, int m){
	limpar_tela();
	mostrar_texto(0);
	int l;
	int i;
		
	if(list_qrt_restrit(tipo, v,m) == 0){
		return 0;
	}
	else{
		do{
			printf("\n\t\t\tNUMERO DO QUARTO SELECIONADO: ");
			l=opc();
			if(test_num(tipo, l, v, m)){
				return l;
			}
			else{
				printf("\n\t\tOPCAO INVALIDA!!!\n");
			}
		} while (1);		
	}
}


int buscar_qrt(int l){
	fechar_qrts();
	ler_qrts();
	
	QUARTO q;
	
	while(fread(&q, sizeof(QUARTO), 1, rooms)){
		if((q.num== l)){
			mostrar_qrts(q);
			return 1;
			break;
		}
	}
	
	return 0;
}


int qtd_qrts(int tipo){

	if(tipo==1||tipo==2||tipo==5){
		return 5;
	}
	else{
		if(tipo==3||tipo==6){
			return 15;
		}
		else{
			return 20;
		}
	}
}


int test_num(int tipo, int num, int *v, int m){	

	if(num <= 0 || num > 85)
		return 0;

	if(tipo == 1 && (num < 81 || num > 85))
		return 0;
	
	if(tipo == 2 && (num < 76 || num > 80))
		return 0;
	
	if(tipo == 3 && (num < 61 || num > 75))
		return 0;
	
	if(tipo == 4 && (num < 41 || num > 60))
		return 0;
	
	if(tipo == 5 && (num < 36 || num > 40))
		return 0;
	
	if(tipo == 6 && (num < 21 || num > 35))
		return 0;
	
	if(tipo == 7 && (num < 1  || num > 20))
		return 0;

	int i;

	for(i=0;i<m;i++){
		if(num == v[i])
			return 0;
	}

}


void criar_qrts(){
	QUARTO quartos[85];
		
	for(int i=80;i<85;i++){
		quartos[i].num   = i+1;
		quartos[i].tipo  = 1;
		quartos[i].vlr_nrm = 1200.0;
		quartos[i].vlr_alt = 1500.0;		
		strcpy(quartos[i].classe, "PRESIDENCIAL");
	}
	
	for(int i=75;i<80;i++){
		quartos[i].num = i+1;
		quartos[i].tipo  = 2;
		quartos[i].vlr_nrm = 520.0;
		quartos[i].vlr_alt = 650.0;
		
		strcpy(quartos[i].classe, "LUXO SIMPLES");
		
	}

	for(int i=60;i<75;i++){
		quartos[i].num = i+1;
		quartos[i].tipo = 3;
		quartos[i].vlr_nrm = 570.0;
		quartos[i].vlr_alt = 712.0;
		
		strcpy(quartos[i].classe, "LUXO DUPLO");
		
	}

	for(int i=40;i<60;i++){
		quartos[i].num = i+1;
		quartos[i].tipo = 4;
		quartos[i].vlr_nrm = 620.0;
		quartos[i].vlr_alt = 775.0;
		
		strcpy(quartos[i].classe, "LUXO TRIPLO");
		
	}

	for(int i=35;i<40;i++){
		quartos[i].num = i+1;
		quartos[i].tipo = 5;
		quartos[i].vlr_nrm = 360.0;
		quartos[i].vlr_alt = 450.0;		
		strcpy(quartos[i].classe, "EXECUTIVO SIMPLES");
		
	}

	for(int i=20;i<35;i++){
		quartos[i].num = i+1;
		quartos[i].tipo = 6;
		quartos[i].vlr_nrm = 385.0;
		quartos[i].vlr_alt = 481.0;		
		strcpy(quartos[i].classe, "EXECUTIVO DUPLO");		
	}

	for(int i=0;i<20;i++){
		quartos[i].num = i+1;
		quartos[i].tipo   = 7;
		quartos[i].vlr_nrm = 440.0;
		quartos[i].vlr_alt = 550.0;		
		strcpy(quartos[i].classe, "EXECUTIVO TRIPLO");
		
	}
	
	fwrite(&quartos, sizeof(quartos),1,rooms);
	fclose(rooms);
	printf("\n\t\tDADOS CARREGADOS... REINICIANDO...\n");
	getchar();
	sair(0);
}

