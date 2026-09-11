#include "../include/pontuacao.h"

int aplicar_bonus(int pontos, int bonus) {
    return pontos + (pontos * bonus / 100);
}

int aplicar_penalizacao(int pontos, int penalizacao) {
    if (penalizacao > pontos)
        return 0;
    return pontos - penalizacao;
}
