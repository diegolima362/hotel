

void listar_qrts();
void mostrar_qrts(QUARTO q);

int  list_qrt_restrit(int tipo, int *v, int m);
void mostrar_qrts_restrict(QUARTO q);	

void checar_vagas();

int reservar_qrt(CONTRATO *p, RESERVAS *r);
int	escolher_tip();
void alocar_qrt(int num, QUARTO* qrt);
int select_qrt(int tipo, int *v, int m);

int buscar_qrt(int l);
int qtd_qrts(int tipo);
int test_num(int tipo, int num, int *v, int m);

void criar_qrts();

