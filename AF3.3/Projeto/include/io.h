#ifndef IO_H
#define IO_H

#include "contacto.h"

/**
 * Guarda um array de contactos num ficheiro de texto.
 * Formato: uma linha por campo, grupos separados por linha vazia.
 *
 * Parâmetros:
 *   ficheiro  - caminho do ficheiro de destino
 *   contactos - array de contactos a guardar
 *   total     - número de contactos no array
 *
 * Retorna:
 *   1 se guardou com sucesso, 0 em caso de erro
 */

int io_guardar(const char *ficheiros, const Contacto contactos[], int total);

/**
 * Carrega contactos de um ficheiro de texto para um array.
 *
 * Parâmetros:
 *   ficheiro  - caminho do ficheiro de origem
 *   contactos - array de destino
 *   max       - capacidade máxima do array
 *
 * Retorna:
 *   Número de contactos carregados, ou -1 em caso de erro
 */

int io_carregar(const char *ficheiros, const Contacto contactos[], int max);

#endif