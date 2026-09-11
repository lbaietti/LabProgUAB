#ifndef PROGRAMA_REFATORADO_H
#define PROGRAMA_REFATORAO_H

/**
 * @brief
 * O seguinte programa ter por objetivo somar 
 * pares de elementos positivos dos quais contém em um vector
 */

bool ehPar(int valor);

bool ehPositivo(int valor);

int somarPares(const int valores[], int soma, int tamanho);

int listarPositivosAteLimite(const int valores[], int tamanho, int limite);


#endif