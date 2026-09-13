#include "../include/pontuacao.h"
#include <assert.h>
#include <stdio.h>

void testar_aplicar_bonus(){
    assert(aplicar_bonus(100, 5));
    assert(aplicar_bonus(12, 0));
    assert(aplicar_bonus(500, 1000));
    assert(aplicar_bonus(20, 2000));
}

void testar_aplicar_penalizacao(){
    assert(aplicar_penalizacao(8, 3));
    assert(aplicar_penalizacao(6, 5));
    
}

int main(){
    testar_aplicar_bonus();
    testar_aplicar_penalizacao();

    printf("    ---- TESTE CONCLUÍDO ----   \n");

}