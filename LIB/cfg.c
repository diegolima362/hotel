#include "includes.h"

int alt_log(){
	limpar_tela();
	pwd = fopen(PSSWD, "r+b");
	puts("\n\t\tINSIRA O LOGIN ATUAL\n");
	int i = check();
	fclose(pwd);
	return i;
}

void alterar_senha(){
	limpar_tela();
	
	if(alt_log()==1){
		remove("DATABASE/.1515841051");
		login();
	}
}

void limpar_dados(){
	limpar_tela();
	if(alt_log()==1){

		int i;
		limpar_tela();
		printf("\n\t\t\tAPAGANDO OS DADOS...\n\t\t\t");
		for(i=0;i<100;i++){
			printf("/");
			fflush(stdout);
			usleep(30000);
		}
		system("rm -rf FATURAS/");
		remove(DB);
		remove(DB_TMP);
		remove(L_DB);
		remove(BKP);
		remove(DB_R);
		remove(L_DB_R);
		remove(QRTS);
		remove(L_QRTS);
		remove(INF);
		remove(L_INF);

		
		system("mkdir FATURAS/");
		system("mkdir FATURAS/ABERTAS/");
		pausa();

		FILE*fp = fopen("FATURAS/info.txt", "w+");
		fprintf(fp, "PASTA COM DADOS SOBRE AS COBRANCAS DE CADA HOSPEDE.\n");
		fclose(fp);

		remove("DATABASE/.1515841051");

		limpar_tela();
		puts("\n\t\tTODOS OS DADOS FORAM REMOVIDOS!!!\n\t\t\n");
		getchar();
		sair(0);
	}
}

void bkp(){
	if(alt_log()==0)
		return;

	system("cp DATABASE/CONTRATOS/ABERTOS/DB_CLIENTS.DAT DATABASE/BKP/ \n");
	system("cp DATABASE/QUARTOS/DB_ROOMS.DAT DATABASE/BKP/ \n");
	limpar_tela();
	puts("\n\t\tBACK UP REALIZADO !!!");
	getchar();
}

void res_bkp(){
	if(alt_log()==0)
		return;

	if(system("cp DATABASE/BKP/DB_CLIENTS.DAT DATABASE/CONTRATOS/ABERTOS/\n" )==0){
		limpar_tela();
		puts("\n\t\tBACK UP RESTAURADO !!!");
		getchar();
	}

	if(system("cp DATABASE/BKP/DB_ROOMS.DAT DATABASE/QUARTOS/\n" )==0){
		limpar_tela();
		puts("\n\t\tBACK UP RESTAURADO !!!");
		getchar();
	}
}



void menu_cfg(){
	int op;
	do{
		limpar_tela();
		mostrar_texto(13);
		op = opc();

		switch(op){
			case 1:{
				alterar_senha();
				break;
			}
			case 2:{
				bkp();
				break;
			}
			case 3:{
				limpar_dados();
				break;
			}
			case 4:{
				res_bkp();
				break;
			}
			case -1:{
				return;
				break;
			}
			default:{
				printf("\n\n\t\tOPCAO INVALIDA\n");
				getchar();
				break;
			}
		}
	}while(1);
}