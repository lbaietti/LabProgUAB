#include <stdio.h>
#include <assert.h>
#include "../include/pontuacao.h"


/*
void testar_calcular_nivel(){
    assert(calcular_pontuacao_nivel(10, 2, 3));
    assert(calcular_pontuacao_nivel(10, 5, 0));
    assert(calcular_pontuacao_nivel(10, 15, 0));
    assert(calcular_pontuacao_nivel(100, 50, 20));

}
*/

void testar_calcular_nivel(){
    if(calcular_pontuacao_nivel(100, 50, 0) != 150)
    printf("Erro: Pontuação com penalização e bônus aplicados deveria ser 150 !\n");

    if(calcular_pontuacao_nivel(100, 50, 20) != 130)
    printf("Erro: Pontuação com penalização e bônus aplicados deveria ser 130 !\n");
}



int main(){
    testar_calcular_nivel();
    printf("    ---- TESTE CONCLUÍDO ----   \n");
}


