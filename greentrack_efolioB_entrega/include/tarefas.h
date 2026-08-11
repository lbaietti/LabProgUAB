#ifndef TAREFAS_H
#define TAREFAS_H

/**
 * @brief Cria uma nova tarefa.
 * @param descricao Descrição da tarefa; não pode ser NULL nem vazia.
 * @param data_prevista Timestamp simplificado da data prevista; deve ser não negativo.
 * @return 1 se a tarefa for criada; 0 em caso de erro (dados inválidos ou limite atingido).
 */
int criar_tarefa(const char* descricao, int data_prevista);

/**
 * @brief Marca uma tarefa como concluída.
 * @param id_tarefa ID da tarefa a concluir.
 * @return 1 se a tarefa existir e for concluída; 0 caso contrário.
 */
int concluir_tarefa(int id_tarefa);

/** @brief Lista as tarefas ainda pendentes no terminal. */
void listar_tarefas_pendentes(void);

/** @brief Remove todas as tarefas em memória. */
void resetar_tarefas(void);

/** @brief Devolve o número de tarefas registadas. */
int obter_total_tarefas(void);

/**
 * @brief Indica o estado de conclusão de uma tarefa.
 * @param id_tarefa ID da tarefa.
 * @return -1 se a tarefa não existir; 0 se estiver pendente; 1 se estiver concluída.
 */
int tarefa_estado(int id_tarefa);

/**
 * @brief Guarda as tarefas num ficheiro CSV.
 * @param caminho Caminho do ficheiro destino.
 * @return 1 se a gravação for bem-sucedida; 0 se ocorrer erro de I/O.
 */
int tarefas_gravar_csv(const char* caminho);

/**
 * @brief Carrega as tarefas a partir de um ficheiro CSV.
 * @param caminho Caminho do ficheiro origem.
 * @return 1 se a leitura for bem-sucedida ou se o ficheiro não existir; 0 se o CSV estiver corrompido.
 */
int tarefas_carregar_csv(const char* caminho);

#endif
