//
// Created by diego on 03/09/2019.
//
/**
 * Arquivo com as structs usados no programa
 */
#include <bits/types/time_t.h>
#include "services.h"

#ifndef HOTEL_TIPOS_H
#define HOTEL_TIPOS_H

#endif //HOTEL_TIPOS_H

typedef struct {
    int numero; // número do quarto
    int classe; // categoria do quarto
    char descricao[20]; // luxo, simples, executivo, ...
    float valor_quarto; // preço do quarto
} QUARTO;

typedef struct {

    char rua[61];
    int numero;
    char bairro[61];
    char cidade[61];
    char estado[31];
    char pais[31];

} ENDERECO;

typedef struct {
    int id; // identificador do cliente
    int status; // status da reserva (ativo, inativo) (0, 1)
    char nome[100 + 1];
    char cpf[15];
    char cartao_credito[30];
    char numero_celular[20];

    ENDERECO endereco; // dados do endereço do cliente
} CLIENTE;

typedef struct {
    int id; // identificador da reserva
    int status; // status da reserva (ativo, inativo) (0, 1)

    time_t data_reserva; // data da realização da reserva
    time_t inicio;  // data em que a reserva inicia
    time_t final; // data em que a reserva acaba

    CLIENTE cliente; // cliente que realizou a reserva
    QUARTO quarto; // quarto associado a reserva
} RESERVA;

typedef struct {
    int id; // identificador da fatura
    CLIENTE cliente; // cliente associado a fatura
    float valor; // valor da fatura

    SERVICE services[10]; // serviços associados a fatura
} FATURA;

typedef struct {
    int id; // identificador do carro
    int tipo; // identificador do tipo do carro
    char modelo[30]; // modelo do carro
    float valor; // preço da reserva do carro

} CAR;

typedef struct {
    int id; // identificador da fatura
    int status; // estado do contrato (ativo, inativo)
    CLIENTE cliente; // cliente associado ao contrato
    RESERVA reserva; // reserva associada ao contrato
    FATURA fatura; // fatura associada ao contrato

} CONTRATO;