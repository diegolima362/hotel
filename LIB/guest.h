
void criar_contrato();
void inserir_contrato();
void alterar_contrato(double n);
void remover_contrato(double n);

void gravar_contrato(CONTRATO p);
void gravar_contrato_inativo(CONTRATO p);
void gravar_contrato_tmp(CONTRATO p);


int verificar_vagas(int tipo, TEMPO dat, int *num);


int reservas_registradas();
void mostrar_reserva(CONTRATO p);
void remover_reserva(double id);
void gravar_reservas(RESERVAS r);
void gravar_reservas_temp(RESERVAS r);


void ler_cliente(CLIENTE *p);
void listar_clientes();
void mostrar_cliente(CONTRATO p);
int  contar_clientes();
void mod_cliente(CLIENTE *p);


double menu_remove();
double menu_edita();


double gerar_id();
int pagina(int *j);
