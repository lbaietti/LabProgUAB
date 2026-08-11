/*
 * persistencia.c — Camada de persistência do GreenTrack
 *
 * Responsabilidade única: orquestrar a gravação e o carregamento de todos os
 * módulos de dados (plantas, regas e tarefas) através dos seus próprios
 * ficheiros CSV.
 *
 * Decisão de implementação: os caminhos dos ficheiros incluem o prefixo
 * "data/" para isolar os dados persistidos num subdirectório dedicado,
 * evitando poluir o directório de trabalho com ficheiros CSV avulsos.
 * Alternativa considerada: caminhos configuráveis por argumento — rejeitada
 * por acrescentar complexidade desnecessária para a dimensão do projecto.
 */

#include "persistencia.h"
#include "plantas.h"
#include "regas.h"
#include "tarefas.h"

/* Caminhos relativos ao directório de trabalho do executável. */
#define FICHEIRO_PLANTAS  "data/plantas.csv"
#define FICHEIRO_REGAS    "data/regas.csv"
#define FICHEIRO_TAREFAS  "data/tarefas.csv"

/*
 * guardar_dados — guarda todos os módulos em disco.
 *
 * Grava sequencialmente plantas, regas e tarefas. Se qualquer escrita
 * falhar, devolve 0 para que o chamador possa notificar o utilizador.
 * Os ficheiros já gravados com sucesso não são revertidos (comportamento
 * aceitável para um sistema de pequena escala sem transacções).
 */
int guardar_dados(void) {
    int ok_plantas  = plantas_gravar_csv(FICHEIRO_PLANTAS);
    int ok_regas    = regas_gravar_csv(FICHEIRO_REGAS);
    int ok_tarefas  = tarefas_gravar_csv(FICHEIRO_TAREFAS);
    return ok_plantas && ok_regas && ok_tarefas;
}

/*
 * carregar_dados — carrega todos os módulos a partir de disco.
 *
 * Se um ficheiro não existir, o módulo correspondente é inicializado vazio
 * (comportamento tolerante para a primeira execução do programa).
 * Devolve 0 apenas quando um CSV existe mas está corrompido.
 */
int carregar_dados(void) {
    int ok_plantas  = plantas_carregar_csv(FICHEIRO_PLANTAS);
    int ok_regas    = regas_carregar_csv(FICHEIRO_REGAS);
    int ok_tarefas  = tarefas_carregar_csv(FICHEIRO_TAREFAS);
    return ok_plantas && ok_regas && ok_tarefas;
}
