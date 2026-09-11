#include <stdio.h>
#include "programa_refatorado.h"





int main(){
    printf("============ SOMAR PARES POSITIVOS =============\n");

    int valores[] = {-3, 4, 7, 8, -1, 10, 2, 15};
    int tamanho = sizeof(valores) / sizeof(valores[0]);

    int resultado = somarParesPositivos(valores, tamanho);
    printf("Soma dos pares positivos: %d\n", resultado);

    printf("Positivos até 10: ");
    int contagem = listarPositivosAteLimite(valores, tamanho, 10);
    printf("Contagem: %d\n", contagem);

    return 0;
}