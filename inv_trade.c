#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "adm_trade.h"
#include "cadastro.h"
#include "funcoes.h"


// Funcao para consultar o saldo
void carteira(struct Investidores *investidor, struct Criptomoeda *criptos, int qtd_moedas) {
    printf("\n--- Carteira do Investidor ---\n");
    printf("Carteira de:\n", investidor->nome);
    printf("Saldo em R$: %.2f\n", investidor->saldo);
    printf("Criptomoedas em posse:\n");
    for (int i = 0; i < qtd_moedas; i++) {
        if (criptos[i].quantidade > 0) {
            printf("%d. %s - Quantidade: %.2f - Cotacao Atual: R$ %.2f\n",
                   i + 1, criptos[i].nome, criptos[i].quantidade, criptos[i].valor);
        }
    }
}

// Deposito
void depositar_reais(struct Investidores *investidor) {
    float valor;
    printf("Digite o valor do deposito: R$ ");
    if (scanf("%f", &valor) != 1) {
        printf("Erro ao ler o valor do deposito.\n");
        clearBuffer();
        return;
    }

    if (valor > 0) {
        investidor->saldo += valor;
        registrarExtrato("Deposito", valor, "Deposito em conta");
        printf("Deposito realizado com sucesso! Saldo atual: R$ %.2f\n", investidor->saldo);
    }
    else {
        printf("Valor invalido. O deposito nao foi realizado.\n");
    }
}

// Função de saque
void sacar_reais(struct Investidores *investidor) {
    float valor;
    printf("Digite o valor do saque: R$ ");
    if (scanf("%f", &valor) != 1) {
        printf("Erro ao ler o valor do saque.\n");
        clearBuffer();
        return;
    }

    if (valor > investidor->saldo) {
        printf("Saldo insuficiente para saque.\n");
    }
    else if (valor <= 0) {
        printf("Valor invalido. O saque nao foi realizado.\n");
    } 
    else {
        investidor->saldo -= valor;
        registrarExtrato("Saque", valor, "Saque em conta");
        printf("Saque realizado com sucesso! Saldo atual: R$ %.2f\n", investidor->saldo);
    }
}

// Função para comprar criptomoedas
void comprar_cripto(struct Investidores *investidor, struct Criptomoeda *criptos, int qtd_moedas) {
    int escolha;
    float valor;

    printf("\nEscolha a criptomoeda para compra:\n");
    for (int i = 0; i < qtd_moedas; i++) {
        printf("%d. %s - Cotacao: R$ %.2f\n", i + 1, criptos[i].nome, criptos[i].valor);
    }

    printf("Escolha: ");
    if (scanf("%d", &escolha) != 1) {
        printf("Erro ao ler a escolha.\n");
        clearBuffer();
        return;
    }
    clearBuffer();
    escolha--;

    if (escolha < 0 || escolha >= qtd_moedas) {
        printf("Escolha invalida!\n");
        return;
    }

    printf("Digite o valor da compra: R$ ");
    if (scanf("%f", &valor) != 1) {
        printf("Erro ao ler o valor da compra.\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    if (valor > investidor->saldo) {
        printf("Falha na compra, saldo insuficiente!\n");
        return;
    }

    float taxa = valor * criptos[escolha].taxa_compra;
    float valor_final = valor - taxa;
    float quantidade = valor_final / criptos[escolha].valor;

    investidor->saldo -= valor;
    criptos[escolha].quantidade += quantidade;

    registrarExtrato("Compra", valor, criptos[escolha].nome);
    printf("Compra realizada de %.2f %s com taxa de R$ %.2f.\n", quantidade, criptos[escolha].nome, taxa);
}

// Função para vender criptomoedas
void vender_cripto(struct Investidores *investidor, struct Criptomoeda *criptos, int qtd_moedas) {
    int escolha;
    float valor;

    printf("\nEscolha a criptomoeda para venda: \n");
    for (int i = 0; i < qtd_moedas; i++) {
        printf("%d. %s - Cotacao: R$ %.2f (Na sua carteira: %.2f)\n", i + 1, criptos[i].nome, criptos[i].valor, criptos[i].quantidade);
    }

    printf("Escolha: ");
    if (scanf("%d", &escolha) != 1) {
        printf("Erro ao ler a escolha.\n");
        clearBuffer();
        return;
    }
    clearBuffer();
    escolha--;

    if (escolha < 0 || escolha >= qtd_moedas) {
        printf("Escolha invalida!\n");
        return;
    }

    printf("Digite o valor da venda: R$ ");
    if (scanf("%f", &valor) != 1) {
        printf("Erro ao ler o valor da venda.\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    float quantidade = valor / criptos[escolha].valor;
    if (quantidade > criptos[escolha].quantidade) {
        printf("Erro na venda, quantidade de %s insuficiente!\n", criptos[escolha].nome);
        return;
    }

    float taxa = valor * criptos[escolha].taxa_venda;
    float valor_final = valor - taxa;

    criptos[escolha].quantidade -= quantidade;
    investidor->saldo += valor_final;

    registrarExtrato("Venda", valor, criptos[escolha].nome);
    printf("Venda realizada de %.2f %s com taxa de R$ %.2f.\n", quantidade, criptos[escolha].nome, taxa);
}

// funcao para ver a cotacao das criptos
void consultar_cotacao(struct Criptomoeda *criptos, int qtd_moedas) {
    printf("\n--- Cotacao Atual das Criptomoedas ---\n");
    for (int i = 0; i < qtd_moedas; i++) {
        printf("%d. %s - Cotacao: R$ %.2f\n", i + 1, criptos[i].nome, criptos[i].valor);
    }
}
