#ifndef PONTUACAO_H
#define PONTUACAO_H

/* Aplica um bónus percentual: retorna pontos + (pontos * bonus / 100) */
int aplicar_bonus(int pontos, int bonus);

/* Aplica uma penalização: subtrai penalizacao; não desce abaixo de zero */
int aplicar_penalizacao(int pontos, int penalizacao);

#endif
