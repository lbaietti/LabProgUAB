#ifndef REGAS_H
#define REGAS_H

/**
 * @brief Regista uma rega associada a uma planta.
 * @param id_planta ID da planta a regar.
 * @param data_rega Timestamp simplificado da rega.
 * @param quantidade_agua Quantidade de água em ml; deve ser positiva.
 * @return 1 se a rega foi registada; 0 em caso de erro (planta inexistente,
 *         quantidade inválida ou capacidade máxima atingida).
 * @pre A planta com id_planta deve existir.
 */
int registar_rega(int id_planta,
                  int data_rega,
                  int quantidade_agua);

/**
 * @brief Lista as regas no terminal.
 * @sideeffect Escreve informação no stdout.
 */
void listar_regas(void);

/** @brief Remove todos os registos de rega em memória. */
void resetar_regas(void);

/** @brief Devolve o número de regas registadas. */
int obter_total_regas(void);

/**
 * @brief Guarda as regas num ficheiro CSV.
 * @param caminho Caminho do ficheiro destino.
 * @return 1 se a gravação for bem-sucedida; 0 se ocorrer erro de I/O.
 */
int regas_gravar_csv(const char* caminho);

/**
 * @brief Carrega as regas a partir de um ficheiro CSV.
 * @param caminho Caminho do ficheiro origem.
 * @return 1 se a leitura for bem-sucedida ou se o ficheiro não existir; 0 se o CSV estiver corrompido.
 */
int regas_carregar_csv(const char* caminho);

#endif
