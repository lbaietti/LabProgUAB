#include <stdio.h>
#include "../include/stats.h"

static int contador = 0, soma = 0.0f;

void adicionarValor(float valor){
    contador++;
    soma += valor; 
}

float calcularMedia(){
    if(contador == 0) return 0.0f; // Tratamento de caso especial
    
    return soma / contador;
}
