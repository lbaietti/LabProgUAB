/*Conversor de numerais romanos

Escreva um programa para converter um número em numeração romana para a notação decimal.

Exemplo de conversão:
MCMLXXIX = 1979

Dica: Use um array de strings para armazenar os numerais romanos e um array de inteiros para armazenar os valores correspondentes.

Implemente um adequado tratamento de erros, que informe o utilizador, de forma clara, sobre o erro que cometeu na escrita do numeral romano (ex. usou uma letra não permitida como "P").*/

#include <stdio.h>
#include <string.h>

int main() {
    char roman[20];
    int decimal = 0;
    
    printf("Digite um numeral romano: ");
    scanf("%s", roman);
    
    // Arrays de numerais romanos e seus valores correspondentes
    char *numerals[] = {"I", "V", "X", "L", "C", "D", "M"};
    int values[] = {1, 5, 10, 50, 100, 500, 1000};
    
// Verificar cada caractere do numeral romano
for (int i = 0; i < strlen(roman); i++) {
    int found = 0;
    for (int j = 0; j < 7; j++) {
        if (roman[i] == numerals[j][0]) {
            decimal += values[j]; // Adicionar o valor correspondente
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Erro: Caractere '%c' não é um numeral romano válido.\n", roman[i]);
        return 1; // Sair com erro
    }
}
    printf("O numeral romano %s é igual a %d em decimal.\n", roman, decimal);
    return 0;
}   


