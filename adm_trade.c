#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "inv_trade.h"
#include "adm_trade.h"
#include "cadastro.h"
#include "funcoes.h"

// funcao de cadastro dos investidores 
void cadastrar_adm(struct Adms *adm) {
    printf("Digite o nome do administrador: ");
    if(fgets(adm->nome_adm, sizeof(adm->nome_adm), stdin) == NULL) {
        printf("Erro ao ler nome do administrador.\n");
        return;
    }
    adm->nome_adm[strcspn(adm->nome_adm, "\n")] = '\0';
    
    int senhaValida = 0;

    while (!senhaValida) {
        printf("Digite uma senha de 6 digitos: ");
        if(fgets(adm->senha, sizeof(adm->senha), stdin) == NULL){
            printf("Erro ao ler senha, tente novamente.\n");
            return;
        }
        adm->senha[strcspn(adm->senha, "\n")] = '\0';

        if (strlen(adm->senha) == 6) {
            senhaValida = 1;
        } 
        else {
            printf("A senha deve ter exatamente 6 digitos.\n");
        }
        clearBuffer();
    }
    printf("Cadastro realizado com sucesso!\n\n");
}

int login(struct Adms *adm) {
    char nome_login[50];
    char senha_login[7];

    printf("--- Login ---\n");
    printf("Digite o nome do administrador: ");
    if (fgets(nome_login, sizeof(nome_login), stdin) == NULL){
        printf("Erro ao ler nome do administrador, tente novamente.\n");
        return 0;
    }
    nome_login[strcspn(nome_login, "\n")] = '\0';

    printf("Digite a senha: ");
    if(fgets(senha_login, sizeof(senha_login), stdin) == NULL){
        printf("Erro ao ler senha, tente novamente.\n");
        return 0;
    }
    senha_login[strcspn(senha_login, "\n")] = '\0';

    clearBuffer();

    if (strcmp(adm->nome_adm, nome_login) == 0 && strcmp(adm->senha, senha_login) == 0) {
        printf("Login realizado com sucesso!\n");
        return 1;
    } else {
        printf("Nome e/ou senha incorretos. Tente novamente.\n");
        return 0;
    }
}

//funçao para adicionar criptomoedas
void adicionar_criptomoeda(struct Criptomoeda *criptos, int *qtd_moedas) {
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
        if (scanf("%f", &nova_cripto.taxa_compra) != 1) {
            printf("Erro ao ler taxa de compra do produto, tente novamente!\n");
            clearBuffer(); 
            continue;
        }
        getchar();
    } while (nova_cripto.taxa_compra <= 0);
    
    // Taxa de venda
    do {
        printf("Digite a taxa de venda: ");
        if (scanf("%f", &nova_cripto.taxa_venda) != 1) {
            printf("Erro ao ler taxa de venda, tente novamente!\n");
            clearBuffer(); 
            continue;
        }   
        getchar();
    } while (nova_cripto.taxa_venda <= 0);
    // Valor da cripto
    do {
        printf("Digite o valor da %s: R$ ", nova_cripto.nome);
        if (scanf("%f", &nova_cripto.valor) != 1) {
            printf("Erro ao ler valor da criptomoeda, tente novamente\n");
            clearBuffer();
            continue;
        }
        getchar();
    } while (nova_cripto.valor <= 0);

    criptos[*qtd_moedas] = nova_cripto;
    (*qtd_moedas)++;

    criptos_txt(nova_cripto);
    printf("Criptomoeda cadastrada com sucesso!\n");
}

// txt das criptos
void criptos_txt(struct Criptomoeda criptos){
    FILE *arquivo = fopen("criptomoedas.txt", "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de criptomoedas.\n");
        return;
    }
    fprintf(arquivo, "%s\n", criptos.nome);
    fprintf(arquivo, "%.2f\n", criptos.taxa_compra);
    fprintf(arquivo, "%.2f\n", criptos.taxa_venda);
    fprintf(arquivo, "%.2f\n", criptos.valor);
    fclose(arquivo);
}

//funcao de remover criptomoeda

void remover_criptomoeda(struct Criptomoeda *criptos, int *qtd_moedas) {
    if (*qtd_moedas == 0) {
        printf("Nao ha nenhuma criptomoeda disponivel, adicione alguma e volte aqui!.\n");
        return;
    }
    //Mostra as criptomoedas disponiveis
    int i;
    char cripto_procurada[MAX_DIGITOS];
    for(i = 0; i < *qtd_moedas; i++){
        printf("Nome: %s\n", criptos[i].nome);
        printf("Taxa de compra: %.2f\n", criptos[i].taxa_compra);
        printf("Taxa de venda: %.2f\n", criptos[i].taxa_venda);
        printf("Cotacao: %.2f\n", criptos[i].valor);
    }
    printf("\nEscolha a criptomoeda para remover: ");
    if (fgets(cripto_procurada, MAX_DIGITOS, stdin) == NULL) {
        printf("Erro ao ler o nome, tente novamente.\n");
        return;
    }
    cripto_procurada[strcspn(cripto_procurada, "\n")] = '\0';
    
    // Procura a criptomoeda pelo nome
    int encontrado = 1;
    for (int i = 0; i < *qtd_moedas; i++) {
        if (strcmp(criptos[i].nome, cripto_procurada) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == 1) {
        printf("Criptomoeda nao encontrada.\n");
        return;
    }
    
    // mostrar os dados da criptomoeda
    struct Criptomoeda *cripto = &criptos[encontrado];
    printf("\nDados da criptomoeda:\n");
    printf("Nome: %s\n", cripto->nome);
    printf("Taxa de compra: %.2f\n", cripto->taxa_compra);
    printf("Taxa de venda: %.2f\n", cripto->taxa_venda);
    printf("Valor: R$ %.2f\n", cripto->valor);
    
    // confirmar exclusao
    char confirma;
    printf("\nTem certeza que deseja excluir esta criptomoeda? (s/n): ");
    if(scanf(" %c", &confirma) != 1) {
        printf("Erro ao ler confirmaçao. Tente novamente\n");
        clearBuffer();
    }
    if (confirma != 's' && confirma != 'S') {
        printf("Operacao cancelada. A moeda nao foi excluida\n");
        return;
    }

    // Remove a criptomoeda
    for (int i = encontrado; i < (*qtd_moedas) - 1; i++) {
        criptos[i] = criptos[i + 1];
    }
    (*qtd_moedas)--;

    // Atualiza o  arquivo de texto
    FILE *arquivo = fopen("criptomoedas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    for (int i = 0; i < *qtd_moedas; i++) {
        fprintf(arquivo, "%s,%.2f,%.2f,%.2f\n", criptos[i].nome, criptos[i].taxa_compra, criptos[i].taxa_venda, criptos[i].valor);
    }
    fclose(arquivo);

    printf("Criptomoeda excluida com sucesso.\n");
}

// função de adicionar investidor
void cadastrar_investidor(struct Investidores *investidor, int *qtd_investidor) {
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
    int cpf_valido, senha_valida = 0;

    while (!cpf_valido) {
        printf("Digite o CPF do investidor: ");
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

    // Checador de senha
        while (!senha_valida) {
        printf("Digite a senha do investidor: ");
        if(fgets(novo_investidor.senha, sizeof(novo_investidor.senha), stdin) == NULL) {
            printf("Erro ao ler senha, tente novamente.\n");
            continue;
        }
        novo_investidor.cpf[strcspn(novo_investidor.cpf, "\n")] = '\0';

        if (strlen(novo_investidor.senha) == 6) {
            senha_valida = 1;
        }
        else {
            printf("Erro! A senha deve ter 6 digitos.\n");
        }
        clearBuffer();
    }

    // Defs para o novo investidor
    novo_investidor.id = *qtd_investidor + 1;  

    // Incrementa o número de funcionários
    investidor[*qtd_investidor] = novo_investidor;
    (*qtd_investidor)++;
    invest_txt(novo_investidor);

    printf("Investidor cadastrado com sucesso! ID: %d\n", novo_investidor.id);
}

//txt de investdores
void invest_txt(struct Investidores investidor){
    FILE *inv = fopen("investidores.txt", "a");
    if (!inv) {
        printf("Erro ao abrir o arquivo de para armazenar investidores.\n");
        return;
    }
    
    fprintf(inv, "Nome: %s\n", investidor.nome);
    fprintf(inv, "CPF: %s\n", investidor.cpf);
    fprintf(inv, "Senha: %s\n", investidor.senha);

    fclose(inv);
}