#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Processo.h"

int Ler_processos(const char *nome_arquivo, Processo processos[], int max_processos) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    
    if (!arquivo) {
        printf("Erro ao abrir o arquivo\n");
        return -1;
    }

    char linha[200];
    int i = 0;

    fgets(linha, sizeof(linha), arquivo);

    while (i < max_processos && fgets(linha, sizeof(linha), arquivo)) {
        Processo p;
        char assuntos[200];  

        if (linha[0] == '\0' || linha[0] == '\n') {
            continue;  
        }

        int n = sscanf(linha, "%d,\"%[^\"]\",%[^,],{%[^}]} ,%d", &p.id, p.numero, p.data_ajuizamento, assuntos, &p.ano_eleicao);

        printf("%s", linha);

        p.num_assuntos = 0;

        char *pedaco = strtok(assuntos, ",");
        while (pedaco) {
            if (p.num_assuntos < 10) {  
                p.id_assunto[p.num_assuntos++] = atoi(pedaco);
            }
            pedaco = strtok(NULL, ",");
        }

        processos[i++] = p;
    }

    fclose(arquivo);
    return i;
}
