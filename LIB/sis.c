#include "includes.h"

void menu_inf_sis(){
	
	if(alt_log() == 0)
		return;

	int op;
	do{
		limpar_tela();
		mostrar_texto(8);
		op = opc();

		switch(op){
			case 1:{
				limpar_tela();
				int qtd = contar_clientes();
				reservas_ativas();
				printf("\n\n\t\tCLIENTES HOSPEDADOS: %d\n", qtd);
				getchar();
				break;
			}

			case 2:{
				list_inat();
				break;
			}

			case 3:{
				listar_qrts(); getchar();
				break;
			}

			case 4:{
				reservas_ativas();
				break;
			}

			case -1:{
				return;
			}
			
			default:{
				printf("\n\t\tOPCAO INVALIDA ");
				getchar();
			}
		}
	}while(1);
}

void reservas_ativas(){
	RESERVAS res;
	ler_qrts();
	
	while(fread(&res, sizeof(RESERVAS), 1, l_rooms)){
		printf("\n\t\tQUARTO %d ID %.lf RESERVA ", res.num, res.id);
		mostrar_dat(res.res.ini); printf(" - "); mostrar_dat(res.res.fim);  putchar('\n');
	}
}

void list_inat(){
	ler_arquivos();
	int hold = 1;
	int i, j=1, l, hold2 = 1;
	
	do{
		limpar_tela();
		puts("\n\tHISTORICO DE CLIENTES HOSPEDADOS\n\n");
		printf("\t\t\t\tPAGINA 1\n\n");
		puts("\t------------------------------------------------------------------------\n");
		
		CONTRATO reg;
		rewind(database);
		
		do{
			for(i=0;;i++){
				if(fread(&reg,sizeof(CONTRATO),1,database_reg)!=1){
					hold2 = 0; 
					break;
				}
				if(!(reg.status)){
					mostrar_reserva(reg);
					if((i+1)%10==0){ 
						l = pagina(&j); 
						if(l==-1){
							hold = 0; 
							hold2 = 0;
							break;
						}
						mostrar_texto(7);
						printf("\n\t\t\t\tPAGINA %d\n\n", j);
					}
				}
			}
		}while(hold2);

		tipo_de_erro(2);
		hold = 0;
	}while(hold);
}