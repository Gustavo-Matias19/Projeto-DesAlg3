#ifndef adm_trade_h
#define adm_trade_h

#define MAX_DIGITOS 50
#define MAX_CRIPTOS 100

struct Criptomoeda {
    char nome[MAX_DIGITOS];
    float taxa_compra;
    float taxa_venda;
    float valor;
};

struct Investidores {
    char nome[50];
    char cpf[12];
    int quantidade;
    char senha[7];
    int id;
};

void adicionar_criptomoeda(struct Criptomoeda *criptos, int *qtd_moedas);

#endif