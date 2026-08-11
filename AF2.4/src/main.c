#include <stdio.h>
#include "../include/stats.h"

int main(){
    adicionarValor(10.5);
    calcularMedia(20);

    printf("Média: %.2f\n", calcularMedia());
    return 0;
}