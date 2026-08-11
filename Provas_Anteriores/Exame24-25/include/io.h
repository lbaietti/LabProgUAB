#ifndef IO_H
#define IO_H

/**
* @brief Guarda todos os dados o sistema em disco
* @return 1 se todas as condições forem válidas. 0 em caso de falha.
*
*/

int guardar_dados(void);

/**
* @brief Carrega todos os dados do sistema a partir do disco.
* @return 1 se as condições forem válidas. 0 se algum ficheiro csv estiver corrompido.
 */

int carregar_dados(void);


#endif