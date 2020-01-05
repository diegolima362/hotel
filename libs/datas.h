//
// Created by Diego on 03/09/2019.
//

#ifndef HOTEL_DATAS_H
#define HOTEL_DATAS_H

#endif //HOTEL_DATAS_H

typedef struct tm DATE;

/**
 * ler date e hora atual do sistema operacional
 *
 * @return struct com o tempo atual
 */
struct tm ler_data();

/**
 * extrai uma data de um string com formato 'yyyy-mm-dd' para struct tm
 *
 * @param date struct que recebera os dados extraidos
 * @param str data no formato (yyyy-mm-dd)
 * @return strut com os campos preenchidos
 */
struct tm *formatar_data_struct(struct tm *date, char *str);

/**
 * formata uma data (yyyy-mm-dd) a partir de uma struct tm
 *
 * @param date struct com a data que sera formatada
 * @param str string que recebera a data formatada
 * @return data formata yyyy-mm-dd
 */
char *formatar_data_sql(struct tm *date, char *str);

/**
 * compara duas datas day, mon, year
 *
 * @param time_1
 * @param time_2
 * @return <0: time_1 menor, 0: datas iguais, >0: time_1 maior
 */
int comparar_data(struct tm *time_1, struct tm *time_2);

/**
 * teste se ano passado é bissexto
 *
 * @param ano
 * @return  1: bissexto, 0: nao bissexto
 */
int bissexto(int ano);

/**
 * valida os valores de uma data day, mon, year
 *
 * @param date
 * @return 1: valida, 0: invalida
 */
int validar_data(struct tm *date);

/**
 * teste se duas datas formam um intervalo valido de tempo day, mon, year
 *
 * @param data_inicio
 * @param data_final
 * @return 1: valido, 0:invalido
 */
int validar_periodo(struct tm *data_inicio, struct tm *data_final);
