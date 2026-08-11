/*
 * test_integracao.c — Testes de integração do GreenTrack
 *
 * Cenários testados:
 *   1. Persistência completa (guardar_dados + carregar_dados):
 *      valida que os três módulos (plantas, regas, tarefas) são
 *      correctamente serializados e deserializados de forma integrada.
 *
 *   2. Lógica de negócio entre módulos (rega actualiza planta):
 *      valida que registar_rega produz o efeito colateral esperado em
 *      plantas.ultima_rega, confirmando a comunicação correcta entre
 *      os módulos regas e plantas.
 *
 *   3. Comportamento perante CSV corrompido:
 *      valida que o sistema devolve erro ao tentar carregar um ficheiro
 *      com dados inválidos, sem corromper o estado em memória.
 *
 *   4. Ciclo completo de uma tarefa (criar → concluir → persistir):
 *      valida que o estado de conclusão de uma tarefa sobrevive a um
 *      ciclo de gravação e carregamento.
 *
 * Nota: os ficheiros CSV temporários são criados no directório de trabalho
 * actual e removidos após cada teste para não deixar rastos.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "persistencia.h"
#include "plantas.h"
#include "regas.h"
#include "tarefas.h"

/* Caminhos temporários usados nos testes (não interferem com data/). */
#define CSV_PLANTAS  "integ_plantas.csv"
#define CSV_REGAS    "integ_regas.csv"
#define CSV_TAREFAS  "integ_tarefas.csv"

static void limpar_ficheiros_teste(void) {
    remove(CSV_PLANTAS);
    remove(CSV_REGAS);
    remove(CSV_TAREFAS);
}

/* ------------------------------------------------------------------ */
/* Cenário 1: persistência completa entre guardar e carregar           */
/* Módulos envolvidos: plantas, regas, tarefas, persistencia           */
/* ------------------------------------------------------------------ */
static void testar_integracao_persistencia(void) {
    limpar_ficheiros_teste();
    resetar_plantas();
    resetar_regas();
    resetar_tarefas();

    /* Arrange: criar um estado conhecido em memória. */
    assert(adicionar_planta("Rabanete", "Raphanus", "02/01/2026", 4) == 1);
    assert(registar_rega(1, 31, 120) == 1);
    assert(criar_tarefa("Verificar humidade", 40) == 1);

    /* Act: guardar para CSV. */
    int gravado = plantas_gravar_csv(CSV_PLANTAS) &&
                  regas_gravar_csv(CSV_REGAS)     &&
                  tarefas_gravar_csv(CSV_TAREFAS);
    if (gravado != 1) {
        printf("FALHA: guardar dados deveria ter sucesso\n");
    }
    assert(gravado == 1);

    /* Act: apagar memória e recarregar. */
    resetar_plantas();
    resetar_regas();
    resetar_tarefas();

    int carregado = plantas_carregar_csv(CSV_PLANTAS) &&
                    regas_carregar_csv(CSV_REGAS)     &&
                    tarefas_carregar_csv(CSV_TAREFAS);
    if (carregado != 1) {
        printf("FALHA: carregar dados deveria ter sucesso\n");
    }
    assert(carregado == 1);

    /* Assert: verificar integridade dos dados após carregamento. */
    assert(obter_total_plantas() == 1);
    assert(obter_total_regas()   == 1);
    assert(obter_total_tarefas() == 1);
    assert(obter_planta_por_id(1)->ultima_rega == 31);
    assert(tarefa_estado(1) == 0); /* pendente */

    limpar_ficheiros_teste();
    printf("OK: testar_integracao_persistencia\n");
}

/* ------------------------------------------------------------------ */
/* Cenário 2: registar_rega actualiza ultima_rega na planta            */
/* Módulos envolvidos: regas, plantas                                  */
/* ------------------------------------------------------------------ */
static void testar_integracao_rega_actualiza_planta(void) {
    resetar_plantas();
    resetar_regas();

    assert(adicionar_planta("Alface", "Lactuca", "05/01/2026", 3) == 1);
    /* Antes da rega, ultima_rega deve ser 0. */
    assert(obter_planta_por_id(1)->ultima_rega == 0);

    assert(registar_rega(1, 35, 200) == 1);
    /* Após a rega, ultima_rega deve reflectir a data registada. */
    int ultima = obter_planta_por_id(1)->ultima_rega;
    if (ultima != 35) {
        printf("FALHA: ultima_rega esperado 35, obtido %d\n", ultima);
    }
    assert(ultima == 35);
    printf("OK: testar_integracao_rega_actualiza_planta\n");
}

/* ------------------------------------------------------------------ */
/* Cenário 3: CSV corrompido é rejeitado sem corromper memória         */
/* Módulos envolvidos: plantas, persistencia                           */
/* ------------------------------------------------------------------ */
static void testar_integracao_csv_corrompido(void) {
    const char* caminho = "integ_corrompido.csv";

    /* Criar ficheiro com conteúdo inválido (campos insuficientes). */
    FILE* f = fopen(caminho, "w");
    assert(f != NULL);
    fprintf(f, "nao,e,um,csv,valido\n");
    fclose(f);

    resetar_plantas();
    int resultado = plantas_carregar_csv(caminho);

    if (resultado != 0) {
        printf("FALHA: CSV corrompido deveria devolver 0, obteve %d\n", resultado);
    }
    assert(resultado == 0);
    /* Estado em memória deve estar limpo (resetar chamado internamente). */
    assert(obter_total_plantas() == 0);

    remove(caminho);
    printf("OK: testar_integracao_csv_corrompido\n");
}

/* ------------------------------------------------------------------ */
/* Cenário 4: ciclo completo criar → concluir → guardar → recarregar  */
/* Módulos envolvidos: tarefas, persistencia                           */
/* ------------------------------------------------------------------ */
static void testar_integracao_ciclo_tarefa(void) {
    limpar_ficheiros_teste();
    resetar_tarefas();

    assert(criar_tarefa("Fertilizar", 50) == 1);
    assert(criar_tarefa("Podar", 60) == 1);
    assert(concluir_tarefa(1) == 1);

    /* Guardar estado com tarefa 1 concluída. */
    assert(tarefas_gravar_csv(CSV_TAREFAS) == 1);

    resetar_tarefas();
    assert(tarefas_carregar_csv(CSV_TAREFAS) == 1);

    /* Verificar que o estado de conclusão foi preservado. */
    int estado1 = tarefa_estado(1);
    int estado2 = tarefa_estado(2);
    if (estado1 != 1) {
        printf("FALHA: tarefa 1 deveria estar concluida (1), obteve %d\n", estado1);
    }
    if (estado2 != 0) {
        printf("FALHA: tarefa 2 deveria estar pendente (0), obteve %d\n", estado2);
    }
    assert(estado1 == 1);
    assert(estado2 == 0);

    limpar_ficheiros_teste();
    printf("OK: testar_integracao_ciclo_tarefa\n");
}

int main(void) {
    testar_integracao_persistencia();
    testar_integracao_rega_actualiza_planta();
    testar_integracao_csv_corrompido();
    testar_integracao_ciclo_tarefa();
    limpar_ficheiros_teste();
    printf("\nTodos os testes de integracao concluidos com sucesso.\n");
    return 0;
}
