// FUNCOES DE BUSCA
#include "includes.h"

void sair_pesquisa(int n){
	char c = ' ';
	if(n > 1)
		c = 'S';

	printf("\n>>> %d RESULTADO%c\n", n, c);
	printf("\n\t\t(1) EDITAR RESERVA (2) FINALIZAR RESERVA\n"); 
	printf("\n\t\t<ENTER> PESQUISAR NOVAMENTE (X) VOLTAR\n\n\t\tOPCAO: "); 
}

int erro_pesquisa(){

	char s[2];

	printf("\n\nNÂO FORAM ENCONTRADOS HOSPEDES PARA O TERMO PESQUISADO !!!\n\n\n");getchar();
	printf("PESQUISAR NOVAMENTE? (S) (N) : "); limpar_teclado(); limpar_teclado();
	
	scanf("%s", s); upper(s);

	if(s[0] == 'S'){
		s[0] = '\0';
		return 1;
	}

	return 0;
}

int analisa(int n){
	int l;
	if(n == 0){
		if(erro_pesquisa()==1){
			return 1;
		}else{
			return 0;
		}			
	}

	sair_pesquisa(n);

	limpar_teclado();

	l = opc();

	if(l==-1) 
		return 0;

	if(l==1){
		printf("\nINSIRA ID: ");
		double op;
		limpar_teclado();
		scanf("%lf", &op);
		alterar_contrato(op);
		return 0;
	}

	if(l==2){
		printf("\nINSIRA ID: ");
		double op;
		limpar_teclado();
		scanf("%lf", &op);
		remover_contrato(op);
		return 0;
	}

	return 1;
}

void pesquisar_cliente_nome(){
	int j = 1, l, i;
	char nome[60];
	int resultados = 0;
	int hold = 1;
	
	CONTRATO p;

	ler_arquivos();

	do{
		limpar_tela();
		mostrar_texto(0);
		puts("\n\t\tBUSCAR POR NOME\n\t");
		printf("\n\tINSIRA O NOME: ");
		limpar_teclado();
		setbuf(stdin, 0);
		fgets(nome, 101, stdin); upper(nome); remover_quebra(nome);	
		rewind(database);
		limpar_tela();
		mostrar_texto(0);
		printf("\n\t\tRESULTADOS ENCONTRADOS PARA %s\n\n", nome);
		
		while(fread(&p, sizeof(p),1,database)){
			
			if(strstr(p.cliente.nome, nome) && p.status == true){
				mostrar_reserva(p);
				
				resultados++;
				j++;
										
			}

			if(j%11==0){
					l = pagina(&i);
					if(l==-1){
						return;
					}
					printf("\n\t\t\t\tPAGINA %d\n\n", i);
				}				
				
		}
		
		nome[0]='\0';
		
		if(analisa(resultados) == 0){
		
			break;
		
		}else{
			getchar();
			limpar_teclado();
			pesquisar_cliente_nome();
		}

		resultados = 0;		

	}while(hold);

	fechar_arquivos();
	tipo_de_erro(2);
}

void pesquisar_cliente_cpf(){
	int j = 1, l, i;
	char cpf[15];
	int resultados = 0;
	int hold = 1;
	
	CONTRATO p;
	ler_arquivos();

	do{
		limpar_tela();
		mostrar_texto(0);
		puts("\n\t\tBUSCAR CPF\n\t");
		limpar_teclado();	formatar_cpf(cpf); 
		setbuf(stdin, 0);
			
		rewind(database);
		limpar_tela();
		mostrar_texto(0);
		printf("\n\t\tRESULTADOS ENCONTRADOS PARA %s\n\n", cpf);
		
		while(fread(&p, sizeof(p),1,database)){
			
			if((strcmp(p.cliente.cpf, cpf)==0) && p.status == true){
				mostrar_reserva(p);
				
				resultados++;
				j++;
				
				if(j%11==0){
					l = pagina(&i);
					if(l==-1){
						return;
					}
				}				
				printf("\n\t\t\t\tPAGINA %d\n\n", i);				
			}
		}

		if(analisa(resultados) == 0){
			break;
		}else{
			getchar();
			limpar_teclado();
			pesquisar_cliente_cpf();
		}

		resultados = 0;		

	}while(hold);

	fechar_arquivos();
	tipo_de_erro(2);
}


void pesquisar_cliente_id(){
	int j = 1, l, i;
	double id;
	int resultados = 0;
	int hold = 1;
	
	ler_arquivos();
	
	CONTRATO p;

	do{
		limpar_tela();
		mostrar_texto(0);
		puts("\n\t\tBUSCAR ID");	
		printf("\n\t\t\tBUSCAR POR: "); limpar_teclado();
		scanf("%lf", &id);
	
		rewind(database);
		limpar_tela();
		mostrar_texto(0);
		printf("\n\t\tRESULTADOS ENCONTRADOS PARA '%.lf'\n\n", id);

		while(fread(&p, sizeof(p),1,database)){
			if(p.status == true && p.id == id){
				mostrar_reserva(p);
				resultados++;
				j++;
				if(j%11==0){
					l = pagina(&i);
					if(l==-1){
						return;
					}
					printf("\n\t\t\t\tPAGINA %d\n\n", i);getchar();
				}
			}
		}

	if(analisa(resultados) == 0)
		break;
	
	resultados = 0;		
	
	}while(hold);

	fechar_arquivos();

	tipo_de_erro(2);
}



