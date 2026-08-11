/*Programa aprimorado para encontrar palíndromos em frases num ficheiro de texto.
Um palíndromo é uma sequência de caracteres que se lê da mesma forma, tanto da esquerda para a direita como da direita para a esquerda.
Agora considera frases, ignorando vírgulas, acentos, pontuações, convertendo para minúsculas.
Mantém os espaços no output.*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Função para remover acentos e converter para minúsculas, removendo pontuações e espaços
void clean_string(char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        unsigned char c = (unsigned char)input[i];
        // Converter para minúscula
        c = tolower(c);
        // Substituir acentos básicos (para português)
        if (c == 225 || c == 224 || c == 226 || c == 227) c = 'a'; // á à â ã
        else if (c == 233 || c == 232 || c == 234) c = 'e'; // é è ê
        else if (c == 237 || c == 236 || c == 238) c = 'i'; // í ì î
        else if (c == 243 || c == 242 || c == 244 || c == 245) c = 'o'; // ó ò ô õ
        else if (c == 250 || c == 249 || c == 251) c = 'u'; // ú ù û
        else if (c == 231) c = 'c'; // ç
        // Manter apenas letras
        if (isalpha(c)) {
            output[j++] = c;
        }
    }
    output[j] = '\0';
}

int is_palindrome(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char filename[100];
    char line[256];
    
    printf("Digite o nome do arquivo de texto: ");
    scanf("%s", filename);
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("Palíndromos encontrados no arquivo:\n");
    while (fgets(line, sizeof(line), file)) {
        // Remover newline
        line[strcspn(line, "\n")] = '\0';
        
        char cleaned[256];
        clean_string(line, cleaned);
        
        if (strlen(cleaned) >= 3 && is_palindrome(cleaned)) {
            printf("%s\n", line);
        }
    }
    
    fclose(file);
    return 0;
}