// LOGIN

#define PSSWD "DATABASE/.1515841051"

typedef struct passwd{
	char passw[32];
	char idntf[32];	
}PASS;

FILE *pwd;

int check();
int create(PASS *PSS);
int gravar_pw(PASS *PSS);
void login();
