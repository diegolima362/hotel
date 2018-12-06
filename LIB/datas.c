#include "includes.h"


void mostrar_data(){
	printf("%2d/%2d/%4d ", date.d,date.m,date.a);
}


void mostrar_dat(time_t dat){
	DATE *data = localtime(&dat);
	printf("%2d/%2d/%4d ", data->tm_mday,data->tm_mon + 1,data->tm_year + 1900);
}


void mostrar_hora(){
	char c = ' ', d = ' ';
	if(h.h < 10)
		c = '0';
	if(h.m < 10)
		d = '0';

	printf("%c%d :%c%d ",c,h.h,d,h.m);
}


void ler_datas(){
	
	t = time(NULL);
	local = localtime(&t);
	date.a = local->tm_year+1900;
	date.m = local->tm_mon+1;
	date.d = local->tm_mday;
}


void ler_hora(){
	h.s = local->tm_sec;
	h.m = local->tm_min;
	h.h = local->tm_hour;
}


int pegar_dat(time_t *data){
	time_t t;
 	DATE * ti;
 	DATA dat;
	
	printf("\n\n\t\t\tINSIRA UMA DATA\n\n");
	printf ("\t\t\tDIA: "); fflush(stdout); scanf ("%d",&dat.d);
	printf ("\t\t\tMES: "); fflush(stdout); scanf ("%d",&dat.m); 
	printf ("\t\t\tANO: "); fflush(stdout); scanf ("%d",&dat.a);
	
	if(dat.a<100)
		dat.a+=2000;

	if(testar_dat(dat)==0){
		printf("\n\t\tDATA INVALIDA\n");	
		return 0;
	}	

	time ( &t );
	ti = localtime ( &t );
	ti->tm_year = dat.a - 1900;
	ti->tm_mon 	= dat.m - 1;
	ti->tm_mday = dat.d;
	*data = mktime(ti);

	return 1;
}


int testar_dat(DATA dat){
	
	bool bi = bissexto(dat.a);

	//DATA FORMATO INVALIDO
	if(dat.d < 1 || dat.d > 31 || dat.m < 1 || dat.m > 12 || dat.a < date.a)
		return 0; 
	//29 E ANO NAO BISSEXTO
	if(dat.d > 28 && dat.m == 2 && !bi)
		return 0;
	//MES
	if(dat.m < date.m && dat.a <= date.a)
		return 0;
	//DIA INVALIDO
	if(dat.d < date.d && (dat.m <= date.m && dat.a <= date.a))
		return 0;
	
	if(dat.d > 29 && dat.m == 2)
		return 0;

	if(dat.d > 30 && (dat.m == 4 || dat.m == 6 || dat.m == 9 || dat.m == 11))
		return 0;

	return 1;	
}


int comparar_datas(TEMPO dat, TEMPO comp){
	time_t i;
	
	if(comp.ini == dat.ini || comp.ini == dat.fim)
		return 0;
	if(comp.fim == dat.ini || comp.fim == dat.fim)
		return 0;
	
	for(i=comp.ini;i<=comp.fim;i+=86400){
		if( (i >= dat.ini && i <= dat.fim)){
			return 0;
		}
	}

	return 1;
}

int alta_temp(TEMPO t){
	int dias = 0;
	time_t i;
	DATE *aux;

	for(i=t.ini; i<=t.fim; i+=86400){
		aux = localtime(&i);
		if(aux->tm_mon == 11 || aux->tm_mon == 0 || aux->tm_mon == 5 || aux->tm_mon == 6)
			dias++;
	}

	printf("\nDIAS EM ALTA %d\n", dias);
	return dias;
}

float qtd_dias(TEMPO dat){
	return difftime(dat.fim, dat.ini) / 60 / 60 / 24;
}


bool bissexto(int ano){

	if(ano % 400 == 0)
		return  true;		
	
	if((ano % 4 == 0) && (ano % 100 != 0))
		return true;		
	
	return false;
}

