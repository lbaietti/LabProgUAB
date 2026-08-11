/*Escreva um programa para encontrar palíndromos num ficheiro de texto. Um palíndromo é uma sequência de caracteres que se lê da mesma forma, tanto da esquerda para a direita como da direita para a esquerda. Exemplos de palíndromos: sacas, rapar, rodador, anilina. Considere apenas palíndromos de comprimentos entre 3 e 10 caracteres.*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_palindrome(char *word) {
    int len = strlen(word);
    for (int i = 0; i < len / 2; i++) {
        if (tolower(word[i]) != tolower(word[len - 1 - i])) {
            return 0; // Não é um palíndromo
        }
    }
    return 1; // É um palíndromo
}

int main() {
    char filename[100];
    char word[20];
    
    printf("Digite o nome do arquivo de texto: ");
    scanf("%s", filename);
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("Palíndromos encontrados no arquivo:\n");
    while (fscanf(file, "%s", word) == 1) {
        int len = strlen(word);
        if (len >= 3 && len <= 10 && is_palindrome(word)) {
            printf("%s\n", word);
        }
    }
    
    fclose(file);
    return 0;
}  