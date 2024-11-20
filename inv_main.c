#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "inv_trade.h"
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

    // Defs para criptomoedas
    struct Criptomoeda criptos[MAX_CRIPTOS];
    int qtd_moedas = 0;
    ler_criptos_txt(criptos, &qtd_moedas);


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
                depositar_reais(&investidor_logado);
                break;
            case 2:
                sacar_reais(&investidor_logado);
                break;
            case 3:
                carteira(&investidor_logado, criptos, qtd_moedas);
                break;
            case 4:
                comprar_cripto(&investidor_logado, criptos, qtd_moedas);
                break;
            case 5:
                vender_cripto(&investidor_logado, criptos, qtd_moedas);
                break;
            case 6:
                consultar_cotacao(criptos, qtd_moedas);
                break;
            case 7:
                consultarExtrato();
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
    criptos_txt(criptos, qtd_moedas); // salva as alteraçoes do investidor no txt
    return 0;
}
