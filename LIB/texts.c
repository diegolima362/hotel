// TEXTOS DE MENUS E CABECALHOS
#include "includes.h"

void mostrar_texto(int n){	
	switch(n){
		case 0:{
			limpar_tela();
			ler_hora();
			printf("\n\n\t\t\t---- CAMPINA  CONFORT  PREMIUM ----\n\t\t\t\t");
			ler_datas(); mostrar_data(); mostrar_hora();
			break;
		}
		case 1:{
			mostrar_texto(0);
			printf("\n\tMENU INICIAL\n");
			printf("\n\t\t(1) HOSPEDAGEM\n");
			printf("\t\t  (2) DADOS DO SISTEMA\n");
			printf("\t\t    (3) TECNICO\n");
			printf("\n\t\t(X) SAIR\n");
			printf("\n\t\tOPÇÃO: ");
			break;
		}
		case 2:{
			mostrar_texto(0);
			printf("\n\tHOSPEDAGEM\n\n");
			printf("\t\t(1) NOVO HOSPEDE\n");
			printf("\t\t  (2) EDITAR DADOS DE UM CLIENTE\n");
			printf("\t\t    (3) FINALIZAR RESERVA DE UM HOSPEDE\n");
			printf("\t\t      (4) BUSCAS\n");
			printf("\t\t        (5) LISTA DE HOSPEDES\n");
			printf("\n\t\t(X) VOLTAR\n");
			printf("\n\t\tOPÇÃO: ");
			break;
		}
		case 5:{
			mostrar_texto(0);
			printf("\n\tPESQUISAR\n\n");
			printf("\t\t(1) PESQUISA POR NOME\n");
			printf("\t\t  (2) PESQUISA POR CPF\n");
			printf("\t\t    (3) PESQUISA POR ID\n");
			printf("\n\t\t(X) VOLTAR\n");
			printf("\n\t\tOPÇÃO: ");
			break;
		}
		case 6:{
			mostrar_texto(0);
			printf("\n\tNOVOS HOSPEDE\n\n");
			printf("\t\t(1) REGISTRAR NOVO HOSPEDE\n");
			printf("\t\t  (2) VER LISTA DE QUARTOS DISPONIVEIS\n");
			printf("\t\t    (3) SERVICOS ADICIONAIS\n");
			printf("\n\t\t(X) VOLTAR\n");
			printf("\n\t\tOPÇÃO: ");
			break;			
		}
		case 7:{
			mostrar_texto(0);
			puts("\n\tCLIENTES HOSPEDADOS\n\n");
			break;
		}
		case 8:{
			mostrar_texto(0);
			printf("\n\tDADOS DO SISTEMA\n");
			printf("\n\t\t(1) QUANTIDADE DE RESERVAS ATIVAS \n");
			printf("\t\t  (2) HISTORICO DE HOSPEDES\n");
			printf("\t\t   (3) LISTAR QUARTOS\n");
			printf("\n\t\t(X) VOLTAR\n");
			printf("\n\t\tOPÇÃO: ");
			break;
		}
		case 9:{
			mostrar_texto(0);			
			break;
		}
		case 10:{
			printf("\t>>> LENDO ARQUIVOS ....\n\n");
			printf("\t>>> ARQUIVOS CARREGADOS ....\n");
			printf("\n\n!!! PARA EVITAR PERDAS DE DADOS IMPORTANTES, NAO DESLIGUE O COMPUTADOR ANTES DE");
			printf("\n\n\t\tSAIR DO PROGRAMA OU O FECHE REPENTINAMENTE !!!\n\n");
			printf("\n\n>>> PRESSIONE <ENTER> PARA CONTINUAR ");
			getchar();
			break;
		}
		case 11:{
			mostrar_texto(0);
			printf("\n\tFINALIZAR RESERVA\n\n");
			printf("\t\t(1) LISTAR HOSPEDES\n");
			printf("\t\t (2) DIGITAR ID DO HOSPEDE\n");
			printf("\n\t\t(X) VOLTAR\n");
			printf("\n\t\tOPÇÃO: ");
			break;
		}
		case 12:{
			mostrar_texto(0);
			printf("\n\tALTERAR RESERVA\n\n");
			printf("\t\t(1) LISTAR HOSPEDES\n");
			printf("\t\t (2) DIGITAR ID DO HOSPEDE\n");
			printf("\n\t\t(X) VOLTAR\n");
			printf("\n\t\tOPÇÃO: ");
			break;
		}
		case 13:{
			mostrar_texto(0);
			printf("\n\tTECNICO\n");
			printf("\n\t\t(1) ALTERAR LOGIN\n");
			printf("\t\t  (2) FAZER BACK UP DOS ARQUIVOS\n");
			printf("\t\t    (3) REMOVER TODOS OS DADOS DO SISTEMA\n");
			printf("\t\t      (4) RESTAURAR BACK UP\n");
			printf("\n\t\t(X) VOLTAR\n");
			printf("\n\t\tOPÇÃO: ");
			break;
		}
		case 14:{
			mostrar_texto(0);
			printf("\n\tSELECIONAR QUARTO\n");
			printf("\n\t\t(1) PRESINDENCIAL\n");
			printf("\n\t\t (2) LUXO SIMPLES");
			printf("\n\t\t  (3) LUXO DUPLO");
			printf("\n\t\t   (4) LUXO TRIPLO\n");
			printf("\n\t\t  (5) EXECUTIVO SIMPLES");
			printf("\n\t\t (6) EXECUTIVO DUPLO");
			printf("\n\t\t(7) EXECUTIVO TRIPLO\n");
			printf("\n\t\tOPÇÃO: ");
			break;
		}
		case 25:{
			puts("                  |\\==================\\\\                	    ");
			puts("                  ||\\                  \\\\                  	");
			puts("                  ||\\\\                  \\\\                 	");
			puts("                  || \\\\                  \\\\                 	");
			puts("                  ||  \\\\                  \\\\                	");
			puts("                  ||   \\\\                  \\\\               	");
			puts("                  ||    \\\\_ _ _ _ _ _ _ _ _ \\\\              	");
			puts("                  ||     ||||              |||              		");
			puts("                  ||     ||||  _   _   _   |||             		");
			puts("                  ||     |||| |_| |_| |_|  |||             		");
			puts("        ----------||     ||||  _   _   _   |||              		");
			puts("         \\\\       ||     |||| |_| |_| |_|  |||             		");
			puts("          \\\\      ||     ||||  _   _   _   |||              	");
			puts("           \\\\     ||     |||| |_| |_| |_|  |||              	"); 
			puts("            \\\\    ||     ||||  _   _   _   |||              	");
			puts("             \\\\   ||     |||| |_| |_| |_|  |||              	");
			puts("              \\\\  \\\\     ||||  _   _   _   |||\\             	");
			puts("               \\\\  \\\\    |||| |_| |_| |_|  |||\\\\            ");
			puts("                \\\\  \\\\   ||||              ||| \\\\  CAMPINA  ");
			puts("                 \\\\  \\\\  ||||  __________  |||  \\\\  CONFORT ");
			puts("                  \\\\  \\\\ |||| /__________\\ |||   \\\\  PREMIUM");
			puts("                   \\\\  \\\\|||| || ||  || || |||    \\\\         ");
			puts("                    \\\\  \\||||_|| ||__|| ||_|||     \\\\       	 ");
			puts("                     \\\\=============================\\\\     	 ");
			puts("                      \\\\=============================\\\\     	 ");
			puts("                       \\\\=============================\\\\     \n");
		}
	}
}