#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cadastro.h"
#include "funcoes.h"
#include "adm_trade.h"
#include "inv_trade.h"

// cadastro adm
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


// função para login dos investidores
int login_invest(struct Investidores *investidor, int qtd_investidor, struct Investidores *investidor_logado){
    char cpf_login[12];
    char senha_login[7];

    printf("Digite seu CPF: ");
    if (fgets(cpf_login, sizeof(cpf_login), stdin) == NULL){
        printf("Erro ao ler cpf do investidor, tente novamente.\n");
        return 0;
    }
    cpf_login[strcspn(cpf_login, "\n")] = '\0';

    printf("Digite sua senha: ");
    if(fgets(senha_login, sizeof(senha_login), stdin) == NULL){
        printf("Erro ao ler senha tente novamente.\n");
        return 0;
    }
    senha_login[strcspn(senha_login, "\n")] = '\0';

    clearBuffer();

    int i;
    for (i = 0; i < qtd_investidor; i++) {
        if (strcmp(investidor->cpf, cpf_login) == 0 && strcmp(investidor->senha, senha_login) == 0) {
            *investidor_logado = *investidor;
            printf("Login bem-sucedido. Bem-vindo, %s!\n", investidor->nome);
            break;
        }
    }
}