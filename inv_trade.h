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


void carteira(struct Investidores *investidor, struct Criptomoeda *criptos, int qtd_moedas);
void depositar_reais(struct Investidores *investidor);
void sacar_reais(struct Investidores *investidor);
void comprar_cripto(struct Investidores *investidor, struct Criptomoeda *criptos, int qtd_moedas);
void vender_cripto(struct Investidores *investidor, struct Criptomoeda *criptos, int qtd_moedas);
void consultar_cotacao(struct Criptomoeda *criptos, int qtd_moedas);
#endif
