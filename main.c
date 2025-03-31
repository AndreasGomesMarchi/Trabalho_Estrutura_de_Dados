#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Processo.h"

int main(){
    Processo processos[MAX_PROCESSOS];

    int total = Ler_processos("processo_043_202409032338.csv", processos, MAX_PROCESSOS);
    if (total == -1) {
        return 1;
    }




    return 0;
}