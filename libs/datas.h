//
// Created by Diego on 03/09/2019.
//

#ifndef HOTEL_DATAS_H
#define HOTEL_DATAS_H

#endif //HOTEL_DATAS_H

typedef struct tm DATE;

/**
 * ler data e hora atual do sistema operacional
 * @return struct com o tempo atual
 */
struct tm *ler_data();

/**
 * extrai uma data de um string com formato 'yyyy-mm-dd' para struct tm
 * @param date struct que recebera os dados extraidos
 * @param str data no formato (yyyy-mm-dd)
 * @return strut com os campos preenchidos
 */
struct tm *formatar_data_struct(struct tm *date, char *str);

/**
 * formata uma data (yyyy-mm-dd) a partir de uma struct tm
 * @param date struct com a data que sera formatada
 * @param str string que recebera a data formatada
 * @return data formata yyyy-mm-dd
 */
char *formatar_data_sql(struct tm *date, char *str);
