#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Processo.h"

//Minha parte
int Ler_processos(const char *nome_arquivo, Processo processos[], int max_processos) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    char linha[200];
    int i = 0;
    fgets(linha, sizeof(linha), arquivo); 

    while (i < max_processos && fgets(linha, sizeof(linha), arquivo)) {
        Processo p;
        char assuntos[50];

        sscanf(linha, "%d,\"%[^\"]\",%[^,],{%d},{%[^}]},%d", &p.id, p.numero, p.data_ajuizamento, &p.id_classe, assuntos, &p.ano_eleicao);
        p.num_assuntos = 0;
        
        char *pedaco = strtok(assuntos, ",");
        while (pedaco) {
            p.id_assunto[p.num_assuntos++] = atoi(pedaco);
            pedaco = strtok(NULL, ",");
        }

        processos[i++] = p;
    }

    fclose(arquivo);
    return i;
}

//Parte Artur 
void ordenar_por_id(Processo processos[], int quantidade) {
    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = 0; j < quantidade - i - 1; j++) {
            if (processos[j].id > processos[j + 1].id) {
                Processo temp = processos[j];
                processos[j] = processos[j + 1];
                processos[j + 1] = temp;
            }
        }
    }
}

void ordenar_por_data(Processo processos[], int quantidade) {
    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = 0; j < quantidade - i - 1; j++) {
            if (strcmp(processos[j].data_ajuizamento, processos[j + 1].data_ajuizamento) < 0) {
                Processo temp = processos[j];
                processos[j] = processos[j + 1];
                processos[j + 1] = temp;
            }
        }
    }
}

//Parte Brenno
int contarPorIdClasse(Processo processos[], int n, const char *idClasse) {
    int count = 0;
    for (int i = 0; i < n; i++){
        if (strcmp(processos[i].id_classe, idClasse) == 0) {
            count++;
        }
    }
    return count;
}

int contarIdAssuntosUnicos(Processo processos[], int n) {
    char assuntos[100][20]; 
    int total = 0;
    
    for (int i = 0; i < n; i++){
        int existe = 0;
        for (int j = 0; j < total; j++){
            if (strcmp(processos[i].id_assunto, assuntos[j]) == 0) {
                existe = 1;
                break;
            }
        }
        if (!existe) {
            strcpy(assuntos[total], processos[i].id_assunto);
            total++;
        }
    }
    return total;
}

//Parte David
void listar_processos_com_multiplos_assuntos(Processo processos[], int n) {
    for (int i = 0; i < n; i++) {
        if (processos[i].num_assuntos > 1) {
            printf("Processo ID: %d, Número: %s, Assuntos: ", processos[i].id, processos[i].numero);
            for (int j = 0; j < processos[i].num_assuntos; j++) {
                printf("%d ", processos[i].id_assunto[j]);
            }
            printf("\n");
        }
    }
}


int calcular_dias_em_tramitacao(const char *data_ajuizamento) {
    // Obtém a data atual
    time_t t = time(NULL);
    struct tm tm_atual = *localtime(&t);
    
    // Converte a data de ajuizamento para um struct tm
    struct tm tm_ajuizamento = {0};
    sscanf(data_ajuizamento, "%d-%d-%d", &tm_ajuizamento.tm_year, &tm_ajuizamento.tm_mon, &tm_ajuizamento.tm_mday);
    tm_ajuizamento.tm_year -= 1900; // O ano é contado a partir de 1900
    tm_ajuizamento.tm_mon -= 1; // O mês é contado de 0 a 11
    
    // Converte as datas para time_t para fazer a diferença
    time_t t_ajuizamento = mktime(&tm_ajuizamento);
    
    // Calcula a diferença em segundos
    double dif_segundos = difftime(t, t_ajuizamento);
    
    // Converte para dias
    int dias = dif_segundos / (60 * 60 * 24);
    
    return dias;
}
