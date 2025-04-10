#include "Processo.h"

int main() {
    system("chcp 65001 > nul"); // Força UTF-8 no terminal. Coloquei para o código suportar acentos e tambémo ç, se necessário
    Processo *processos = NULL;
    const char *nome_arquivo = "processo_043_202409032338.csv";
    const char *cabecalho = "\"id\",\"numero\",\"data_ajuizamento\",\"id_classe\",\"id_assunto\",\"ano_eleicao\""; //Coloquei para depois aparecer no cabecalho dos csv que serão criados a partir da primeira e segunda questão.

    
    int quantidade_lidos = ler_processos(nome_arquivo, &processos);

    if (quantidade_lidos <= 0) {
        printf("Erro ao carregar os processos.\n");
        return 1;
    }
    
    printf("Foram carregados %d processos do arquivo.\n", quantidade_lidos);

    int opcao;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Imprimir todos os processos\n");
        printf("2. Ordenar por ID (crescente) e salvar\n");
        printf("3. Ordenar por data de ajuizamento (decrescente) e salvar\n");
        printf("4. Contar por ID Classe\n");
        printf("5. Contar assuntos\n");
        printf("6. Listar processos com múltiplos assuntos\n");
        printf("7. Dias em tramitação de um processo\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {

                imprimir_processos(processos, quantidade_lidos);
                break;
            }
            case 2: {

                ordenar_por_id(processos, quantidade_lidos);
                printf("Ordenado por ID (crescente).\n");
                salvar_csv("processos_ordenados_por_id.csv", processos, quantidade_lidos, cabecalho);
                printf("Dados salvos em 'processos_ordenados_por_id.csv'\n");
                break;
            }
            case 3: {
            
                ordenar_por_data(processos, quantidade_lidos);
                printf("Ordenado por data (decrescente).\n");
                salvar_csv("processos_ordenados_por_data.csv", processos, quantidade_lidos, cabecalho);
                printf("Dados salvos em 'processos_ordenados_por_data.csv'\n");
                break;
            }
            case 4: {

                int id;
                printf("Digite o ID da classe: ");
                scanf("%d", &id);
                int total = contar_por_id_classe(processos, quantidade_lidos, id);
                printf("Total de processos com ID de classe %d: %d\n", id, total);
                imprimir_por_id_classe(processos, quantidade_lidos, id);
                break;
            }
            case 5: {

                int total = contar_assuntos_unicos(processos, quantidade_lidos);
                printf("Total de assuntos: %d\n", total);
                imprimir_assuntos_unicos(processos, quantidade_lidos);
                break;
            }
            case 6: {

                listar_processos_com_multiplos_assuntos(processos, quantidade_lidos);
                break;
            }
            case 7: {

                int indice;
                printf("Digite o índice do processo (0 a %d): ", quantidade_lidos - 1);
                scanf("%d", &indice);
                
                if (indice >= 0 && indice < quantidade_lidos) {
                    int dias = calcular_dias_em_tramitacao(processos[indice].data_ajuizamento);
                    printf("Dias em tramitação do processo %d: %d dias\n", indice, dias);
                    printf("Detalhes do processo:\n");
                    imprimir_processo(processos[indice]);
                } else {
                    printf("Índice inválido!\n");
                }
                break;
            }
            case 0: {

                printf("Encerrando o programa...\n");
                break;
            }
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    free(processos); //Coloquei para liberar a memória que foi alocada dinamicamente pelas outras funções (malloc, calloc, etc)
    return 0;
}
