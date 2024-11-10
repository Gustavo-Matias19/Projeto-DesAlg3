#ifndef trade_h
#define trade_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastro.h"

// struct de extrato
typedef struct{
    char data[11];
    char tipoOperacao[10];
    float valor;
    float taxa;
    char criptomoeda[10];
    int idUsuario;
} Transacao;

// struct com dados de criptomoeda
typedef struct{
    char nome[50];
    float cotacao;
    float quantidade;
} Criptomoeda;

// struct com dados do usuario
typedef struct{
    int id;
    char nome[50];
} Usuario;

void carteira(float *, Criptomoeda *, int);
void depositar_reais(float *);
void sacar_reais(float *, char *);
void comprar_cripto(float *, Criptomoeda *, int, char *);
void vender_cripto(float *, Criptomoeda *, int, char *);
void salvarTransacao(Usuario, Transacao);
void consultarExtrato();
#endif
