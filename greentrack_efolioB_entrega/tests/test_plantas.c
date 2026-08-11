/*
 * test_plantas.c — Testes de unidade para o módulo plantas
 *
 * Funções testadas:
 *   - adicionar_planta   (caso normal, limite de capacidade, inputs inválidos)
 *   - obter_planta_por_id (encontrar existente, ID inexistente)
 *   - obter_total_plantas (reflecte adições correctamente)
 *   - plantas_gravar_csv / plantas_carregar_csv (persistência isolada)
 *
 * Padrão de diagnóstico: assert() com printf explicativo anterior,
 * permitindo identificar a linha exacta da falha sem depurador externo.
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "plantas.h"

/* ------------------------------------------------------------------ */
/* Caso normal: adição de uma planta com todos os dados válidos        */
/* ------------------------------------------------------------------ */
static void testar_adicao_valida(void) {
    resetar_plantas();

    int resultado = adicionar_planta("Rosa", "Rosa canina", "10/04/2026", 3);
    if (resultado != 1) {
        printf("FALHA: adicionar_planta valida deveria devolver 1, obteve %d\n",
               resultado);
    }
    assert(resultado == 1);
    assert(obter_total_plantas() == 1);
    printf("OK: testar_adicao_valida\n");
}

/* ------------------------------------------------------------------ */
/* Caso de erro: intervalo_rega == 0 (valor negativo de fronteira)     */
/* Justificação: o limite mínimo é 1; testar 0 (N-1) confirma         */
/* que a validação de fronteira está correcta.                         */
/* ------------------------------------------------------------------ */
static void testar_adicao_intervalo_invalido(void) {
    resetar_plantas();

    int resultado = adicionar_planta("Rosa", "Rosa canina", "10/04/2026", 0);
    if (resultado != 0) {
        printf("FALHA: intervalo invalido (0) deveria ser rejeitado\n");
    }
    assert(resultado == 0);
    assert(obter_total_plantas() == 0);
    printf("OK: testar_adicao_intervalo_invalido\n");
}

/* ------------------------------------------------------------------ */
/* Caso de erro: intervalo_rega == -1 (abaixo do mínimo)              */
/* ------------------------------------------------------------------ */
static void testar_adicao_intervalo_negativo(void) {
    resetar_plantas();

    int resultado = adicionar_planta("Rosa", "Rosa canina", "10/04/2026", -1);
    if (resultado != 0) {
        printf("FALHA: intervalo negativo deveria ser rejeitado\n");
    }
    assert(resultado == 0);
    assert(obter_total_plantas() == 0);
    printf("OK: testar_adicao_intervalo_negativo\n");
}

/* ------------------------------------------------------------------ */
/* Caso normal: intervalo_rega == 1 (valor mínimo válido, N+1 de 0)   */
/* Justificação: confirma que o limite inferior aceitável é exactamente */
/* 1 dia — sensibilidade N±1 em torno de zero.                         */
/* ------------------------------------------------------------------ */
static void testar_adicao_intervalo_minimo_valido(void) {
    resetar_plantas();

    int resultado = adicionar_planta("Rosa", "Rosa canina", "10/04/2026", 1);
    if (resultado != 1) {
        printf("FALHA: intervalo 1 (minimo valido) deveria ser aceite, obteve %d\n",
               resultado);
    }
    assert(resultado == 1);
    assert(obter_total_plantas() == 1);
    printf("OK: testar_adicao_intervalo_minimo_valido\n");
}

/* ------------------------------------------------------------------ */
/* Caso de erro: nome vazio                                            */
/* ------------------------------------------------------------------ */
static void testar_adicao_nome_vazio(void) {
    resetar_plantas();

    int resultado = adicionar_planta("", "Rosa canina", "10/04/2026", 3);
    if (resultado != 0) {
        printf("FALHA: nome vazio deveria ser rejeitado\n");
    }
    assert(resultado == 0);
    assert(obter_total_plantas() == 0);
    printf("OK: testar_adicao_nome_vazio\n");
}

/* ------------------------------------------------------------------ */
/* Caso de erro: NULL como nome                                        */
/* ------------------------------------------------------------------ */
static void testar_adicao_nome_nulo(void) {
    resetar_plantas();

    int resultado = adicionar_planta(NULL, "Rosa canina", "10/04/2026", 3);
    if (resultado != 0) {
        printf("FALHA: nome NULL deveria ser rejeitado\n");
    }
    assert(resultado == 0);
    assert(obter_total_plantas() == 0);
    printf("OK: testar_adicao_nome_nulo\n");
}

/* ------------------------------------------------------------------ */
/* Caso limite: preencher exatamente MAX_PLANTAS e tentar uma extra    */
/* Justificação: testa o comportamento exato na fronteira da           */
/* capacidade máxima (N = MAX_PLANTAS); a planta N+1 deve ser recusada.*/
/* ------------------------------------------------------------------ */
static void testar_limite_maximo(void) {
    resetar_plantas();

    char nome[20];
    for (int i = 0; i < MAX_PLANTAS; i++) {
        snprintf(nome, sizeof(nome), "P%02d", i + 1);
        assert(adicionar_planta(nome, "Especie", "10/04/2026", 2) == 1);
    }

    int resultado = adicionar_planta("Extra", "Especie", "10/04/2026", 2);
    if (resultado != 0) {
        printf("FALHA: ultrapassar MAX_PLANTAS deveria falhar\n");
    }
    assert(resultado == 0);
    assert(obter_total_plantas() == MAX_PLANTAS);
    printf("OK: testar_limite_maximo\n");
}

/* ------------------------------------------------------------------ */
/* Caso normal: obter_planta_por_id com ID existente                   */
/* ------------------------------------------------------------------ */
static void testar_obter_planta_existente(void) {
    resetar_plantas();
    assert(adicionar_planta("Tomate", "Solanum", "01/03/2026", 2) == 1);

    Planta* p = obter_planta_por_id(1);
    if (p == NULL) {
        printf("FALHA: obter_planta_por_id(1) deveria devolver ponteiro valido\n");
    }
    assert(p != NULL);
    assert(strcmp(p->nome, "Tomate") == 0);
    printf("OK: testar_obter_planta_existente\n");
}

/* ------------------------------------------------------------------ */
/* Caso de erro: obter_planta_por_id com ID inexistente               */
/* ------------------------------------------------------------------ */
static void testar_obter_planta_inexistente(void) {
    resetar_plantas();

    Planta* p = obter_planta_por_id(99);
    if (p != NULL) {
        printf("FALHA: obter_planta_por_id(99) deveria devolver NULL\n");
    }
    assert(p == NULL);
    printf("OK: testar_obter_planta_inexistente\n");
}

/* ------------------------------------------------------------------ */
/* Persistência isolada: gravar e recarregar um CSV de plantas         */
/* ------------------------------------------------------------------ */
static void testar_csv_plantas(void) {
    const char* caminho = "test_tmp_plantas.csv";
    resetar_plantas();
    assert(adicionar_planta("Girassol", "Helianthus", "05/05/2026", 7) == 1);

    int gravado = plantas_gravar_csv(caminho);
    if (gravado != 1) {
        printf("FALHA: plantas_gravar_csv deveria devolver 1\n");
    }
    assert(gravado == 1);

    resetar_plantas();
    int carregado = plantas_carregar_csv(caminho);
    if (carregado != 1) {
        printf("FALHA: plantas_carregar_csv deveria devolver 1\n");
    }
    assert(carregado == 1);
    assert(obter_total_plantas() == 1);

    Planta* p = obter_planta_por_id(1);
    assert(p != NULL);
    assert(strcmp(p->nome, "Girassol") == 0);
    assert(p->intervalo_rega == 7);

    remove(caminho);
    printf("OK: testar_csv_plantas\n");
}

/* ------------------------------------------------------------------ */
/* Caso de erro: CSV inexistente deve inicializar vazio sem erro       */
/* ------------------------------------------------------------------ */
static void testar_csv_ficheiro_inexistente(void) {
    resetar_plantas();
    int resultado = plantas_carregar_csv("ficheiro_que_nao_existe.csv");
    if (resultado != 1) {
        printf("FALHA: ficheiro inexistente deveria devolver 1 (vazio), obteve %d\n",
               resultado);
    }
    assert(resultado == 1);
    assert(obter_total_plantas() == 0);
    printf("OK: testar_csv_ficheiro_inexistente\n");
}

int main(void) {
    testar_adicao_valida();
    testar_adicao_intervalo_invalido();
    testar_adicao_intervalo_negativo();
    testar_adicao_intervalo_minimo_valido();
    testar_adicao_nome_vazio();
    testar_adicao_nome_nulo();
    testar_limite_maximo();
    testar_obter_planta_existente();
    testar_obter_planta_inexistente();
    testar_csv_plantas();
    testar_csv_ficheiro_inexistente();
    printf("\nTodos os testes de plantas concluidos com sucesso.\n");
    return 0;
}
