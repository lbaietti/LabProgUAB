/*
 * Programa para calcular a soma dos números pares positivos de um array
 * e listar os valores positivos abaixo de um limite definido.
 *
 * Versão refatorada a partir de código original com más práticas:
 * - Nomes crípticos (p, f, a, n, s, c, lim)
 * - Aninhamento excessivo de if's
 * - Funções monolíticas com múltiplas responsabilidades
 * - Ausência de validação e comentários significativos
 */

#include <stdio.h>
#include <stdbool.h>

/**
 * Verifica se um número inteiro é par.
 */
bool ehPar(int valor) {
    return valor % 2 == 0;
}

/**
 * Verifica se um número inteiro é positivo (exclui zero).
 */
bool ehPositivo(int valor) {
    return valor > 0;
}

/**
 * Calcula a soma dos números pares e positivos de um array.
 */
int somarParesPositivos(const int valores[], int tamanho) {
    if (valores == NULL || tamanho <= 0) return 0;

    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        int v = valores[i];
        // Zero é par, mas a especificação exige positivos — exclusão intencional
        if (ehPositivo(v) && ehPar(v)) {
            soma += v;
        }
    }
    return soma;
}

/**
 * Imprime os valores positivos do array abaixo de um limite.
 * Retorna o número de valores impressos.
 */
int listarPositivosAteLimite (const int valores[], int tamanho, int limite) {
    if (valores == NULL || tamanho <= 0) return 0;

    int contagem = 0;
    for (int i = 0; i < tamanho; i++) {
        int v = valores[i];
        if (ehPositivo(v) && v <= limite) {
            printf("%d ", v);
            contagem++;
        }
    }
    return contagem;
}

int main() {
    int valores[] = {-3, 4, 7, 8, -1, 10, 2, 15};
    int tamanho = sizeof(valores) / sizeof(valores[0]);

    int resultado = somarParesPositivos(valores, tamanho);
    printf("Soma dos pares positivos: %d\n", resultado);

    printf("Positivos até 10: ");
    int contagem = listarPositivosAteLimite(valores, tamanho, 10);
    printf("\nTotal encontrado: %d\n", contagem);

    return 0;
}