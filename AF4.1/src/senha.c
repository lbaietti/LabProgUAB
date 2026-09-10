#include <string.h>
#include "../include/senha.h"

int classificar_senha(int comprimento, char *classe) {
    if (comprimento < 0 || classe == NULL) return 0;

    if (comprimento <= 3) strcpy(classe, "Fraca");
    else if (comprimento <= 7) strcpy(classe, "Media");
    else if (comprimento <= 15) strcpy(classe, "Forte");
    else strcpy(classe, "Muito Forte"); 
    
    return 1;
}

