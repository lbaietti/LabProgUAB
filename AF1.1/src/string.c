#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "palindrome.h"



/* Função para remover acentos e converter para minúsculas, removendo pontuações e espaços*/

static void clean_string(char *input, char *output) {
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