/*
 * tarefas.c — Módulo de gestão de tarefas do GreenTrack
 *
 * Responsabilidade: criar, concluir e listar tarefas de manutenção,
 * bem como serializar/deserializar o seu estado em CSV.
 *
 * Modelo de estado: cada tarefa tem o campo `concluida` (0 = pendente,
 * 1 = concluída). Uma tarefa concluída não é removida da lista — mantém-
 * se disponível para auditoria e persistência, sendo filtrada na listagem
 * de pendentes.
 *
 * Decisão de capacidade: MAX_TAREFAS = 200. Suporta uma gestão activa
 * de tarefas ao longo de várias semanas sem atingir o limite.
 */

#include "tarefas.h"

#include <stdio.h>
#include <string.h>

#define MAX_TAREFAS 200

typedef struct {
    int  id;
    char descricao[100]; /* Texto livre; não pode ser vazio. */
    int  data_prevista;  /* Timestamp simplificado; >= 0.   */
    int  concluida;      /* 0 = pendente, 1 = concluída.    */
} Tarefa;

static Tarefa tarefas[MAX_TAREFAS];
static int    total_tarefas = 0;

/* ------------------------------------------------------------------ */
/* Funções auxiliares internas                                          */
/* ------------------------------------------------------------------ */

/* texto_valido — reutilizada de plantas.c por ser um helper comum. */
static int texto_valido(const char* texto) {
    return texto != NULL && texto[0] != '\0';
}

static int texto_cabe_no_buffer(const char* texto, size_t capacidade) {
    if (texto == NULL) {
        return 0;
    }
    return strlen(texto) < capacidade;
}

static int copiar_texto(char* destino, size_t capacidade, const char* origem) {
    if (!texto_cabe_no_buffer(origem, capacidade)) {
        return 0;
    }
    snprintf(destino, capacidade, "%s", origem);
    return 1;
}

/* ------------------------------------------------------------------ */
/* Interface pública                                                    */
/* ------------------------------------------------------------------ */

void resetar_tarefas(void) {
    total_tarefas = 0;
}

int obter_total_tarefas(void) {
    return total_tarefas;
}

/*
 * tarefa_estado — devolve o estado de uma tarefa sem expor a estrutura
 * interna. O valor -1 sinaliza ID inexistente, permitindo ao chamador
 * distinguir entre "não existe" e "pendente" (0).
 */
int tarefa_estado(int id_tarefa) {
    for (int i = 0; i < total_tarefas; i++) {
        if (tarefas[i].id == id_tarefa) {
            return tarefas[i].concluida;
        }
    }
    return -1; /* ID não encontrado. */
}

int criar_tarefa(const char* descricao, int data_prevista) {
    /* Guard clause: capacidade máxima atingida. */
    if (total_tarefas >= MAX_TAREFAS) {
        return 0;
    }

    /* Guard clause: descrição obrigatória e data não negativa.
     * data_prevista == 0 (epoch) é aceite; -1 (N-1) é rejeitado. */
    if (!texto_valido(descricao) || data_prevista < 0) {
        return 0;
    }

    /* Guard clause: descrição não pode exceder o buffer interno. */
    if (!texto_cabe_no_buffer(descricao, sizeof(tarefas[0].descricao))) {
        return 0;
    }

    Tarefa* nova = &tarefas[total_tarefas];
    nova->id = total_tarefas + 1;

    if (!copiar_texto(nova->descricao, sizeof(nova->descricao), descricao)) {
        return 0;
    }

    nova->data_prevista = data_prevista;
    nova->concluida     = 0; /* Toda a nova tarefa começa como pendente. */
    total_tarefas++;
    return 1;
}

int concluir_tarefa(int id_tarefa) {
    for (int i = 0; i < total_tarefas; i++) {
        if (tarefas[i].id == id_tarefa) {
            tarefas[i].concluida = 1;
            return 1;
        }
    }
    return 0; /* Tarefa não encontrada. */
}

void listar_tarefas_pendentes(void) {
    printf("=== TAREFAS PENDENTES ===\n");
    if (total_tarefas == 0) {
        printf("Sem tarefas registadas.\n");
        return;
    }

    for (int i = 0; i < total_tarefas; i++) {
        if (tarefas[i].concluida == 0) {
            printf("Tarefa %d | %s | Prevista:%d\n",
                   tarefas[i].id,
                   tarefas[i].descricao,
                   tarefas[i].data_prevista);
        }
    }
}

/*
 * tarefas_gravar_csv — serializa as tarefas em formato CSV.
 * Formato: id,descricao,data_prevista,concluida
 * Inclui tarefas concluídas para preservar o histórico completo.
 */
int tarefas_gravar_csv(const char* caminho) {
    if (!caminho || caminho[0] == '\0') {
        return 0;
    }

    FILE* f = fopen(caminho, "w");
    if (!f) {
        return 0;
    }

    for (int i = 0; i < total_tarefas; i++) {
        if (fprintf(f, "%d,%s,%d,%d\n",
                    tarefas[i].id,
                    tarefas[i].descricao,
                    tarefas[i].data_prevista,
                    tarefas[i].concluida) < 0) {
            fclose(f);
            return 0;
        }
    }

    fclose(f);
    return 1;
}

/*
 * tarefas_carregar_csv — desserializa tarefas a partir de CSV.
 * Tolerante a ficheiro ausente; intolerante a linhas malformadas.
 */
int tarefas_carregar_csv(const char* caminho) {
    if (!caminho || caminho[0] == '\0') {
        return 0;
    }

    FILE* f = fopen(caminho, "r");
    if (!f) {
        resetar_tarefas();
        return 1;
    }

    resetar_tarefas();

    while (total_tarefas < MAX_TAREFAS) {
        Tarefa temporaria;
        int lidos = fscanf(f, "%d,%99[^,],%d,%d",
                           &temporaria.id,
                           temporaria.descricao,
                           &temporaria.data_prevista,
                           &temporaria.concluida);

        if (lidos == EOF) {
            break;
        }

        if (lidos != 4) {
            fclose(f);
            resetar_tarefas();
            return 0;
        }

        tarefas[total_tarefas++] = temporaria;
    }

    fclose(f);
    return 1;
}
