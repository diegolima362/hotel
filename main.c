
#include "LIB/includes.h"

int main(){
	limpar_tela();
	medir_tela();
	getchar();
	limpar_tela();
	int i = contar_clientes();
	printf("clientes = %d\n", i); getchar();
	reservas_ativas();
	getchar();
	limpar_tela();
	puts("\n");
	mostrar_texto(25);
	getchar();
	login();
	sair(0);
    return 0;
}
