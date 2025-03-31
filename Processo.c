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

    // Lê a primeira linha (cabeçalho), se houver
    fgets(linha, sizeof(linha), arquivo);

    while (i < max_processos && fgets(linha, sizeof(linha), arquivo)) {
        Processo p;
        char assuntos[200];  // Aumentei o tamanho para suportar mais assuntos

        // Verificar se a linha é válida (não vazia ou com erro)
        if (linha[0] == '\0' || linha[0] == '\n') {
            continue;  // Se a linha for vazia, pula para a próxima
        }

        // Usando sscanf para ler os campos corretamente, ajustando para variabilidade
        int n = sscanf(linha, "%d,\"%[^\"]\",%[^,],{%[^}]} ,%d", &p.id, p.numero, p.data_ajuizamento, assuntos, &p.ano_eleicao);

        printf("%s", linha);

        // Inicializa a contagem de assuntos
        p.num_assuntos = 0;

        // Usa strtok para separar os múltiplos valores dentro das chaves
        char *pedaco = strtok(assuntos, ",");
        while (pedaco) {
            if (p.num_assuntos < 10) {  // Limite de 10 assuntos
                p.id_assunto[p.num_assuntos++] = atoi(pedaco);
            }
            pedaco = strtok(NULL, ",");
        }

        // Armazena o processo no vetor
        processos[i++] = p;
    }

    fclose(arquivo);
    return i;
}
