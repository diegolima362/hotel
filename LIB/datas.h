

void mostrar_data();
void mostrar_dat(time_t dat);
void mostrar_hora();


void ler_datas();
void ler_hora();
int  pegar_dat(time_t *data);

int testar_dat(DATA dat);
int comparar_datas(TEMPO dat, TEMPO comp);

int alta_temp(TEMPO t);

float qtd_dias(TEMPO dat);
bool bissexto(int ano);