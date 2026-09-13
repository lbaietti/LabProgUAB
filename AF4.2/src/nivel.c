#include "../include/pontuacao.h"

/*
 * Calcula a pontuação final de um nível:
 * aplica primeiro o bónus e depois a penalização ao resultado.
 * Esperado: aplicar_penalizacao( aplicar_bonus(pontos, bonus), penalizacao )
 */
int calcular_pontuacao_nivel(int pontos, int bonus, int penalizacao) {
    int com_bonus = aplicar_bonus(pontos, bonus);
    return aplicar_penalizacao(com_bonus, penalizacao); /* ERRO: deveria usar 'com_bonus', não 'pontos' */
}
