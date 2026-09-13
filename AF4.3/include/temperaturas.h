#ifndef TEMPERATURAS_H
#define TEMPERATURAS_H

/*
 * Contrato de registar_temperatura:
 * - Pré-condição : lista != NULL; capacidade > 0; 0 <= indice < capacidade
 * - Pós-condição : lista[indice] == valor; restantes elementos inalterados
 * - Retorno      : 1 em caso de sucesso, 0 em caso de erro
 */
int registar_temperatura(float *lista, int capacidade, int indice, float valor);

/*
 * Contrato de media_temperaturas:
 * - Pré-condição : lista != NULL; n > 0; resultado != NULL
 * - Pós-condição : *resultado == média aritmética dos n primeiros elementos
 * - Retorno      : 1 em caso de sucesso, 0 em caso de erro
 */
int media_temperaturas(float *lista, int n, float *resultado);

#endif
