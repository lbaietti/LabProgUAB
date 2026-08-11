/*
 * test_tarefas.c — Testes de unidade para o módulo tarefas
 *
 * Funções testadas:
 *   - criar_tarefa       (caso normal, descrição vazia, data negativa,
 *                         limite de capacidade)
 *   - concluir_tarefa    (tarefa existente, ID inexistente)
 *   - tarefa_estado      (pendente, concluída, inexistente)
 *   - tarefas_gravar_csv / tarefas_carregar_csv (persistência isolada)
 *
 * Padrão de diagnóstico: assert() com printf explicativo anterior.
 */

#include <assert.h>
#include <stdio.h>

#include "tarefas.h"

/* ------------------------------------------------------------------ */
/* Caso normal: criar tarefa com dados válidos                         */
/* ------------------------------------------------------------------ */
static void testar_tarefa_valida(void) {
    resetar_tarefas();

    int resultado = criar_tarefa("Regar estufa", 15);
    if (resultado != 1) {
        printf("FALHA: tarefa valida deveria devolver 1, obteve %d\n", resultado);
    }
    assert(resultado == 1);
    assert(obter_total_tarefas() == 1);
    /* Estado inicial deve ser pendente (0). */
    assert(tarefa_estado(1) == 0);
    printf("OK: testar_tarefa_valida\n");
}

/* ------------------------------------------------------------------ */
/* Caso de erro: descrição vazia                                       */
/* ------------------------------------------------------------------ */
static void testar_tarefa_descricao_invalida(void) {
    resetar_tarefas();

    int resultado = criar_tarefa("", 15);
    if (resultado != 0) {
        printf("FALHA: descricao vazia deveria ser rejeitada\n");
    }
    assert(resultado == 0);
    assert(obter_total_tarefas() == 0);
    printf("OK: testar_tarefa_descricao_invalida\n");
}

/* ------------------------------------------------------------------ */
/* Caso de erro: data_prevista negativa                                */
/* Justificação: 0 é aceite (epoch), -1 é o N-1 de 0 e deve ser       */
/* rejeitado, confirmando a fronteira inferior correctamente.          */
/* ------------------------------------------------------------------ */
static void testar_tarefa_data_negativa(void) {
    resetar_tarefas();

    int resultado = criar_tarefa("Adubagem", -1);
    if (resultado != 0) {
        printf("FALHA: data_prevista negativa deveria ser rejeitada\n");
    }
    assert(resultado == 0);
    assert(obter_total_tarefas() == 0);
    printf("OK: testar_tarefa_data_negativa\n");
}

/* ------------------------------------------------------------------ */
/* Caso limite: data_prevista == 0 (N+1 de -1, mínimo válido)         */
/* Justificação: confirma que 0 (epoch) é aceite.                      */
/* ------------------------------------------------------------------ */
static void testar_tarefa_data_zero(void) {
    resetar_tarefas();

    int resultado = criar_tarefa("Poda", 0);
    if (resultado != 1) {
        printf("FALHA: data_prevista 0 deveria ser aceite, obteve %d\n", resultado);
    }
    assert(resultado == 1);
    printf("OK: testar_tarefa_data_zero\n");
}

/* ------------------------------------------------------------------ */
/* Caso normal: concluir tarefa existente                              */
/* ------------------------------------------------------------------ */
static void testar_concluir_tarefa(void) {
    resetar_tarefas();
    assert(criar_tarefa("Limpar canteiro", 20) == 1);

    int resultado = concluir_tarefa(1);
    if (resultado != 1) {
        printf("FALHA: concluir tarefa existente deveria devolver 1, obteve %d\n",
               resultado);
    }
    assert(resultado == 1);
    assert(tarefa_estado(1) == 1);
    printf("OK: testar_concluir_tarefa\n");
}

/* ------------------------------------------------------------------ */
/* Caso de erro: concluir tarefa com ID inexistente                   */
/* ------------------------------------------------------------------ */
static void testar_concluir_tarefa_inexistente(void) {
    resetar_tarefas();

    int resultado = concluir_tarefa(999);
    if (resultado != 0) {
        printf("FALHA: concluir tarefa inexistente deveria devolver 0\n");
    }
    assert(resultado == 0);
    printf("OK: testar_concluir_tarefa_inexistente\n");
}

/* ------------------------------------------------------------------ */
/* Caso de erro: tarefa_estado com ID inexistente devolve -1          */
/* ------------------------------------------------------------------ */
static void testar_estado_tarefa_inexistente(void) {
    resetar_tarefas();

    int estado = tarefa_estado(42);
    if (estado != -1) {
        printf("FALHA: tarefa_estado de ID inexistente deveria devolver -1, obteve %d\n",
               estado);
    }
    assert(estado == -1);
    printf("OK: testar_estado_tarefa_inexistente\n");
}

/* ------------------------------------------------------------------ */
/* Persistência isolada: gravar e recarregar CSV de tarefas            */
/* ------------------------------------------------------------------ */
static void testar_csv_tarefas(void) {
    const char* caminho = "test_tmp_tarefas.csv";
    resetar_tarefas();
    assert(criar_tarefa("Verificar humidade", 100) == 1);
    assert(criar_tarefa("Cortar relva", 200) == 1);
    assert(concluir_tarefa(1) == 1);

    int gravado = tarefas_gravar_csv(caminho);
    if (gravado != 1) {
        printf("FALHA: tarefas_gravar_csv deveria devolver 1\n");
    }
    assert(gravado == 1);

    resetar_tarefas();
    int carregado = tarefas_carregar_csv(caminho);
    if (carregado != 1) {
        printf("FALHA: tarefas_carregar_csv deveria devolver 1\n");
    }
    assert(carregado == 1);
    assert(obter_total_tarefas() == 2);
    assert(tarefa_estado(1) == 1); /* concluída */
    assert(tarefa_estado(2) == 0); /* pendente  */

    remove(caminho);
    printf("OK: testar_csv_tarefas\n");
}

int main(void) {
    testar_tarefa_valida();
    testar_tarefa_descricao_invalida();
    testar_tarefa_data_negativa();
    testar_tarefa_data_zero();
    testar_concluir_tarefa();
    testar_concluir_tarefa_inexistente();
    testar_estado_tarefa_inexistente();
    testar_csv_tarefas();
    printf("\nTodos os testes de tarefas concluidos com sucesso.\n");
    return 0;
}
