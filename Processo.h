//Aqui tem um cabeçalho onde tem as structs, difinir tipo, cabeçaho das informações, etc
#ifndef PROCESSO_H
#define PROCESSO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PROCESSOS 1000

typedef struct Processo{
    int id;
    char numero[20];
    char data_ajuizamento[50];
    int id_classe;
    int id_assunto[10];
    int num_assuntos;
    int ano_eleicao;
}Processo;

int Ler_processos(const char *nome_arquivo, Processo processos[], int max_processos);

//Parte artur
void ordenar_por_id(Processo processos[], int quantidade);
void ordenar_por_data(Processo processos[], int quantidade);

//Parte Breno
char IdClasseDesejado[20] = "12377";
int contarPorIdClasse(Processo processos[], int n, const char *idClasse);
int contarIdAssuntosUnicos(Processo processos[], int n);

//Parte David
void listar_processos_com_multiplos_assuntos(Processo processos[], int n);
int calcular_dias_em_tramitacao(const char *data_ajuizamento);


#endif
