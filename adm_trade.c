#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "inv_trade.h"
#include "adm_trade.h"
#include "cadastro.h"
#include "funcoes.h"

//funçao para adicionar criptomoedas

void adicionar_criptomoeda(struct Criptomoeda *criptos, int *qtd_moedas) {
    // abre o txt para armazenar as criptos
    FILE *file = fopen("criptomoedas.txt", "a");
    if (!file) {
        printf("Erro ao abrir o arquivo de criptomoedas.\n");
        return;
    }

    // verifica se já não atingiu o maximo de criptos
    if(*qtd_moedas > MAX_CRIPTOS){
        printf("O estoque está cheio. Não é possível adicionar mais criptomoedas.\n");
        return;
    }

    struct Criptomoeda nova_cripto;
    
    // Nome da cripto
    do {
        printf("Digite o nome da nova criptomoeda: ");
        if (fgets(nova_cripto.nome, MAX_DIGITOS, stdin) == NULL) {
            printf("Erro ao ler nome da cripto, tente novamente!\n");
            continue;
        }
        nova_cripto.nome[strcspn(nova_cripto.nome, "\n")] = '\0';
    } while (strlen(nova_cripto.nome) == 0);

    // Taxa de compra
    do {
        printf("Digite a taxa de compra: ");
        if (scanf("%f",nova_cripto.taxa_compra) != 1) {
            printf("Erro ao ler taxa de compra do produto, tente novamente!\n");
            clearBuffer(); 
            continue;
        }
    } while (nova_cripto.taxa_compra <= 0);
    
    // Taxa de venda
    do {
        printf("Digite a taxa de venda: ");
        if (scanf("%f", nova_cripto.taxa_venda) != 1) {
            printf("Erro ao ler taxa de venda, tente novamente!\n");
            clearBuffer(); 
            continue;
        }   
    }  while (nova_cripto.taxa_venda <= 0);
    // Valor da cripto
    do {
        printf("Digite o valor da %s: R$ ", nova_cripto.nome);
        if (scanf("%f", &nova_cripto.valor) != 1) {
            printf("Erro ao ler valor da criptomoeda, tente novamente\n");
            clearBuffer();
            continue;
        }
    } while (nova_cripto.valor <= 0);

    criptos[*qtd_moedas] = nova_cripto;
    (*qtd_moedas)++;

    // salva os dados do novo produto no txt
    fprintf(file, "%s\n", nova_cripto.nome);
    fprintf(file, "%f\n", nova_cripto.taxa_compra);
    fprintf(file, "%f\n", nova_cripto.taxa_venda);
    fprintf(file, "%f\n", nova_cripto.valor);
    fclose(file);

    printf("Criptomoeda cadastrada com sucesso!\n");
}

// função de adicionar investidor
void cadastrar_investidor(struct Investidores *investidor, int *qtd_Investidor) {
    struct Investidores novo_investidor;
    
    // Nome do funcionário
    do {
        printf("Digite o nome do investidor: ");
        if(fgets(novo_investidor.nome, sizeof(novo_investidor.nome), stdin) == NULL){
            printf("Erro ao ler nome, tente novamente.\n");
            return;
        }
        novo_investidor.nome[strcspn(novo_investidor.nome, "\n")] = '\0';
    } while (strlen(novo_investidor.nome) == 0);

    // Checador de CPF
    int cpf_valido = 0;

    while (!cpf_valido) {
        printf("Digite o CPF do funcionario: ");
        if(fgets(novo_investidor.cpf, sizeof(novo_investidor.cpf), stdin) == NULL) {
            printf("Erro ao ler CPF, tente novamente.\n");
            continue;
        }
        novo_investidor.cpf[strcspn(novo_investidor.cpf, "\n")] = '\0';

        if (strlen(novo_investidor.cpf) == 11) {
            cpf_valido = 1;
        }
        else {
            printf("Erro! O CPF deve ter 11 digitos.\n");
        }
        clearBuffer();
    }

    // Defs para o novo investidor
    novo_investidor.id = *qtd_Investidor + 1;  

    // Incrementa o número de funcionários
    investidor[*qtd_Investidor] = novo_investidor;
    (*qtd_Investidor)++;

    printf("Investidor cadastrado com sucesso! ID: %d\n", novo_investidor.id);
}
