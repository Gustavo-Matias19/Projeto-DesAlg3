#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#include "inv_trade.h"
#include "adm_trade.h"
#include "cadastro.h"
#include "funcoes.h"

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
        printf("Digite a taxa de compra (porcentagem): ");
        if (scanf("%f", &nova_cripto.taxa_compra) != 1) {
            printf("Erro ao ler taxa de compra do produto, tente novamente!\n");
            clearBuffer(); 
            continue;
        }
        getchar();
    } while (nova_cripto.taxa_compra <= 0);
    
    // Taxa de venda
    do {
        printf("Digite a taxa de venda (porcentagem): ");
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

    criptos_txt(criptos, *qtd_moedas);
    printf("Criptomoeda cadastrada com sucesso!\n");
}

// txt das criptos
void criptos_txt(struct Criptomoeda *criptos, int qtd_moedas){
    FILE *arquivo = fopen("criptomoedas.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de criptomoedas.\n");
        return;
    }
    
    int i;
    for (i = 0; i < qtd_moedas; i++){ 
        fprintf(arquivo, "Nome: %s\n", criptos[i].nome);
        fprintf(arquivo, "Taxa de Compra: %.2f\n", criptos[i].taxa_compra);
        fprintf(arquivo, "Taxa de Venda: %.2f\n", criptos[i].taxa_venda);
        fprintf(arquivo, "Cotacao: %.2f\n", criptos[i].valor);
        fprintf(arquivo, "--------\n");
    }
    fclose(arquivo);
}

int ler_criptos_txt(struct Criptomoeda *criptos, int *qtd_moedas){
    FILE *arquivo = fopen("criptomoedas.txt", "r");
    if (!arquivo) {
        printf("Nenhuma criptomoeda encontrada. Criando um novo arquivo.\n");
        *qtd_moedas = 0;
        return 0;
    }

    *qtd_moedas = 0;
    char linha[256];
    struct Criptomoeda temp;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strncmp(linha, "Nome: ", 6) == 0) {
            sscanf(linha, "Nome: %49[^\n]", temp.nome);
        } else if (strncmp(linha, "Taxa de Compra: ", 16) == 0) {
            sscanf(linha, "Taxa de Compra: %f", &temp.taxa_compra);
        } else if (strncmp(linha, "Taxa de Venda: ", 15) == 0) {
            sscanf(linha, "Taxa de Venda: %f", &temp.taxa_venda);
        } else if (strncmp(linha, "Cotacao: ", 9) == 0) {
            sscanf(linha, "Cotacao: %f", &temp.valor);
        } else if (strncmp(linha, "--------", 8) == 0) {
            criptos[*qtd_moedas] = temp;
            // Remover espaços ou quebras de linha
            temp.nome[strcspn(temp.nome, "\r\n")] = '\0';
            (*qtd_moedas)++;
        }
    }

    fclose(arquivo);
    return *qtd_moedas;
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
    printf("--- Criptomoedas no Banco de Dados ---\n");
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
    int encontrado = -1;
    for (i = 0; i < *qtd_moedas; i++) {
        if (strcmp(criptos[i].nome, cripto_procurada) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1) {
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
    if(scanf("%c", &confirma) != 1) {
        printf("Erro ao ler confirmaçao. Tente novamente\n");
        clearBuffer();
    }
    if (confirma != 's' && confirma != 'S') {
        printf("Operacao cancelada. A moeda nao foi excluida\n");
        return;
    }

    // Remove a criptomoeda
    for (i = encontrado; i < (*qtd_moedas) - 1; i++) {
        criptos[i] = criptos[i + 1];
    }
    (*qtd_moedas)--;

    //Atualiza o txt
    criptos_txt(criptos, *qtd_moedas);

    printf("Criptomoeda excluida com sucesso.\n");
}

// função de adicionar investidor
void cadastrar_investidor(struct Investidores *investidor, int *qtd_investidor) {
    struct Investidores novo_investidor;
    
    // Nome do investidor
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


    // Incrementa o número de investidores
    novo_investidor.saldo = 0.0;
    investidor[*qtd_investidor] = novo_investidor;
    (*qtd_investidor)++;
    invest_txt(investidor, *qtd_investidor);

    printf("Investidor cadastrado com sucesso!\n");
}

//txt de investdores
void invest_txt(struct Investidores *investidor, int qtd_investidor){
    FILE *inv = fopen("investidores.txt", "w");
    if (!inv) {
        printf("Erro ao abrir o arquivo de para armazenar investidores.\n");
        return;
    }
    int i;
    for(i = 0; i < qtd_investidor; i++){
        fprintf(inv, "Nome: %s\n", investidor[i].nome);
        fprintf(inv, "CPF: %s\n", investidor[i].cpf);
        fprintf(inv, "Senha: %s\n", investidor[i].senha);
        fprintf(inv, "--------\n");
    }
    fclose(inv);
}
int ler_invest_txt(struct Investidores *investidor, int *qtd_investidor) {
    FILE *inv = fopen("investidores.txt", "r");
    if (!inv) {
        printf("Nenhum investidor encontrado. Criando um novo arquivo.\n");
        *qtd_investidor = 0; // Sem registros carregados
        return 0;
    }

    *qtd_investidor = 0;
    char linha[256];
    struct Investidores temp;

    while (fgets(linha, sizeof(linha), inv)) {
        if (strncmp(linha, "Nome: ", 6) == 0) {
            sscanf(linha, "Nome: %49[^\n]", temp.nome);
        } else if (strncmp(linha, "CPF: ", 5) == 0) {
            sscanf(linha, "CPF: %11[^\n]", temp.cpf);
        } else if (strncmp(linha, "Senha: ", 7) == 0) {
            sscanf(linha, "Senha: %6[^\n]", temp.senha);
        } else if (strncmp(linha, "Saldo: ", 7) == 0) {
            sscanf(linha, "Saldo: %f", &temp.saldo);
        } else if (strncmp(linha, "--------", 8) == 0) {
            // Remover espaços ou quebras de linha
            temp.cpf[strcspn(temp.cpf, "\r\n")] = '\0';
            temp.senha[strcspn(temp.senha, "\r\n")] = '\0';
            investidor[*qtd_investidor] = temp;
            (*qtd_investidor)++;
        }
    }
    fclose(inv);
    return *qtd_investidor;
}

void remover_investidor(struct Investidores *investidor, int *qtd_investidor) {
    if (*qtd_investidor == 0) {
        printf("Nao ha nenhum investidor no banco de dados, adicione algum e volte aqui!.\n");
        return;
    }

    //Mostra os investidores disponiveis
    int i;
    char investidor_procurado[MAX_DIGITOS];
    printf("--- Investidores no Banco de Dados ---\n");
    for(i = 0; i < *qtd_investidor; i++){
        printf("Nome: %s\n", investidor[i].nome);
        printf("CPF: %s\n", investidor[i].cpf);
        printf("Senha: %s\n", investidor[i].senha);

    }
    printf("\nEscolha o investidor para remover: ");
    if (fgets(investidor_procurado, MAX_DIGITOS, stdin) == NULL) {
        printf("Erro ao ler o nome, tente novamente.\n");
        return;
    }
    investidor_procurado[strcspn(investidor_procurado, "\n")] = '\0';
    
    // Procura o investidor pelo nome
    int encontrado = -1;
    for (i = 0; i < *qtd_investidor; i++) {
        if (strcmp(investidor[i].nome, investidor_procurado) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1) {
        printf("Investidor nao encontrado.\n");
        return;
    }
    
    // mostrar os dados dos investidores
    struct Investidores *investidores = &investidor[encontrado];
    printf("\nDados do investidor:\n");
    printf("Nome: %s\n", investidores->nome);
    printf("CPF: %s\n", investidores->cpf);
    printf("Senha: %s\n", investidores->senha);

    
    // confirmar exclusao
    char confirma;
    printf("\nTem certeza que deseja excluir esta investidor? (s/n): ");
    if(scanf(" %c", &confirma) != 1) {
        printf("Erro ao ler confirmacao. Tente novamente\n");
        clearBuffer();
    }
    if (confirma != 's' && confirma != 'S') {
        printf("Operacao cancelada. A conta nao foi excluida\n");
        return;
    }

    // Remove o investidor
    for (i = encontrado; i < (*qtd_investidor) - 1; i++) {
        investidor[i] = investidor[i + 1];
    }
    (*qtd_investidor)--;

    // Atualiza o arquivo de texto
    invest_txt(investidor, *qtd_investidor);

    printf("Investidor excluido com sucesso.\n");
}

// atualizar cotação
void atualizar_cotacao(struct Criptomoeda *criptos, int *qtd_moedas) {
    if (*qtd_moedas == 0) {
        printf("Nao ha nenhuma criptomoeda no banco de dados, adicione algum e volte aqui!.\n");
        return;
    }

    //Mostra as criptomoedas disponiveis
    int i;
    char cripto_procurada[MAX_DIGITOS];
    printf("--- Criptomoedas no Banco de Dados ---\n");
    for(i = 0; i < *qtd_moedas; i++){
        printf("Nome: %s\n", criptos[i].nome);
        printf("Taxa de compra: %.2f\n", criptos[i].taxa_compra);
        printf("Taxa de venda: %.2f\n", criptos[i].taxa_venda);
        printf("Cotacao: %.2f\n", criptos[i].valor);
    }
    printf("\nEscolha a criptomoeda para atualizar a cotacao: ");
    if (fgets(cripto_procurada, MAX_DIGITOS, stdin) == NULL) {
        printf("Erro ao ler o nome, tente novamente.\n");
        return;
    }
    cripto_procurada[strcspn(cripto_procurada, "\n")] = '\0';
    
    // Procura a criptomoeda pelo nome
    int encontrado = -1;
    for (i = 0; i < *qtd_moedas; i++) {
        if (strcmp(criptos[i].nome, cripto_procurada) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1) {
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

    // Solicita o novo valor da cotação
    float nova_cotacao;
    do {
        printf("Digite o novo valor da cotacao para %s: ", criptos[encontrado].nome);
        if (scanf("%f", &nova_cotacao) != 1 || nova_cotacao <= 0) {
            printf("Valor invalido. Tente novamente.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();
        break;
    } while (1);

    // Atualiza a cotação
    criptos[encontrado].valor = nova_cotacao;

    // Atualiza o txt
    criptos_txt(criptos, *qtd_moedas);
    printf("Cotacao da %s atualizada com sucesso.\n", criptos->nome);
}

// função para consultar saldo dos investidores
void consultar_saldo_invest(struct Investidores *investidor, int *qtd_investidor){
    if (qtd_investidor == 0) {
        printf("Nao existem investidores cadastrados no sistema.\n");
        return;
    }
    
    //Mostra os investidores disponiveis
    int i;
    char cpf_procurado[MAX_DIGITOS];
    printf("--- Investidores no Banco de Dados ---\n");
    for(i = 0; i < *qtd_investidor; i++){
        printf("Nome: %s\n", investidor[i].nome);
        printf("CPF: %s\n", investidor[i].cpf);
        printf("Senha: %s\n", investidor[i].senha);

    }
    printf("\nDigite o CPF investidor para consulta: ");
    if (fgets(cpf_procurado, MAX_DIGITOS, stdin) == NULL) {
        printf("Erro ao ler o nome, tente novamente.\n");
        return;
    }
    cpf_procurado[strcspn(cpf_procurado, "\n")] = '\0';
    
    // Procura o investidor pelo nome
    int encontrado = -1;
    for (i = 0; i < *qtd_investidor; i++) {
        if (strcmp(investidor[i].cpf, cpf_procurado) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1) {
        printf("Investidor nao encontrado.\n");
        return;
    }
    
    // mostrar os dados dos investidores
    struct Investidores *investidores = &investidor[encontrado];
    printf("\nDados do investidor:\n");
    printf("Nome: %s\n", investidores->nome);
    printf("CPF: %s\n", investidores->cpf);
    printf("Saldo: %.2f\n", investidores->saldo);
}
