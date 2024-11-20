#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void registrarExtrato(const char *operacao, float valor, const char *detalhes) {
    FILE *file = fopen("extrato.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de extrato.\n");
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(file, "%02d-%02d-%d %02d:%02d:%02d - Operacao: %s | Valor: R$ %.2f | Detalhes: %s\n",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec,
            operacao, valor, detalhes);

    fclose(file);
}


void consultarExtrato() {
    FILE *file = fopen("extrato.txt", "r");
    if (file == NULL) {
        printf("Nao ha transacoes registradas.\n");
        return;
    }

    char linha[256];
    printf("\n--- Extrato de Transacoes ---\n");
    while (fgets(linha, sizeof(linha), file)) {
        printf("%s", linha);
    }
    fclose(file);
}