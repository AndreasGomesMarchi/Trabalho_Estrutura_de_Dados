#include "Processo.h"

int ler_processos(const char *nome_arquivo, Processo **processos) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n"); //Coloquei mais por garantia. Isso não deve aparecer. eu espero que não
        return 0;
    }

    char linha[512];
    int capacidade = 100;
    int i = 0;
    *processos = malloc(capacidade * sizeof(Processo));

    fgets(linha, sizeof(linha), arquivo); // Pula cabeçalho

    while (fgets(linha, sizeof(linha), arquivo)) {

        if (i >= capacidade) {
            capacidade *= 2;
            *processos = realloc(*processos, capacidade * sizeof(Processo));
        }

        Processo p;
        p.num_assuntos = 0;
        
        linha[strcspn(linha, "\r\n")] = 0; // Remover possíveis quebras de linha. Se não buga também
        
        // Variáveis temporárias para armazenar os campos
        char id_str[20];
        char numero[30];
        char data[50];
        char id_classe_str[20];
        char assuntos_str[100];
        char ano_str[20];
        
        // Inicializar campos
        id_str[0] = '\0';
        numero[0] = '\0';
        data[0] = '\0';
        id_classe_str[0] = '\0';
        assuntos_str[0] = '\0';
        ano_str[0] = '\0';
        
        // Ler cada linha sem erro, aqui ler os processos com a escrita "normal"
        int lidos = sscanf(linha, "%[^,],\"%[^\"]\",%""[^,],{%[^}]},{%[^}]%*c,%[^\n]", id_str, numero, data, id_classe_str, assuntos_str, ano_str);
        
        // Ler as linhas que possuem id_classe ou id_assunto diferente, se não da erro kkkkk
        if (lidos != 6) {
            lidos = sscanf(linha, "%[^,],\"%[^\"]\",%""[^,],{%[^}]},\"{%[^}]}\"%*c,%[^\n]",id_str, numero, data, id_classe_str, assuntos_str, ano_str);
        }
        
        // Converter os campos para os tipos apropriados
        p.id = atoi(id_str); //O atoi serve para converter os numeros que estão na string em inteiros, facilitando o resto do processo
        strncpy(p.numero, numero, sizeof(p.numero) - 1); //copiar um número específico de caracteres de uma string para outra. fácil de entender
        p.numero[sizeof(p.numero) - 1] = '\0';
        
        strncpy(p.data_ajuizamento, data, sizeof(p.data_ajuizamento) - 1);
        p.data_ajuizamento[sizeof(p.data_ajuizamento) - 1] = '\0';
        
        p.id_classe = atoi(id_classe_str);
        p.ano_eleicao = atoi(ano_str);
        
        // Processar os assuntos (que podem ser múltiplos)
        char *token = strtok(assuntos_str, ","); //O strtok serve para quebrar uma string em partes menores, também chamadas tokens. Por isso o nome de varios tokens nessa parte kkkkk
        while (token != NULL && p.num_assuntos < MAX_ASSUNTOS) {
            p.id_assunto[p.num_assuntos++] = atoi(token);
            token = strtok(NULL, ",");
        }
        
        (*processos)[i++] = p;
    }

    fclose(arquivo);
    return i;
}

void imprimir_processo(Processo p) {
    printf("ID: %d\n", p.id);
    printf("Numero: %s\n", p.numero);
    printf("Data: %s\n", p.data_ajuizamento);
    printf("Classe: %d\n", p.id_classe);
    printf("Assuntos (%d): ", p.num_assuntos);
    for (int j = 0; j < p.num_assuntos; j++) {
        printf("%d ", p.id_assunto[j]);
    }
    printf("\nAno Eleição: %d\n", p.ano_eleicao);
    printf("-----------------------------\n");
}

void imprimir_processos(Processo processos[], int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        imprimir_processo(processos[i]);
    }
}

void ordenar_por_id(Processo processos[], int quantidade) { //De modo ccrescente, como pedido. 1 questão do oque deve ser feito
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

void ordenar_por_data(Processo processos[], int quantidade) { //De modo decrescente, como pedido. 2 questão de oque deve ser feito
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

int contar_por_id_classe(Processo processos[], int n, int id_classe) { //3 questão do que deve ser feito
    int count = 0;

    for (int i = 0; i < n; i++) {

        if (processos[i].id_classe == id_classe) {
            count++;
        }
    }
    return count;
}

void imprimir_por_id_classe(Processo processos[], int n, int id_classe) { 
    printf("Processos com ID de classe %d:\n", id_classe);

    for (int i = 0; i < n; i++) {

        if (processos[i].id_classe == id_classe) {
            imprimir_processo(processos[i]);
        }
    }
}

int contar_assuntos_unicos(Processo processos[], int n) { //4 questão do oque deve ser feito
    int unicos[100] = {0};
    int total = 0;

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < processos[i].num_assuntos; j++) {
            int atual = processos[i].id_assunto[j];
            int existe = 0;

            for (int k = 0; k < total; k++) {
                if (unicos[k] == atual) {
                    existe = 1;
                    break;
                }
            }

            if (!existe) {
                unicos[total++] = atual;
            }
        }
    }
    return total;
}

void imprimir_assuntos_unicos(Processo processos[], int n) {
    int unicos[100] = {0};
    int total = 0;

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < processos[i].num_assuntos; j++) {
            int atual = processos[i].id_assunto[j];
            int existe = 0;

            for (int k = 0; k < total; k++) {
                if (unicos[k] == atual) {
                    existe = 1;
                    break;
                }
            }

            if (!existe) {
                unicos[total++] = atual;
            }
        }
    }
    
    printf("Assuntos únicos (%d): ", total);

    for (int i = 0; i < total; i++) {
        printf("%d ", unicos[i]);
    }

    printf("\n");
}

void listar_processos_com_multiplos_assuntos(Processo processos[], int n) { //5 questão do qoue deve ser feito
    int encontrou = 0;
    
    printf("Processos com múltiplos assuntos:\n");
    for (int i = 0; i < n; i++) {

        if (processos[i].num_assuntos > 1) {
            imprimir_processo(processos[i]);
            encontrou = 1;
        }
    }
    
    if (!encontrou) {
        printf("Nenhum processo com múltiplos assuntos encontrado.\n"); //Coloquei mais por garantia. Isso não deve aparecer. eu espero que não
    }
}

int calcular_dias_em_tramitacao(const char *data_ajuizamento) { //6 questão da tramitação. Todas as questões foram colocadas
    struct tm tm_ajuizamento = {0};
    int ano, mes, dia, hora, minuto, segundo;
    
    sscanf(data_ajuizamento, "%d-%d-%d %d:%d:%d",&ano, &mes, &dia, &hora, &minuto, &segundo); //Colocado para seguir o formato certinho do csv

    tm_ajuizamento.tm_year = ano - 1900;
    tm_ajuizamento.tm_mon = mes - 1;
    tm_ajuizamento.tm_mday = dia;
    tm_ajuizamento.tm_hour = hora;
    tm_ajuizamento.tm_min = minuto;
    tm_ajuizamento.tm_sec = segundo;

    time_t data_proc = mktime(&tm_ajuizamento);
    time_t agora = time(NULL);
    double diff = difftime(agora, data_proc);
    return (int)(diff / (60 * 60 * 24));
}

int salvar_csv(const char *nome_arquivo, Processo processos[], int quantidade, const char *cabecalho) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (!arquivo) {
        printf("Erro ao criar o arquivo %s.\n", nome_arquivo); //Coloquei mais por garantia. Isso não deve aparecer. eu espero que não
        return 0;
    }
    
    fprintf(arquivo, "%s\n", cabecalho); // Escrever o cabeçalho. aquele cabeçalho no main.c serve agora aqui. Tentei colocar no processo.h, mas deu erro. Então deixei no main
    
    for (int i = 0; i < quantidade; i++) { // Escrever os dados de cada processo
        char assuntos[200];

        if (processos[i].num_assuntos > 1){ // Múltiplos assuntos - usar o formato com aspas extras - Como esse deu dor de cabeça
            sprintf(assuntos, "\"{");

            for (int j = 0; j < processos[i].num_assuntos; j++) {
                char temp[20];
                sprintf(temp, "%d", processos[i].id_assunto[j]);
                strcat(assuntos, temp);

                if (j < processos[i].num_assuntos - 1) {
                    strcat(assuntos, ",");
                }
            }

            strcat(assuntos, "}\"");

        } else{
            sprintf(assuntos, "{%d}", processos[i].id_assunto[0]); // Único assunto - formato normal
        }
        
        fprintf(arquivo, "%d,\"%s\",%s,{%d},%s,%d\n", 
                processos[i].id, 
                processos[i].numero, 
                processos[i].data_ajuizamento, 
                processos[i].id_classe, 
                assuntos, 
                processos[i].ano_eleicao);
    }
    
    fclose(arquivo);
    return 1;
}
