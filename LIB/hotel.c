// FUNCOES DO HOTEL
#include "includes.h"

void sair(int n){
	limpar_tela();
	mostrar_texto(25);
	putchar('\n');
	printf("\t\t\tSAINDO ...\n\n");
	exit(n);
}

void menu_pesquisa(){
	int l;
	
	int hold = 1;
	
	do{
		limpar_tela();	
		mostrar_texto(5);
	
		l = opc();
	
		switch(l){
			case  1 : pesquisar_cliente_nome(); break;
			case  2 : pesquisar_cliente_cpf();  break;
			case  3 : pesquisar_cliente_id();   break;
			case -1 : hold = 0; break;
			default : tipo_de_erro(1);  break;
		}

	}while(hold);
}

void menu_hospedagem(){
	int l, hold=1;

	do{
		limpar_tela();
		mostrar_texto(2);
		
		l = opc();
		
		switch(l){
			case 1  : criar_contrato(); break;
			case 2  : alterar_contrato(0); break;
			case 3  : remover_contrato(0); break;
			case 4  : menu_pesquisa(database); break;
			case 5  : listar_clientes(); break;
			case 6  : contratar_srvc(); break;
			
			case -1 : hold = 0; break;
			default : tipo_de_erro(1);   break;
		}
	}while(hold);
}

void menu_principal(){
	int l;
	int hold = 1;

	do{
		limpar_tela();
		mostrar_texto(1);
		l = opc();

		switch(l){
			case  1:{
				menu_hospedagem();
				break;
			}
			case 2:{
				menu_inf_sis();
				break;
			}
			case 3:{
				menu_cfg();
				break;
			}
			case -1: sair(0); hold = 0; break;
			default: tipo_de_erro(1); break; 
		}
		
		
	}while(hold);
}

void inic(){
	limpar_tela();
	mostrar_texto(10);	
	
	ler_arquivos();
	fechar_arquivos();
	
	ler_datas();
	
	ler_qrts();
	fechar_qrts();

	criar_services();

	limpar_tela();
	menu_principal();
}
