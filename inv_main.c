#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "adm_trade.h"
#include "cadastro.h"
#include "funcoes.h"

int main(){
    
    // Defs para o cadastro dos investidores
    struct Investidores investidor[MAX_INVESTIDORES];
    struct Investidores investidor_logado;

    int qtd_investidor = 0;
    float saldo = investidor_logado.saldo;
    ler_invest_txt(investidor, &qtd_investidor);


    printf("==== Bem-vindo a Exchange ====\n");

    // loop para o login
    int login_sucesso = 0;
    while (!login_sucesso) {
        printf("\n--- Login ---\n");
        login_sucesso = login_invest(investidor, qtd_investidor, &investidor_logado);
    }
 
 
    int opcao, continuar = 1;
    while (continuar) {
        printf("\n=-=-= Menu de Investidor =-=-=\n");
        printf("1. Deposito\n");
        printf("2. Saque\n");
        printf("3. Consultar saldo\n");
        printf("4. Comprar Criptomoedas\n");
        printf("5. Vender Criptomoedas\n");
        printf("6. Consultar Cotacao de Criptomoedas\n");
        printf("7. Ver Extrato\n");
        printf("8. Sair\n");
        printf("Digite sua opcao: ");
        if(scanf("%d", &opcao) != 1){
            fprintf(stderr, "Erro ao ler valor, tente novamente\n");
            clearBuffer();
            continue;
        };
        clearBuffer();

        switch (opcao) {
            case 1:
                printf("deposito\n");
                break;
            case 2:
                printf("Saque\n");
                break;
            case 3:
                printf("Consultar saldo\n");
                break;
            case 4:
                printf("Comprar Criptomoedas\n");
                break;
            case 5:
                printf("Vender Criptomoedas\n");
                break;
            case 6:
                printf("Consultar Cotacao de Criptomoedas\n");
                break;
            case 7:
                printf("Ver Extrato\n");
                break;
            case 8:
                printf("Saindo...\n");
                continuar = 0;
                break;
            default:
                printf("Opcao invalida.\n");
        }
    }

    invest_txt(investidor, qtd_investidor); // Salva as alterações feitas pelo investidor no txt
    return 0;
}
