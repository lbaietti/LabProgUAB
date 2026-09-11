#include <stdio.h>
#include <stdbool.h> /* !!! Inclusão da lib apropriada. Caso não inclua, dará erro tanto na interface quanto na implementação */

#include "programa_refatorado.h"

// Funções bool com a parte lógica, tendo assim responsabilidades únicas.
bool ehPar(int valor){
    return valor % 2 == 0;
}

bool ehPositivo(int valor){
    return valor > 0;
}

static int somar_pares(const int valores[], int tamanho){
    int soma = 0;

    for(int i = 0; i < tamanho; i++){
        int v = valores[i]; 

        // Zero é par, mas a especificação exige positivos - exclusão intencional
        if(ehPar(v) && ehPositivo(v)){
            soma += v;
        }
    }
    return soma;
}

static int listarPositivosAteLimite(const int valores[], int tamanho, int limite){
    if(valores == NULL || tamanho <= 0) return 0;

    int contagem = 0;
    for(int i = 0; i < tamanho; i++){
        int v = valores[i];

        if(ehPositivo(v) && v <= limite){
            printf("%d", v);
            contagem++;
        }
    }
    return contagem;
}


/**
 * @note
 * O código poderia ser monolítico, no entanto optei por fazê-lo de forma modular, para se praticar os conceitos apreendidos.
 */