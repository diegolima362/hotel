// FUNCOES DE SISTEMA
#include "includes.h"

void upper(char *str){
	while(*str){
		*str=toupper(*str);
		str++;
	}
} 

void remover_quebra(char *str){
	str[strcspn(str, "\n")] = 0;
}

void limpar_teclado(){
	setbuf(stdin, NULL);
	setbuf(stdin, NULL);
	setbuf(stdin, NULL);
}

void limpar_tela(){
	//linux
	system("clear"); system("clear");
	/*windows
	system("cls");
	*/
}

void tipo_de_erro(int n){
	switch(n){
		case 0:{
			getchar(); getchar();
			break;
		}
		case 1:{
			limpar_tela();
			printf("OPCAO INVALIDA\n");
			tipo_de_erro(2);
			break;
		}
		case 2:{
			printf("\n>>> PRESSIONE <ENTER> PARA CONTINUAR >>>");
			getchar();
			break;
		}
		case 3:{
			fprintf(stderr, "ERRO FATAL: IMPOSSIVEL CRIAR O ARQUIVO DE DADOS\n");
			tipo_de_erro(2);
			break;
		}
		case 4:{
			printf("REGISTRO INEXISTENTE OU PROBLEMA NO POSICIONAMENTO!!!");
			tipo_de_erro(2);
			break;
		}
		case 5:{
			fprintf(stderr, "ERRO FATAL: IMPOSSIVEL CRIAR O ARQUIVO DE DADOS\n");
			tipo_de_erro(2);
			break;
		}
		case 6:{
			printf("\nHOLTEL COM LOTACAO MAXIMA! \nVERIFIQUE A DISPONIBILIDADE DE VAGAS NO MENU DE RESERVAS\n");
			tipo_de_erro(2);
			break;
		}
	}
}

int opc(){
	char op[5];
	int l;
	limpar_teclado();
	fgets(op, 5, stdin); upper(op); if ( op[0] == 'X' ) { return -1; }
	l=atoi(op);
	return l;
}

int confirmar(){
	char s[2];
	limpar_teclado();
	scanf(" %s", s); upper(s);
	if(s[0] == 'S')
		return 1;
	return 0;
}

void pausa(){
	getchar(); getchar();
}

void test_fun(char c){
	printf("\nTESTE %c\n", c);
}

void formatar_cpf(char *cpf_formatado){
	char scpf[15], aux[2];
	int icpf[11];
	int i = 0;
	
	printf("\t\tINSIRA O CPF (SOMENTE NUMEROS): ");
	limpar_teclado();
	
	fgets(scpf,19,stdin); limpar_teclado();
	
	do{
		aux[0]=scpf[i];
		icpf[i]=atoi(aux);
		i++;
	}while(scpf[i] != '\0');
	
	cpf_formatado[3] = '.'; cpf_formatado[7] = '.';
	cpf_formatado[11] = '-';
	//FORMATAR  CPF
	for(i=0;  i<3;i++)  { 	cpf_formatado[i] = scpf[i]; 		}			
	for(i=4;  i<7;i++)  { 	cpf_formatado[i] = scpf[i-1];		}
	for(i=8;  i<11;i++) {	cpf_formatado[i] = scpf[i-2];		}
	for(i=12; i<15;i++) {	cpf_formatado[i] = scpf[i-3];		}
	remover_quebra(cpf_formatado);
}

void load(){
	int i;

	printf("\n\n\t\t\t\t\t\t\t\tCARRAGANDO ...\n\n\t\t\t\t");
	/*for(i=0;i<30;i++){
		printf("||");
		fflush(stdout);
		usleep(50000);
	}*/

	for(i=0;i<100;i++){
		printf("/");
		fflush(stdout);
		usleep(30000);
	}

}