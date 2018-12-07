typedef struct hora{
	int s,m,h;
}HORA;

typedef struct quarto{
	
	int 	num;
	int 	tipo;
	char 	classe[18];
	float 	vlr_nrm;
	float 	vlr_alt;

}QUARTO;

typedef struct endereco{
	
	char rua[60+1];
	int  num;
	char bairro[60+1];
	char cidade[60+1];
	char estado[30+1];
	char pais[30+1];	

}ENDERECO;

typedef struct pessoa{	
	char nome[100+1];
	char cpf[15];
	char cred_card[30];
	char cel[20];
	ENDERECO end;
	double id;
	bool ativo;
}CLIENTE;

typedef struct data{
	int d, m, a;
}DATA;

typedef struct{
	time_t ini;
	time_t fim;
}TEMPO;

typedef struct{
	int num;
	int tipo;
	double id;
	bool status;
	TEMPO res;
	time_t agendamento;
}RESERVAS;

typedef struct service{
	char nome[30+1];
	char dscric[66+1];
	float prc_norm;
	float prc_alta;
	time_t data;
	int   id;
}SERVICE;

typedef struct fatura{
	float vlr_fin;
	float vlr_adc;	
}FATURA;

typedef struct carro{
	int id;
	char classe[15];
	char model[30];
	int tipo;
	float vlr_alt;
	float vlr_nrm;
	bool ocupado;	
}CAR;

typedef struct contrato{
	
	double id;
	
	bool status;
	int dias_reserva;
	int dias_alt_tmp;
	
	CLIENTE cliente;
	TEMPO res;
	QUARTO qrt;
	RESERVAS r;
	
	float fatura;
	char fat[31];
	int num;

}CONTRATO;
