#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cadastro.h"
#include "funcoes.h"
#include "inv_trade.h"
#include "adm_trade.h"

int main(){
    // defs para adms
    struct Adms adm;
    int logado = 0;
    cadastrar_adm(&adm);

    while (!logado) {
        logado = login(&adm);
    }
    
    // Def para as criptos
    int qtd_moedas = 0;
    struct Criptomoeda criptos[MAX_CRIPTOS];
    ler_criptos_txt(criptos, &qtd_moedas);

    // Def para os investidores
    int qtd_investidor = 0;
    struct Investidores investidor[MAX_INVESTIDORES];
    ler_invest_txt(investidor, &qtd_investidor);

    int opcao, continuar = 1;
    while (continuar) {
        printf("\n=-=-= Menu de Administrador =-=-=\n");
        printf("1. Cadastrar novo investidor\n");
        printf("2. Excluir investidor\n");
        printf("3. Adicionar criptomoeda\n");
        printf("4. Excluir criptomoeda\n");
        printf("5. Consultar saldo de investidor\n");
        printf("6. Consultar extrato de investidor\n");
        printf("7. Atualizar cotacao de criptomoedas\n");
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
                cadastrar_investidor(investidor, &qtd_investidor);
                break;
            case 2:
                remover_investidor(investidor, &qtd_investidor);
                break;
            case 3:
                adicionar_criptomoeda(criptos, &qtd_moedas);
                break;
            case 4:
                remover_criptomoeda(criptos,&qtd_moedas);
                break;
            case 5:
                consultar_saldo_invest(investidor, &qtd_investidor);
                break;
            case 6:
                printf("Consultar extrato de investidor\n");
                break;
            case 7:
                atualizar_cotacao(criptos, &qtd_moedas);
                break;
            case 8:
                printf("Saindo...\n");
                continuar = 0;
                break;
            default:
                printf("Opcao invalida.\n");
        }
    }

}