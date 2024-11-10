#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastro.h"
#include "funcoes.h"

// cadastro adm
void cadastro_adm(struct Login_adm *login) {
    
    printf("Digite seu CPF: ");
    if(fgets(login->cpf, sizeof(login->cpf), stdin) == NULL) {
        printf("Erro ao ler nome da login.\n");
        return;
    }
    login->cpf[strcspn(login->cpf, "\n")] = '\0';
    
    int senhaValida = 0;

    while (!senhaValida) {
        printf("Digite uma senha de 6 digitos: ");
        if(fgets(login->senha, sizeof(login->senha), stdin) == NULL){
            printf("Erro ao ler senha, tente novamente.\n");
            return;
        }
        login->senha[strcspn(login->senha, "\n")] = '\0';

        if (strlen(login->senha) == 6) {
            senhaValida = 1;
        } 
        else {
            printf("A senha deve ter exatamente 6 digitos.\n");
        }
        clearBuffer();
    }
    printf("Cadastro realizado com sucesso!\n\n");
}

int login(struct Login_adm *login) {
    char cpf[50];
    char senha_login[7];

    printf("--- Login ---\n");
    printf("Digite o nome da login: ");
    if (fgets(cpf, sizeof(cpf), stdin) == NULL){
        printf("Erro ao ler nome da login, tente novamente.\n");
        return 0;
    }
    cpf[strcspn(cpf, "\n")] = '\0';

    printf("Digite a senha: ");
    if(fgets(senha_login, sizeof(senha_login), stdin) == NULL){
        printf("Erro ao ler senha, tente novamente.\n");
        return 0;
    }
    senha_login[strcspn(senha_login, "\n")] = '\0';

    clearBuffer();

    if (strcmp(login->cpf, cpf) == 0 && strcmp(login->senha, senha_login) == 0) {
        printf("Login realizado com sucesso!\n");
        return 1;
    } else {
        printf("Nome e/ou senha incorretos. Tente novamente.\n");
        return 0;
    }
}