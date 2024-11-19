#ifndef adm_trade_h
#define adm_trade_h

#define MAX_DIGITOS 50
#define MAX_CRIPTOS 100
#define MAX_INVESTIDORES 50

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
    float saldo;
};

// Estrutura para o administrador
struct Adms {
    char nome_adm[50];
    char senha[7];
};

//func para cadastro
void cadastrar_adm(struct Adms *adm);
int login(struct Adms *adm);

// func para criptos
void adicionar_criptomoeda(struct Criptomoeda *criptos, int *qtd_moedas);
void criptos_txt(struct Criptomoeda *criptos, int);
int ler_criptos_txt(struct Criptomoeda *criptos, int *qtd_moedas);
void remover_criptomoeda(struct Criptomoeda *criptos, int *qtd_moedas);
void atualizar_cotacao(struct Criptomoeda *criptos, int *qtd_moedas);

//func para invest
void cadastrar_investidor(struct Investidores *investidor, int *);
void invest_txt(struct Investidores *investidor, int);
void remover_investidor(struct Investidores *investidor, int *);
int ler_invest_txt(struct Investidores *investidores, int *qtd_investidores);
void consultar_saldo_invest(struct Investidores *investidor, int *qtd_investidor);
#endif