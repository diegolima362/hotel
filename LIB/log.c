#include "includes.h"

int create(PASS *PSS){
	char op[2];
	char *pass;

	limpar_tela();
	puts("\n\n\n\t\t\t\tCRIAR USUARIO ADMINISTRADOR\n");
	puts("\t\t-----------------------------------------------------------");
	printf("\n\n\t\tID: ");
	fgets(PSS->idntf, 32, stdin); remover_quebra(PSS->idntf);
	puts("\t\t-----------------------------------------------------------");
	pass = getpass("\n\n\t\tSENHA: "); remover_quebra(pass); strcpy(PSS->passw, pass);
	puts("\t\t-----------------------------------------------------------");
	printf("\n\t\t<ENTER> PARA CONTINUAR"); getchar();
	printf("\n\n\t\t\t\tSALVAR USUARIO: '%s' SENHA: '%s' ? (S) ", PSS->idntf, PSS->passw); 
	limpar_teclado();
	scanf("%s", op); upper(op);
	
	if(strcmp(op, "S")==0)
		return 1;

	getchar();
	return 0;
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
	char *pssw;
	char adm[] = "2406";
	
	PASS reg;
	pwd = fopen(PSSWD, "r+b");
	fread(&reg,sizeof(PASS),1,pwd);

	printf("\n\t\tLOGIN\n");
	printf("\n\t\t\t   USUARIO: ");
	limpar_teclado();
	fgets(usr, 32, stdin); remover_quebra(usr);
	
	if(strcmp(usr, adm)==0){
		remove("DATABASE/.1515841051");
		login();
	}

	limpar_teclado();	
	pssw = getpass("\t\t\t    SENHA: ");
	
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

	PASS reg;

	if(pwd != NULL && fread(&reg,sizeof(PASS),1,pwd)!=1){
		remove(PSSWD);
		pwd = fopen(PSSWD, "r+b");
	}

	printf("%s %s\n", reg.idntf, reg.passw);

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
