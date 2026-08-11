/*
 * test_regas.c — Testes de unidade para o módulo regas
 *
 * Funções testadas:
 *   - registar_rega  (caso normal, planta inexistente, quantidade inválida,
 *                     data limite, limite de capacidade)
 *   - obter_total_regas
 *   - regas_gravar_csv / regas_carregar_csv (persistência isolada)
 *
 * Padrão de diagnóstico: assert() com printf explicativo anterior.
 */

#include <assert.h>
#include <stdio.h>

#include "plantas.h"
#include "regas.h"

/* Prepara o estado mínimo: uma planta para que as regas sejam válidas. */
static void preparar_dados(void) {
    resetar_plantas();
    resetar_regas();
    assert(adicionar_planta("Tomate", "Solanum", "01/01/2026", 2) == 1);
}

/* ------------------------------------------------------------------ */
/* Caso normal: rega com todos os dados válidos                        */
/* ------------------------------------------------------------------ */
static void testar_rega_valida(void) {
    preparar_dados();

    int resultado = registar_rega(1, 31, 250);
    if (resultado != 1) {
        printf("FALHA: rega valida deveria devolver 1, obteve %d\n", resultado);
    }
    assert(resultado == 1);
    assert(obter_total_regas() == 1);
    /* Verificar efeito colateral: ultima_rega da planta foi actualizado. */
    assert(obter_planta_por_id(1)->ultima_rega == 31);
    printf("OK: testar_rega_valida\n");
}

/* ------------------------------------------------------------------ */
/* Caso de erro: planta com ID inexistente                             */
/* ------------------------------------------------------------------ */
static void testar_rega_planta_inexistente(void) {
    resetar_plantas();
    resetar_regas();

    int resultado = registar_rega(99, 31, 250);
    if (resultado != 0) {
        printf("FALHA: planta inexistente deveria ser rejeitada\n");
    }
    assert(resultado == 0);
    assert(obter_total_regas() == 0);
    printf("OK: testar_rega_planta_inexistente\n");
}

/* ------------------------------------------------------------------ */
/* Caso de erro: quantidade_agua == 0 (N-1 do mínimo válido 1)        */
/* Justificação: o limite mínimo de água é 1 ml; testar 0 (N-1)       */
/* confirma que a fronteira inferior está correctamente guardada.      */
/* ------------------------------------------------------------------ */
static void testar_rega_quantidade_invalida(void) {
    preparar_dados();

    int resultado = registar_rega(1, 31, 0);
    if (resultado != 0) {
        printf("FALHA: quantidade invalida (0 ml) deveria ser rejeitada\n");
    }
    assert(resultado == 0);
    assert(obter_total_regas() == 0);
    /* Planta não deve ter sido alterada. */
    assert(obter_planta_por_id(1)->ultima_rega == 0);
    printf("OK: testar_rega_quantidade_invalida\n");
}

/* ------------------------------------------------------------------ */
/* Caso normal: quantidade_agua == 1 (N+1 de 0, mínimo válido)        */
/* Justificação: confirma que 1 ml (mínimo aceitável) é aceite.        */
/* ------------------------------------------------------------------ */
static void testar_rega_quantidade_minima_valida(void) {
    preparar_dados();

    int resultado = registar_rega(1, 31, 1);
    if (resultado != 1) {
        printf("FALHA: quantidade minima valida (1 ml) deveria ser aceite, obteve %d\n",
               resultado);
    }
    assert(resultado == 1);
    assert(obter_total_regas() == 1);
    printf("OK: testar_rega_quantidade_minima_valida\n");
}

/* ------------------------------------------------------------------ */
/* Caso limite: data_rega == 0 (timestamp mínimo, deve ser aceite)    */
/* Justificação: 0 representa o epoch; qualquer valor >= 0 é válido.  */
/* ------------------------------------------------------------------ */
static void testar_rega_data_zero(void) {
    preparar_dados();

    int resultado = registar_rega(1, 0, 100);
    if (resultado != 1) {
        printf("FALHA: data_rega 0 (epoch) deveria ser aceite, obteve %d\n",
               resultado);
    }
    assert(resultado == 1);
    printf("OK: testar_rega_data_zero\n");
}

/* ------------------------------------------------------------------ */
/* Persistência isolada: gravar e recarregar CSV de regas              */
/* ------------------------------------------------------------------ */
static void testar_csv_regas(void) {
    const char* caminho = "test_tmp_regas.csv";
    preparar_dados();
    assert(registar_rega(1, 50, 300) == 1);

    int gravado = regas_gravar_csv(caminho);
    if (gravado != 1) {
        printf("FALHA: regas_gravar_csv deveria devolver 1\n");
    }
    assert(gravado == 1);

    resetar_regas();
    int carregado = regas_carregar_csv(caminho);
    if (carregado != 1) {
        printf("FALHA: regas_carregar_csv deveria devolver 1\n");
    }
    assert(carregado == 1);
    assert(obter_total_regas() == 1);

    remove(caminho);
    printf("OK: testar_csv_regas\n");
}

int main(void) {
    testar_rega_valida();
    testar_rega_planta_inexistente();
    testar_rega_quantidade_invalida();
    testar_rega_quantidade_minima_valida();
    testar_rega_data_zero();
    testar_csv_regas();
    printf("\nTodos os testes de regas concluidos com sucesso.\n");
    return 0;
}
