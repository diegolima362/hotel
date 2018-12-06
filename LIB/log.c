#include "includes.h"

int create(PASS *PSS){
	char op[2];

	limpar_tela();
	puts("\t\t\t\tCRIAR USUARIO ADMINISTRADOR\n");
	puts("\t\t---------------------------------------------------");
	printf("\t\tID: ");
	fgets(PSS->idntf, 32, stdin); remover_quebra(PSS->idntf);
	puts("\t\t---------------------------------------------------");
	printf("\t\tSENHA: ");
	fgets(PSS->passw, 32, stdin); remover_quebra(PSS->passw);
	puts("\t\t---------------------------------------------------");
	printf("\n\t<ENTER> PARA CONTINUAR "); getchar();
	printf("\n\t\tSALVAR '%s' : '%s' ? (S) ", PSS->idntf, PSS->passw); 
	limpar_teclado();
	scanf("%s", op); upper(op);
	
	if(strcmp(op, "S")==0)
		return 1;

	getchar();
	create(PSS);
}

int gravar_pw(PASS *PSS){
	rewind(pwd);
	
	if(fwrite(PSS, sizeof(PASS), 1, pwd)){
		fclose(pwd);
		return 1;
	}

	return 0;
}

int check(){
	char usr[32];
	char pssw[32];
	char adm[] = "2406";
	
	PASS reg;
	fread(&reg,sizeof(PASS),1,pwd);

	printf("\n\t\tLOGIN\n");
	printf("\n\t\t\t   USUARIO: ");
	limpar_teclado();
	fgets(usr, 32, stdin); remover_quebra(usr);
	
	if(strcmp(usr, adm)==0){
		remove("DATABASE/.1515841051");
		login();
	}

	printf("\t\t\t    SENHA: "); limpar_teclado();	
	fgets(pssw, 32, stdin); remover_quebra(pssw);

	if(strcmp(reg.idntf, usr)==0 && strcmp(reg.passw, pssw)==0){
		return 1;
	}

	limpar_tela();
	printf("\n\tLOGIN OU SENHA INVALIDO!!!\n"); getchar();
	return 0;
}

void login(){
	PASS PSS;

	pwd = fopen(PSSWD, "r+b");

	if(pwd == NULL){
		pwd = fopen(PSSWD, "w+b");
		
		if(create(&PSS)){
			if(gravar_pw(&PSS)){
				printf("\n\n\t\tCONTA CRIADA!!! PRESSIONE <ENTER> PARA FAZER LOGIN  ");
				getchar(); getchar();
				login();
			}else{
				puts("\n\n\t\tIMPOSSIVEL CRIAR CONTA!!! PRESSIONE <ENTER> PARA SAIR"); getchar();
				remove("DATABASE/.1515841051");
				exit(0);

			}
		}
	}else{
		
		limpar_tela();
		
		if(check()){
			fclose(pwd);
			inic();
		}
		login();
	}
}
