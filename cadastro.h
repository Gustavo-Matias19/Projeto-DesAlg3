#ifndef cadastro_h
#define cadastro_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adm_trade.h"

// Estrutura para o administrador
struct Adms {
    char nome_adm[50];
    char senha[7];
};

//func para cadastro
void cadastrar_adm(struct Adms *adm);
int login(struct Adms *adm);
int login_invest(struct Investidores *investidor, int qtd_investidor, struct Investidores *investidor_logado);
#endif