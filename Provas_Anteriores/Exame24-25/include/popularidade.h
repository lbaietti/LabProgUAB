#ifndef POPULARIDADE_H
#define POPULARIDADE_H

/**
* @brief Representa as interações feitas num post, optadas estas por serem parâmetros como:
*   - Visualizações 
*   - Curtidas 
*   - Comentários 
*/

int interacoes(int visualizacoes, int curtidas, int comentarios);

/**
* @brief guarda popularidade num ficheiro csv
* @return 1 se a escrita for bem sucedida. 0 se ocorrer erro de I/O
 */

int interacoes_gravar_csv(const char* caminho);



int interacoes_carregar_caminho(const char* caminho);

#endif
