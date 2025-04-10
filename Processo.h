#ifndef PROCESSO_H
#define PROCESSO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ASSUNTOS 10

typedef struct Processo {
    int id;
    char numero[20];
    char data_ajuizamento[100];
    int id_classe;
    int id_assunto[MAX_ASSUNTOS];
    int num_assuntos;
    int ano_eleicao;
} Processo;

int ler_processos(const char *nome_arquivo, Processo **processos);
void imprimir_processos(Processo processos[], int quantidade);
void ordenar_por_id(Processo processos[], int quantidade);
void ordenar_por_data(Processo processos[], int quantidade);
int contar_por_id_classe(Processo processos[], int n, int id_classe);
void imprimir_por_id_classe(Processo processos[], int n, int id_classe);
int contar_assuntos_unicos(Processo processos[], int n);
void imprimir_assuntos_unicos(Processo processos[], int n);
void listar_processos_com_multiplos_assuntos(Processo processos[], int n);
int calcular_dias_em_tramitacao(const char *data_ajuizamento);
void imprimir_processo(Processo p);
int salvar_csv(const char *nome_arquivo, Processo processos[], int quantidade, const char *cabecalho);

#endif
