// FUNCOES DE HOSPEDAGEM
#include "includes.h"


void criar_contrato(){
	int l;
	int hold = 1;

	do{
		limpar_tela();
		mostrar_texto(6);

		l = opc();

		switch(l){
			case  1:{
				inserir_contrato();
				break;
			}
			case  2:{
				checar_vagas();
				break;
			}
			case  3:{
				contratar_srvc(); 
				break;
			}
			case  -1: hold = 0; break;

			default : tipo_de_erro(1); break;
		}
	}while(hold);
}


void inserir_contrato(){
	CONTRATO p;
	RESERVAS r;
	
	ler_arquivos();
	ler_qrts();

	int res = reservar_qrt(&p, &r);
	
	if(res == -1)
		return;
	
	if(res == 0){		
		printf("\n\t\tNAO HA QUARTOS DISPONIVEIS PARA ESSA DATA \n\t\tOU PERIOSO DE RESERVA INVALIDO\n");
		pausa();
		return;
	}

	ler_cliente(&p.cliente);
	
	p.id = p.cliente.id;
	p.status = true;
	p.dias_reserva = qtd_dias(p.res);
	p.dias_alt_tmp = alta_temp(p.res);

	r.id = p.cliente.id;
	r.status = true;

	p.r = r;

	alocar_qrt(r.num, &p.qrt);

	criar_fatura(p.fat, p.id);

	gravar_contrato(p);	
	gravar_reservas(r);

	fechar_qrts();
	fechar_arquivos();

	limpar_tela();
	printf("\n\n\t\t\tRESERVA REALIZADA COM SUCESSO!\n\t\t<ENTER>");
	pausa();
}


void alterar_contrato(double n){

	ler_arquivos();

	if(contar_clientes()==0){
		printf("\n\n\t\tNAO EXITEM HOSPEDES REGISTRADOS!!!\n");
		getchar();
		return;
	}

	CONTRATO reg;
	double id = n;
	bool x = false;
	char op[2];

	if(n == 0)
		id = menu_edita();

	rewind(database);

	while(fread(&reg,sizeof(CONTRATO),1,database)){
		if(reg.id == id && reg.status){
			x=true;
			break;
		}
	}

	if(!x){
		puts("ID INEXISTENTE OU PROBLEMAS NO POSICIONAMENTO!!!\n");
		tipo_de_erro(2);
		return;
	}

	limpar_tela(); mostrar_texto(0);

	printf("\n\tDADOS DO HOSPEDE\n\n");
	mostrar_cliente(reg);
	printf("\n\n\t\tEDITAR A RESERVA (S/N)? "); limpar_teclado(); 
	
	scanf("%s", op); upper(op);

	if(op[0] != 'S'){
		printf("\n\tRESERVA NAO EDITADA !!! \n\n");
		tipo_de_erro(2); 
		return;
	}

	mod_cliente(&reg.cliente);
	puts("\n\nDADOS EDITADOS !!!"); getchar();
	mostrar_cliente(reg); getchar();

	
	fseek(database,-(long)sizeof(CONTRATO), SEEK_CUR);
	fwrite(&reg,sizeof(CONTRATO),1,database);
	
}

void remover_contrato(double n){
	
	if(contar_clientes() == 0){
		printf("\n\t\tNAO EXISTEM RESERVAS ATIVAS\n");
		getchar();
		return;
	}

	ler_arquivos();
	ler_qrts();

	CONTRATO reg;

	double id = n;
	int x = 0;
	char op[2];

	if(n == 0){
		id = menu_remove();
	}


	rewind(database);
	
	while(fread(&reg,sizeof(CONTRATO),1,database)){
		if(reg.r.id == id){
			x=1;
			break;
		}
	}

	if(x==0){
		puts("ID INEXISTENTE OU PROBLEMAS NO POSICIONAMENTO!!!\n");
		getchar();
		return;
	}

	limpar_tela(); mostrar_texto(0);

	printf("\n\tDADOS DO HOSPEDE\n\n");
	mostrar_cliente(reg);
	printf("\n\n\t\tFINALIZAR A RESERVA (S/N)? "); limpar_teclado(); 
	
	scanf("%s", op); upper(op);

	if(op[0] != 'S'){
		printf("\n\tRESERVA NAO FINALIZADA !!! \n\n"); getchar();
		limpar_tela();
		return;
	}

	gravar_contrato_inativo(reg);
	
	fechar_fatura(&reg);
		
	
	database_temp = fopen("DATABASE/CONTRATOS/ABERTOS/DB_CLIENTS_TMP.DAT", "w+b");
	
	
	rewind(database);

	while(fread(&reg,sizeof(CONTRATO),1,database)){
		
		if(reg.id != id){
			
			fseek(database_temp, 0L, SEEK_END);
	
			if(fwrite(&reg, sizeof(CONTRATO),1,database_temp)!=1){
				puts(">>>> ERRO AO ADICIONAR O CLIENTE AO REGISTRO\n\n");
				getchar();
			}
		}
	}
	
	fclose(database_temp);
	fclose(database);
	
	system("mv DATABASE/CONTRATOS/ABERTOS/DB_CLIENTS.DAT DATABASE/CONTRATOS/ABERTOS/OLD.DAT");
	system("mv DATABASE/CONTRATOS/ABERTOS/DB_CLIENTS_TMP.DAT DATABASE/CONTRATOS/ABERTOS/DB_CLIENTS.DAT");
	
	remover_reserva(id);
	printf("\n\tRESERVA FINALIZADA!!!\n\n\t\tDADOS DA COBRANCA SALVOS NO ARQUIVO COM NOME IGUAL O ID NA PASTA FATURA\n"); getchar();
}


void gravar_contrato(CONTRATO p){
	
	fseek(database, 0L, SEEK_END);
	
	if(fwrite(&p, sizeof(CONTRATO),1,database)!=1){
		puts(">>>> ERRO AO ADICIONAR O CLIENTE AO REGISTRO\n\n");
		tipo_de_erro(2); getchar();
	}
	
	limpar_tela();
	puts(">>> CLIENTE ADICIONADO COM SUCESSO!!!");
	
}


void gravar_contrato_inativo(CONTRATO p){
	
	fopen(DB_R, "r+b");
	fseek(database_reg, 0L, SEEK_END);
		
	if(fwrite(&p, sizeof(CONTRATO),1,database_reg)!=1){
		puts(">>>> ERRO AO ADICIONAR O CLIENTE AO REGISTRO\n\n");
		tipo_de_erro(2); getchar();
	}pausa();
	fclose(database_reg);
}

void gravar_contrato_tmp(CONTRATO p){
	
	fseek(database_temp, 0L, SEEK_END);
	
	if(fwrite(&p, sizeof(CONTRATO),1,database_temp)!=1){
		puts(">>>> ERRO AO ADICIONAR O CLIENTE AO REGISTRO\n\n");
		tipo_de_erro(2); getchar();
	}
}


void mostrar_reserva(CONTRATO p){
	printf("\t\tID: %.lf\n", p.id);
	printf("\t\t NOME DO CLIENTE: %s\n", p.cliente.nome);
	printf("\t\t  CPF: %s\n", p.cliente.cpf);
	printf("\t\t   QUARTO: %d\n\n", p.r.num);
	printf("\t\t    RESERVA: "); mostrar_dat(p.res.ini); printf(" - "); mostrar_dat(p.res.fim); putchar('\n');
	puts("\t-----------------------------------------------------------------------------------\n");
}


int verificar_vagas(int tipo, TEMPO dat, int *num){
	
	RESERVAS res;
	
	int m = 20;
	int i;
	
	m = qtd_qrts(tipo);

	int v[m];
	
	for(i=0;i<m;i++){
		v[i] = 0;
	}

	i=0;
	
	while(fread(&res, sizeof(RESERVAS), 1, l_rooms)){
		if(res.tipo == tipo){
			if(comparar_datas(res.res, dat)==0){
				v[i] = res.num;
				i++;
			}			
		}
	}

	// SE TODOS OS QUARTOS NAO PUDEREM SER AGENDADOS NESSA DATA
	if(i>=m){
		return 0;
	}
	
	*num = select_qrt(tipo, v, m);

	return 1;
}


int reservas_registradas(){
	RESERVAS res;
	int i=0;

	while(fread(&res, sizeof(RESERVAS), 1, l_rooms)){
		mostrar_dat(res.res.ini);
		printf(" - ");
		mostrar_dat(res.res.ini);
		i++;
	}

	return i;
}


void remover_reserva(double id){

	RESERVAS reg;

	rewind(l_rooms);

	l_rooms_temp = fopen("DATABASE/QUARTOS/REG_ROOMS_TMP.DAT", "w+b");
	
	while(fread(&reg,sizeof(RESERVAS),1,l_rooms)){
			
		if(reg.id!=id){
				
			fseek(l_rooms_temp, 0L, SEEK_END);

			if(fwrite(&reg, sizeof(RESERVAS),1,l_rooms_temp)!=1){
				puts(">>>> ERRO AO ADICIONAR RESRVA AO REGISTRO\n\n");
			}

		}
	}

	fclose(l_rooms_temp);

	l_rooms_temp = fopen("DATABASE/QUARTOS/REG_ROOMS_TMP.DAT", "r+b");
	
	fclose(l_rooms);
	system("mv DATABASE/QUARTOS/REG_ROOMS.DAT DATABASE/QUARTOS/OLD_ROOMS.DAT");
	system("mv DATABASE/QUARTOS/REG_ROOMS_TMP.DAT DATABASE/QUARTOS/REG_ROOMS.DAT");

}


void gravar_reservas(RESERVAS r){
	
	fseek(l_rooms, 0L, SEEK_END);
	
	if(fwrite(&r, sizeof(RESERVAS),1,l_rooms)!=1){
		puts("\n\t\t>>>> ERRO AO ADICIONAR O CLIENTE AO REGISTRO\n\n");
		tipo_de_erro(2); getchar();
	}
}


void gravar_reservas_temp(RESERVAS r){
	fseek(l_rooms_temp, 0L, SEEK_END);
	
	if(fwrite(&r, sizeof(RESERVAS),1,l_rooms_temp)!=1){
		puts(">>>> ERRO AO ADICIONAR RESRVA AO REGISTRO\n\n");
		tipo_de_erro(2); getchar();
	}
}


void ler_cliente(CLIENTE *p){
	char scpf[15];
	char aux[101];
	double id = gerar_id();

	limpar_tela();
	printf("\n\n\t\t\t-------- ADICIONAR DADOS DO CLIENTE --------\n\n");

	printf("\n\t\tID: %.lf\n", id); p->id = id;
	printf("\n\t\tNOME DO CLIENTE: "); limpar_teclado();
	fgets(aux, 101, stdin); upper(aux); strcpy(p->nome, aux); 
	formatar_cpf(scpf); strcpy(p->cpf, scpf);
	printf("\t\tCARTAO DE CREDITO: "); limpar_teclado();
	fgets(aux, 30, stdin); remover_quebra(aux); strcpy(p->cred_card, aux);
	printf("\t\tTELEFONE DE CONTATO: "); limpar_teclado();
	fgets(aux, 20, stdin); remover_quebra(aux); strcpy(p->cel, aux);

	puts("\n\t\t\t>>> INSERIR ENDERECO \n");
	
	printf("\n\t\tRUA: "); limpar_teclado(); getchar();
	fgets(p->end.rua, 61, stdin);upper(p->end.rua); remover_quebra(p->end.rua);
	printf("\t\tNUMERO: ");limpar_teclado();
	scanf(" %d", &p->end.num);
	printf("\t\tBAIRRO: "); limpar_teclado();
	fgets(p->end.bairro, 61, stdin);upper(p->end.bairro); remover_quebra(p->end.bairro);
	printf("\t\tCIDADE: ");limpar_teclado();
	fgets(p->end.cidade, 61, stdin);upper(p->end.cidade); remover_quebra(p->end.cidade);
	printf("\t\tESTADO: ");limpar_teclado();
	fgets(p->end.estado, 31, stdin);upper(p->end.estado); remover_quebra(p->end.estado);
	printf("\t\tPAIS: ");limpar_teclado();
	fgets(p->end.pais, 31, stdin);upper(p->end.pais); remover_quebra(p->end.pais);
	limpar_teclado();
}


void listar_clientes(){

	if(contar_clientes() == 0){
		printf("\n\t\tNAO EXISTEM RESERVAS ATIVAS\n");
		getchar();
		return;
	}
	
	ler_arquivos();
		
	int hold = 1;
	int i, j=1, l, hold2 = 1;

	limpar_tela();
	
	do{
		mostrar_texto(7);
		printf("\t\t\t\tPAGINA 1\n\n");
		puts("\t------------------------------------------------------------------------\n");
		
		CONTRATO reg;
		rewind(database);
		
		do{
			for(i=0;;i++){
				if(fread(&reg,sizeof(CONTRATO),1,database)!=1){
					hold2 = 0; 
					break;
				}
				if(1){
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
	fechar_arquivos();
}


void mostrar_cliente(CONTRATO p){
	printf("\t\tID: %.lf\n\n", p.id);
	printf("\t\tNOME DO CLIENTE: %s\n", p.cliente.nome);
	printf("\t\tCPF: %s\n", p.cliente.cpf);
	printf("\t\tQUARTO: %d\n\n", p.r.num);
	printf("\t\tRESERVA: "); mostrar_dat(p.res.ini); printf(" - "); mostrar_dat(p.res.fim); putchar('\n');
	printf("\t\tCARTAO DE CREDITO: %s\n", p.cliente.cred_card);
	printf("\t\tTELEFONE DE CONTATO: %s\n\n", p.cliente.cel);
	puts("\t\tENDERECO: ");
	printf("\t\t%s, %d, %s\n", p.cliente.end.bairro, p.cliente.end.num, p.cliente.end.rua);
	printf("\t\t%s - %s - %s\n", p.cliente.end.cidade, p.cliente.end.estado, p.cliente.end.pais);
	
	puts("\t--------------------------------------------------------------------------------------------------------\n");
	
}


int contar_clientes(){
	RESERVAS reg;
	int num_clientes = 0;
	
	ler_qrts();
	rewind(l_rooms);	
	
	while(fread(&reg,sizeof(reg),1,l_rooms)){
		if(reg.status == true)
			num_clientes++;
	}

	fechar_qrts();
	
	return num_clientes;
}


void mod_cliente(CLIENTE *p){
	int tmp = p->id; 
	ler_cliente(p);
	p->id = tmp;
}


double menu_remove(){
	int l;
	double id;

	limpar_tela();	
	mostrar_texto(11);

	l = opc();
	
	switch(l){
		case 1:{
			listar_clientes();
			printf("\n\n\t\tDIGITE O ID PARA FAZER CHECK-OUT: ");
			scanf("%lf", &id);
			remover_contrato(id);
			break;
		}
		case 2:{
			printf("\n\t\tDIGITE O ID: ");
			scanf("%lf", &id);
			return id;
			break;
		}
		default: tipo_de_erro(1); break;
	}
}


double menu_edita(){
	int l;
	double id;

	limpar_tela();	
	mostrar_texto(12);

	l = opc();
	
	switch(l){
		case 1:{
			listar_clientes();
			printf("\n\n\t\tDIGITE O ID PARA EDITAR HOSPEDE: "); limpar_teclado();
			scanf("%lf", &id);
			alterar_contrato(id);
			break;
		}
		case 2:{
			printf("\n\t\tDIGITE O ID: "); limpar_teclado();
			scanf("%lf", &id);
			return id;
			break;
		}
		default: tipo_de_erro(1); break;
	}
}


double gerar_id(){
	time_t t;
	DATE *ti;
	time ( &t );
	ti = localtime ( &t );

	// 1 811 292 055 

	double id = 0;

	id += (ti->tm_year-100) * 10000000000;
	id += (ti->tm_mon+1) * 100000000;
	id += (ti->tm_mday) * 1000000;
	id += (ti->tm_hour) * 10000;
	id += ti->tm_min * 100;
	id += ti->tm_sec;

	return id;
}


int pagina(int *j){ 
	int l;
	printf("\n\t\t>>> PRESSIONE <ENTER> PARA MOSTRAR  A PROXIMA PAGINA OU X PARA SAIR: ");
	*j = *j+1;
	l = opc();
	limpar_tela();
	return l;
}

