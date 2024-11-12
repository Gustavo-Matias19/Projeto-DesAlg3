#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "trade.h"
#include "cadastro.h"
#include "funcoes.h"

int main(){
    int opcao, continuar = 1;
    while (continuar) {
        printf("\n=-=-= Menu de Administrador =-=-=\n");
        printf("1. Cadastrar novo investidor\n");
        printf("2. Excluir investidor\n");
        printf("3. Adicionar cripotomoeda\n");
        printf("4. Excluir cripotomoeda\n");
        printf("5. Consultar saldo de investidor\n");
        printf("6. Consultar extrato de investidor\n");
        printf("7. Atualizar cotacao de cripotomoedas\n");
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
                printf("Cadastrar novo investidor\n");
                break;
            case 2:
                printf("Excluir investidor\n");
                break;
            case 3:
                printf("Adicionar cripotomoeda\n");
                break;
            case 4:
                printf("Excluir cripotomoeda\n");
                break;
            case 5:
                printf("Consultar saldo de investidor\n");
                break;
            case 6:
                printf("Consultar extrato de investidor\n");
                break;
            case 7:
                printf("Atualizar cotacao de cripotomoedas\n");
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