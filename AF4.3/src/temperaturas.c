#include "../include/temperaturas.h"
#include <stdio.h>

int registar_temperatura(float *lista, int capacidade, int indice, float valor) {
    if (lista == NULL || capacidade <= 0 || indice < 0 || indice >= capacidade)
        return 0;
    lista[indice] = valor;
    return 1;
}

int media_temperaturas(float *lista, int n, float *resultado) {
    if (lista == NULL || n <= 0 || resultado == NULL)
        return 0;
    float soma = 0;
    for (int i = 0; i < n; i++)
        soma += lista[i];
    *resultado = soma / n; /* ERRO: resultado pode ser NULL — comportamento indefinido */
    return 1;
}
