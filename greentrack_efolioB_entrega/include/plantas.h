#ifndef PLANTAS_H
#define PLANTAS_H

#include <stddef.h>

#define MAX_PLANTAS 100

/**
 * @brief Representa uma planta gerida pelo sistema.
 *
 * A estrutura é exposta no cabeçalho para permitir leitura em testes e
 * integrar de forma controlada com outros módulos, sem expor o armazenamento
 * interno em array.
 */
typedef struct {
    int  id;
    char nome[50];
    char especie[50];
    char data_plantio[11];
    int  intervalo_rega;
    int  ultima_rega;
} Planta;

/**
 * @brief Adiciona uma nova planta ao sistema.
 * @param nome Nome da planta; não pode ser NULL nem vazio.
 * @param especie Espécie da planta; não pode ser NULL nem vazia.
 * @param data_plantio Data de plantio em formato DD/MM/AAAA.
 * @param intervalo_rega Intervalo de rega em dias; deve ser positivo.
 * @return 1 se a planta foi adicionada com sucesso; 0 em caso de erro
 *         (limite atingido, dados inválidos ou texto demasiado longo).
 * @pre O módulo deve ter espaço disponível no limite MAX_PLANTAS.
 */
int adicionar_planta(const char* nome,
                     const char* especie,
                     const char* data_plantio,
                     int intervalo_rega);

/**
 * @brief Lista as plantas existentes no ecrã.
 * @sideeffect Escreve informação no stdout.
 */
void listar_plantas(void);

/**
 * @brief Obtém um ponteiro para a planta com o ID indicado.
 * @param id Identificador da planta.
 * @return Ponteiro para a planta se existir; NULL caso contrário.
 */
Planta* obter_planta_por_id(int id);

/**
 * @brief Devolve o número de plantas atualmente registadas.
 * @return Número de plantas existentes no sistema.
 */
int obter_total_plantas(void);

/**
 * @brief Remove todos os registos em memória.
 * @sideeffect Reinicializa o estado do módulo para permitir testes isolados.
 */
void resetar_plantas(void);

/**
 * @brief Atualiza a última rega de uma planta.
 * @param id_planta ID da planta a atualizar.
 * @param data_rega Data da rega em timestamp simplificado.
 * @sideeffect Altera o estado interno da planta, se existir.
 */
void atualizar_ultima_rega(int id_planta, int data_rega);

/**
 * @brief Guarda as plantas num ficheiro CSV.
 * @param caminho Caminho do ficheiro destino.
 * @return 1 se a escrita for bem-sucedida; 0 se ocorrer erro de I/O.
 * @sideeffect Sobrescreve o ficheiro indicado.
 */
int plantas_gravar_csv(const char* caminho);

/**
 * @brief Carrega as plantas a partir de um ficheiro CSV.
 * @param caminho Caminho do ficheiro origem.
 * @return 1 se a leitura for bem-sucedida ou se o ficheiro não existir; 0 se o CSV estiver corrompido.
 * @sideeffect Substitui o estado atual em memória.
 */
int plantas_carregar_csv(const char* caminho);

#endif
