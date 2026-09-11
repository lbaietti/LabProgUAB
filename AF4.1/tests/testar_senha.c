#include "../include/senha.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

int classificar_senha(int comprimento, char *classe);

void testar_senha(){
    char buf[32];

    assert(classificar_senha(0, buf) == 1);
    assert(classificar_senha(1, buf) == 1);
    assert(classificar_senha(3, buf) == 1);
    assert(classificar_senha(4, buf) == 1);
    assert(classificar_senha(7, buf) == 1);
    assert(classificar_senha(8, buf) == 1);
    assert(classificar_senha(15, buf) == 1);
    assert(classificar_senha(16, buf) == 1);
    assert(classificar_senha(31, buf) == 1); /*Falha aqui ! Programa termina !*/

    /* Não chega a ser executado com o código errado*/
    assert(classificar_senha(-1, buf) == 0);
    assert(classificar_senha(5, NULL) == 0);

    classificar_senha(0, buf); assert(strcmp(buf, "Fraca")  == 0);
    classificar_senha(4, buf); assert(strcmp(buf, "Media")  == 0);
    classificar_senha(8, buf); assert(strcmp(buf, "Forte")  == 0);
    classificar_senha(16, buf); assert(strcmp(buf, "Muito Forte") == 0);
}

