/*
 * regas.c — Módulo de gestão de regas do GreenTrack
 *
 * Responsabilidade: registar e listar as regas associadas a plantas
 * existentes, actualizando o campo ultima_rega da planta correspondente
 * como efeito colateral de cada registo bem-sucedido.
 *
 * Dependência explícita: este módulo depende de plantas.h para verificar
 * a existência da planta antes de aceitar a rega (regra de negócio: não
 * se pode regar uma planta desconhecida).
 *
 * Decisão de capacidade: MAX_REGAS = 500. Valor escolhido para suportar
 * regas diárias de até 100 plantas durante cerca de 5 dias sem atingir
 * o limite — suficiente para a escala do projecto.
 */

#include "regas.h"
#include "plantas.h"

#include <stdio.h>

#define MAX_REGAS 500

typedef struct {
    int id;
    int id_planta;
    int data_rega;       /* Timestamp simplificado (inteiro). */
    int quantidade_agua; /* Em mililitros; deve ser > 0. */
} Rega;

static Rega regas[MAX_REGAS];
static int  total_regas = 0;

/* ------------------------------------------------------------------ */
/* Funções de validação internas                                        */
/* ------------------------------------------------------------------ */

/*
 * quantidade_valida — a quantidade de água deve ser positiva (> 0 ml).
 * Justificação: 0 ml não constitui uma rega; valores negativos são
 * fisicamente impossíveis.
 */
static int quantidade_valida(int quantidade_agua) {
    return quantidade_agua > 0;
}

/*
 * data_valida — aceita qualquer timestamp não negativo.
 * O valor 0 representa o epoch (referência temporal base) e é legítimo.
 */
static int data_valida(int data_rega) {
    return data_rega >= 0;
}

/* ------------------------------------------------------------------ */
/* Interface pública                                                    */
/* ------------------------------------------------------------------ */

void resetar_regas(void) {
    total_regas = 0;
}

int obter_total_regas(void) {
    return total_regas;
}

int registar_rega(int id_planta,
                  int data_rega,
                  int quantidade_agua) {
    /* Guard clause: capacidade máxima atingida. */
    if (total_regas >= MAX_REGAS) {
        return 0;
    }

    /* Guard clause: a planta deve existir antes de registar a rega. */
    if (!obter_planta_por_id(id_planta)) {
        return 0;
    }

    /* Guard clause: validações dos valores numéricos. */
    if (!data_valida(data_rega) || !quantidade_valida(quantidade_agua)) {
        return 0;
    }

    regas[total_regas].id             = total_regas + 1;
    regas[total_regas].id_planta      = id_planta;
    regas[total_regas].data_rega      = data_rega;
    regas[total_regas].quantidade_agua = quantidade_agua;
    total_regas++;

    /* Efeito colateral deliberado: actualizar o registo de última rega
     * na planta associada, evitando que o chamador necessite de o fazer. */
    atualizar_ultima_rega(id_planta, data_rega);
    return 1;
}

void listar_regas(void) {
    printf("=== REGAS ===\n");
    if (total_regas == 0) {
        printf("Sem regas registadas.\n");
        return;
    }

    for (int i = 0; i < total_regas; i++) {
        printf("Rega %d | Planta:%d | Data:%d | Quantidade:%dml\n",
               regas[i].id,
               regas[i].id_planta,
               regas[i].data_rega,
               regas[i].quantidade_agua);
    }
}

/*
 * regas_gravar_csv — serializa as regas em formato CSV.
 * Formato: id,id_planta,data_rega,quantidade_agua
 */
int regas_gravar_csv(const char* caminho) {
    if (!caminho || caminho[0] == '\0') {
        return 0;
    }

    FILE* f = fopen(caminho, "w");
    if (!f) {
        return 0;
    }

    for (int i = 0; i < total_regas; i++) {
        if (fprintf(f, "%d,%d,%d,%d\n",
                    regas[i].id,
                    regas[i].id_planta,
                    regas[i].data_rega,
                    regas[i].quantidade_agua) < 0) {
            fclose(f);
            return 0;
        }
    }

    fclose(f);
    return 1;
}

/*
 * regas_carregar_csv — desserializa regas a partir de CSV.
 * Tolerante a ficheiro ausente; intolerante a linhas malformadas.
 */
int regas_carregar_csv(const char* caminho) {
    if (!caminho || caminho[0] == '\0') {
        return 0;
    }

    FILE* f = fopen(caminho, "r");
    if (!f) {
        resetar_regas();
        return 1;
    }

    resetar_regas();

    while (total_regas < MAX_REGAS) {
        Rega temporaria;
        int lidos = fscanf(f, "%d,%d,%d,%d",
                           &temporaria.id,
                           &temporaria.id_planta,
                           &temporaria.data_rega,
                           &temporaria.quantidade_agua);

        if (lidos == EOF) {
            break;
        }

        if (lidos != 4) {
            fclose(f);
            resetar_regas();
            return 0;
        }

        regas[total_regas++] = temporaria;
    }

    fclose(f);
    return 1;
}
