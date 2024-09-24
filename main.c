#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

int main() {
    char usuario[USUARIO];
    char senha[SENHA];
    char cpf[CPF];

    // Criar a conta com validação de usuário, CPF e senha
    cadastro(usuario, cpf, senha);

    // Solicitar login
    printf("\nFaca login para acessar o sistema.\n");
    login(usuario, senha);

    float saldo_reais = 0;
    Criptomoeda *criptos = malloc(3 * sizeof(Criptomoeda));
    if (criptos == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Inicializando as criptomoedas
    strcpy(criptos[0].nome, "Bitcoin");
    strcpy(criptos[1].nome, "Ethereum");
    strcpy(criptos[2].nome, "Ripple");
    criptos[0].cotacao = 50000.0;
    criptos[1].cotacao = 3000.0;
    criptos[2].cotacao = 1.0;
    criptos[0].quantidade = 0.0;
    criptos[1].quantidade = 0.0;
    criptos[2].quantidade = 0.0;

    int opcao, continuar = 1;
    srand(time(NULL));

    while (continuar) {
        printf("\n--- Menu Exchange ---\n");
        printf("1. Deposito\n");
        printf("2. Saque\n");
        printf("3. Consultar saldo\n");
        printf("4. Comprar Criptomoedas\n");
        printf("5. Vender Criptomoedas\n");
        printf("6. Atualizar Cotacao de Criptomoedas\n");
        printf("7. Ver Extrato\n");
        printf("8. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Erro ao ler a opcao.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();  

        switch (opcao) {
            case 1:
                depositar_reais(&saldo_reais);
                break;
            case 2:
                sacar_reais(&saldo_reais, senha);  
                break;
            case 3:
                carteira(&saldo_reais, criptos, 3);
                break;
            case 4:
                comprar_cripto(&saldo_reais, criptos, 3, senha);  
                break;
            case 5:
                vender_cripto(&saldo_reais, criptos, 3, senha);  
                break;
            case 6:
                atualizar_cotacao(criptos, 3);
                break;
            case 7:
                printf("desenvolvedores animais nao fizeram ainda :)");
                break;
            case 8:
                continuar = 0;
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }

    free(criptos);
    return 0;
}
