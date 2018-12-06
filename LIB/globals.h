// VARIAVEIS GLOBAIS E DEFINES


#define DB     "DATABASE/CONTRATOS/ABERTOS/DB_CLIENTS.DAT"
#define DB_TMP "DATABASE/CONTRATOS/ABERTOS/DB_CLIENTS_TMP.DAT"
#define L_DB   "LOG/DB_CLIENTS.TXT"

#define BKP		"DATABASE/BKP/DB_CLIENTS.DAT"

#define DB_R   	"DATABASE/CONTRATOS/FECHADOS/DB_CLIENTS.DAT"
#define L_DB_R 	"LOG/DB_CLIENTS.TXT"

#define QRTS 	"DATABASE/QUARTOS/DB_ROOMS.DAT"
#define L_QRTS 	"DATABASE/QUARTOS/REG_ROOMS.DAT"
#define L_QTMP	"DATABASE/QUARTOS/REG_ROOMS_TMP.DAT"

#define INF 	"DATABASE/USERS.DAT"
#define L_INF 	"LOG/LOG_USERS.TXT"


FILE *database;
FILE *database_temp;
FILE *l_database;

FILE *database_reg;

FILE *rooms;
FILE *l_rooms;
FILE *l_rooms_temp;

FILE *users;
FILE *l_users;

int users_cadastrados;
int new_id;
int aberto;

DATA date;
HORA h;
typedef struct tm DATE;
DATE *local;
time_t t;

