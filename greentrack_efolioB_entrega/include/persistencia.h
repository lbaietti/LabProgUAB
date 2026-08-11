#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "posts.h"
#include "popularidade.h"

/**
 * @brief Guarda todos os dados do sistema em disco.
 * @return 1 se todas as escritas forem bem-sucedidas; 0 se alguma falhar.
 */
int guardar_dados(void);

/**
 * @brief Carrega todos os dados do sistema a partir de disco.
 * @return 1 se a leitura for bem-sucedida (ou se os ficheiros ainda não existirem); 0 se algum CSV estiver corrompido.
 */
int carregar_dados(void);

#endif
