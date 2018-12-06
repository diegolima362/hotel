// FUNCOES PARA MANIPULAR ARQUIVOS
#include "includes.h"

void ler_qrts(){
	
	rooms = fopen(QRTS, "r+b");
	
	if(rooms == NULL){
		rooms = fopen(QRTS, "w+b");
		criar_qrts();		
		if(rooms == NULL){
			tipo_de_erro(5);
			//sair(1);
		}
	}
	
	l_rooms = fopen(L_QRTS, "r+b");
	
	if(l_rooms == NULL){
		l_rooms = fopen(L_QRTS, "w+b");
		if(l_rooms == NULL){
			tipo_de_erro(5);
			//sair(1);
		}
	}
}

void fechar_qrts(){
	fclose(rooms);
	fclose(l_rooms);
}

void ler_arquivos(){
	
	database = fopen(DB, "r+b");
		
	if(database == NULL){
		database = fopen(DB, "w+b");		
		if(database==NULL){
			tipo_de_erro(5);
			getchar();
			//sair(1);
		}
	}

	database_reg = fopen(DB_R, "r+b");

	if(database_reg == NULL){
		database_reg = fopen(DB_R, "w+b");
		if(database_reg == NULL){
			tipo_de_erro(5);
		}
	}
	
	l_database = fopen(L_DB, "r+");	
		
	if(l_database == NULL){
		l_database = fopen(L_DB, "w+");		
		if(l_database==NULL){
			tipo_de_erro(5);
			//sair(1);
		}
	}

	if(users = fopen(INF, "r+b")){
		fread(&new_id, sizeof(int),1,users);
	}

	if(users == NULL){
		users = fopen(INF, "w+b");
		users_cadastrados = 0;
		fwrite(&users_cadastrados, sizeof(users_cadastrados),1,users);		
		if(users == NULL){
			tipo_de_erro(5);
			//sair(1);
		}
	}

	l_users = fopen(L_INF, "a+");

	if(l_users == NULL){
		l_users = fopen(L_INF, "w+");
		users_cadastrados = 0;
		fprintf(l_users, "USERS: %d\n\n", users_cadastrados);		
		if(l_users == NULL){
			tipo_de_erro(5);
			//sair(1);
		}
	}	
}

void fechar_arquivos(){
	
	fclose(database);
	fclose(l_database);
	rewind(users);
	fwrite(&new_id, sizeof(int),1,users);
	
	fprintf(l_users, "\nUSERS REGISTRADOS     %s /  %s    =  %d \n", __DATE__, __TIME__, users_cadastrados);
	fprintf(l_users, "--------------------------------------------------------------------------------------\n");		

	fclose(users);
	fclose(l_users);
	aberto = 0;

}