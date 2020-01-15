//
// Created by diego on 03/09/2019.
//

#ifndef HOTEL_EXTRA_FUNCS_H
#define HOTEL_EXTRA_FUNCS_H

#endif //HOTEL_EXTRA_FUNCS_H

/**
 * espera pressionar tecla
 */
void pausa();

/**
 * limpar o terminal
 */
void limpar_tela();

/**
 * limpar buffer do teclado
 */
void limpar_teclado();

/**
 * retorna a string toda em maiuscula
 * @param str string para fazer uppercase
 */
char * upper(char *str);

/**
 * remover quebra de linha de uma string
 * @param str string para remover a quebra de linha
 */
void remover_quebra(char *str);

int is_in(int valor, const int*array, int tamanho);

void mostrar_titulo();
