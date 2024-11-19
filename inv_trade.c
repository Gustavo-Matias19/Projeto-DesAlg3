#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "adm_trade.h"
#include "cadastro.h"
#include "funcoes.h"


// Funcao para consultar o saldo
void carteira(float *saldo_reais, Criptomoeda *criptos, int menu_cripto)
{
    printf("Saldo em R$: %.2f\n", *saldo_reais);
    printf("Quantidade de Criptomoedas:\n");
    int i;
    for (i = 0; i < menu_cripto; i++){
        printf("%d. %s - Quantidade: %.2f\n", i + 1, criptos[i].nome, criptos[i].quantidade);
    }
}

// Deposito
void depositar_reais(float *saldo_reais)
{
    float valor;
    printf("Digite o valor do deposito: R$ ");
    if (scanf("%f", &valor) != 1){
        printf("Erro ao ler o valor do deposito.\n");
        clearBuffer();
        return;
    }

    if (valor > 0){
        *saldo_reais += valor;
        printf("Deposito realizado com sucesso! Saldo atual: R$ %.2f\n", *saldo_reais);
    }

    else{
        printf("Erro no deposito!\n");
    }
}

// Função de saque
void sacar_reais(float *saldo_reais, char *senha_cadastrada){
    float valor;
    if (!validar_senha(senha_cadastrada))
        return; // Valida a senha

    printf("Digite a quantia do saque: R$ ");
    if (scanf("%f", &valor) != 1){
        printf("Erro ao ler o valor do saque.\n");
        clearBuffer();
        return;
    }

    if (valor > *saldo_reais){
        printf("Saldo insuficiente!\n");
    }

    else if (valor <= 0){
        printf("Erro no saque, valor invalido!\n");
    }

    else{
        *saldo_reais -= valor;
        printf("Saque realizado com sucesso! Saldo atual: R$ %.2f\n", *saldo_reais);
    }
}

// Função para comprar criptomoedas
void comprar_cripto(float *saldo_reais, Criptomoeda *criptos, int menu_cripto, char *senha_cadastrada)
{
    if (!validar_senha(senha_cadastrada))
        return; // Valida a senha

    int escolha;
    float valor;
    printf("\nEscolha a criptomoeda para compra:\n");

    int i;
    for (i = 0; i < menu_cripto; i++){
        printf("%d. %s - Cotacao: R$ %.2f\n", i + 1, criptos[i].nome, criptos[i].cotacao);
    }

    printf("Escolha: ");
    if (scanf("%d", &escolha) != 1){
        printf("Erro ao ler a escolha.\n");
        clearBuffer();
        return;
    }
    clearBuffer();
    escolha--;

    if (escolha < 0 || escolha >= menu_cripto){
        printf("Escolha invalida!\n");
        return;
    }

    printf("Digite o valor da compra: R$ ");
    if (scanf("%f", &valor) != 1){
        printf("Erro ao ler o valor da compra.\n");
        clearBuffer();
        return;
    }
    clearBuffer(); // Limpa o buffer de entrada após scanf

    if (valor > *saldo_reais){
        printf("Falha na compra, saldo insuficiente!\n");
        return;
    }

    float taxa = valor * taxa_compra(criptos[escolha]);
    float valor_final = valor - taxa;
    criptos[escolha].quantidade += valor_final / criptos[escolha].cotacao;
    *saldo_reais -= valor;

    printf("Compra realizada de %.2f %s com taxa de R$ %.2f.\n",
           valor_final / criptos[escolha].cotacao, criptos[escolha].nome, taxa);
}

// Função para vender criptomoedas
void vender_cripto(float *saldo_reais, Criptomoeda *criptos, int menu_cripto, char *senha_cadastrada)
{
    if (!validar_senha(senha_cadastrada))
        return; // Valida a senha

    int escolha;
    float valor;
    printf("\nEscolha a criptomoeda para venda:\n");

    int i;
    for (i = 0; i < menu_cripto; i++){
        printf("%d. %s - Cotacao: R$ %.2f\n", i + 1, criptos[i].nome, criptos[i].cotacao);
    }

    printf("Escolha: ");
    if (scanf("%d", &escolha) != 1){
        printf("Erro ao ler a escolha.\n");
        clearBuffer();
        return;
    }
    clearBuffer(); // Limpa o buffer de entrada após scanf
    escolha--;

    if (escolha < 0 || escolha >= menu_cripto){
        printf("Escolha invalida!\n");
        return;
    }

    printf("Digite o valor da venda: R$ ");
    if (scanf("%f", &valor) != 1){
        printf("Erro ao ler o valor da venda.\n");
        clearBuffer();
        return;
    }
    clearBuffer(); // Limpa o buffer de entrada após scanf

    float valor_cripto = valor / criptos[escolha].cotacao;
    if (valor_cripto > criptos[escolha].quantidade){
        printf("Erro na venda, quantidade de %s insuficiente!\n", criptos[escolha].nome);
        return;
    }

    float taxa = valor * taxa_venda(criptos[escolha]);
    float valor_final = valor - taxa;
    criptos[escolha].quantidade -= valor_cripto;
    *saldo_reais += valor_final;

    printf("Venda realizada de %.2f %s com taxa de R$ %.2f.\n", valor_cripto, criptos[escolha].nome, taxa);
}

void registrarExtrato(const char *operacao, float valor, const char *detalhes)
{
    FILE *file = fopen("extrato.txt", "a");
    if (file == NULL){
        printf("Erro ao abrir o arquivo de extrato.\n");
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(file, "%02d-%02d-%d %02d:%02d:%02d - Operacao: %s | Valor: %.2f | Detalhes: %s\n",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec,
            operacao, valor, detalhes);

    fclose(file);
}

void consultarExtrato(){
    FILE *file = fopen("extrato.txt", "r");
    if (file == NULL){
        printf("Nao ha transacoes registradas.\n");
        return;
    }

    char linha[256];
    printf("\n--- Extrato de Transacoes ---\n");
    while (fgets(linha, sizeof(linha), file)){
        printf("%s", linha);
    }
    fclose(file);
}