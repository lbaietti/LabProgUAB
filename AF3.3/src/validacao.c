#include "../include/validacao.h"
#include <string.h>
#include <ctype.h>

/* Procura o índice do "@" na string; retorna -1 se não encontrar*/
static int encontrarArroba(const char *email){
    int i;

    for(i = 0; email[i] != '\0'; i++){
        if(email[i] == '@') return i;
    }
    return -1;
}

int validacao_emailValido(const char *email){
    int posicao_arroba, ponto_encontrado, i;

    if(email == NULL) return 0; 

    posicao_arroba = encontrarArroba(email);
    /* Deve ter '@' e não pode ser  primeiro ou último carácter */
    if(posicao_arroba <= 0 || email[posicao_arroba +1] == '\0') return 0;

    /* Deve existir ao menos um '.' após o '@'*/
    ponto_encontrado = 0;
    for(i = posicao_arroba +1; email[i] != '\0'; i++){
        if(email[i] == '.') ponto_encontrado = 1;
    }

    return ponto_encontrado;
}


int validacao_telefoneValido(const char *telefone){
    int i = 0; 
    int comprimento;

    if(telefone == NULL) return 0;

    if(telefone[0] == '+') i = 1;

    comprimento = (int)strlen(telefone);

    /* Enter 9 e 15 dígitos (sem contar o +)*/
    if(comprimento - i < 9 || comprimento - i > 15) return 0;

    /* Todos os restantes caracteres devem ser dígitos*/
    for(i = 1; telefone[i] != '\0'; i++){
        if(!isdigit((unsigned char) telefone[i])) return 0;
    }
    return 1;
}