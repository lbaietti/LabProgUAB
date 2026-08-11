/*
 * plantas.c — Módulo de gestão de plantas do GreenTrack
 *
 * Responsabilidade: manter uma colecção em memória de plantas com as suas
 * propriedades, e disponibilizar operações de adição, consulta e
 * serialização/deserialização em CSV.
 *
 * Decisão de armazenamento: array estático de MAX_PLANTAS elementos.
 * Alternativa considerada: lista ligada dinâmica — rejeitada por aumentar
 * a complexidade de gestão de memória sem benefício real na dimensão
 * esperada do projecto (≤ 100 plantas).
 *
 * Atribuição de IDs: sequential (id = posição + 1). Consequência: após
 * um carregamento de CSV os IDs são preservados, mas uma eventual remoção
 * de registos no ficheiro não é suportada por esta versão.
 */

#include "plantas.h"

#include <stdio.h>
#include <string.h>

/* Armazenamento interno: não exposto fora deste módulo. */
static Planta plantas[MAX_PLANTAS];
static int    total_plantas = 0;

/* ------------------------------------------------------------------ */
/* Funções auxiliares internas (sem visibilidade externa)              */
/* ------------------------------------------------------------------ */

/*
 * texto_valido — verifica se o ponteiro não é NULL e o texto não é vazio.
 * Guard clause reutilizada em múltiplas validações de entrada.
 */
static int texto_valido(const char* texto) {
    return texto != NULL && texto[0] != '\0';
}

/*
 * texto_cabe_no_buffer — verifica se o texto cabe no buffer destino.
 * Usa < em vez de <= porque snprintf reserva sempre um '\0' final.
 */
static int texto_cabe_no_buffer(const char* texto, size_t capacidade) {
    if (texto == NULL) {
        return 0;
    }
    return strlen(texto) < capacidade;
}

/*
 * copiar_texto — copia origem para destino com verificação de capacidade.
 * Devolve 0 se o texto não couber, evitando truncagem silenciosa.
 */
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

void resetar_plantas(void) {
    total_plantas = 0;
}

int obter_total_plantas(void) {
    return total_plantas;
}

Planta* obter_planta_por_id(int id) {
    for (int i = 0; i < total_plantas; i++) {
        if (plantas[i].id == id) {
            return &plantas[i];
        }
    }
    return NULL;
}

void atualizar_ultima_rega(int id_planta, int data_rega) {
    Planta* planta = obter_planta_por_id(id_planta);
    if (!planta) {
        return; /* ID inexistente — ignorar silenciosamente. */
    }
    planta->ultima_rega = data_rega;
}

int adicionar_planta(const char* nome,
                     const char* especie,
                     const char* data_plantio,
                     int intervalo_rega) {
    /* Guard clause: capacidade máxima atingida. */
    if (total_plantas >= MAX_PLANTAS) {
        return 0;
    }

    /* Guard clause: campos de texto obrigatórios. */
    if (!texto_valido(nome) || !texto_valido(especie) || !texto_valido(data_plantio)) {
        return 0;
    }

    /* Guard clause: intervalo deve ser positivo (mínimo 1 dia). */
    if (intervalo_rega <= 0) {
        return 0;
    }

    /* Guard clause: textos não podem exceder os buffers da estrutura. */
    if (!texto_cabe_no_buffer(nome, sizeof(plantas[0].nome)) ||
        !texto_cabe_no_buffer(especie, sizeof(plantas[0].especie)) ||
        !texto_cabe_no_buffer(data_plantio, sizeof(plantas[0].data_plantio))) {
        return 0;
    }

    /* Preencher o próximo slot disponível. */
    Planta* nova = &plantas[total_plantas];
    nova->id = total_plantas + 1;

    if (!copiar_texto(nova->nome, sizeof(nova->nome), nome) ||
        !copiar_texto(nova->especie, sizeof(nova->especie), especie) ||
        !copiar_texto(nova->data_plantio, sizeof(nova->data_plantio), data_plantio)) {
        return 0;
    }

    nova->intervalo_rega = intervalo_rega;
    nova->ultima_rega    = 0; /* Sem rega registada ainda. */
    total_plantas++;
    return 1;
}

void listar_plantas(void) {
    printf("=== PLANTAS ===\n");
    if (total_plantas == 0) {
        printf("Sem plantas registadas.\n");
        return;
    }

    for (int i = 0; i < total_plantas; i++) {
        printf("ID:%d | Nome:%s | Especie:%s | Plantio:%s | Intervalo:%d | Ultima rega:%d\n",
               plantas[i].id,
               plantas[i].nome,
               plantas[i].especie,
               plantas[i].data_plantio,
               plantas[i].intervalo_rega,
               plantas[i].ultima_rega);
    }
}

/*
 * plantas_gravar_csv — serializa todas as plantas em formato CSV.
 *
 * Formato de cada linha: id,nome,especie,data_plantio,intervalo_rega,ultima_rega
 * O ficheiro é sobrescrito a cada gravação (sem append), garantindo que
 * remoções futuras de registos são correctamente reflectidas em disco.
 */
int plantas_gravar_csv(const char* caminho) {
    if (!texto_valido(caminho)) {
        return 0;
    }

    FILE* f = fopen(caminho, "w");
    if (!f) {
        return 0;
    }

    for (int i = 0; i < total_plantas; i++) {
        if (fprintf(f, "%d,%s,%s,%s,%d,%d\n",
                    plantas[i].id,
                    plantas[i].nome,
                    plantas[i].especie,
                    plantas[i].data_plantio,
                    plantas[i].intervalo_rega,
                    plantas[i].ultima_rega) < 0) {
            fclose(f);
            return 0;
        }
    }

    fclose(f);
    return 1;
}

/*
 * plantas_carregar_csv — desserializa plantas a partir de um ficheiro CSV.
 *
 * Tolerância: se o ficheiro não existir, o módulo é inicializado vazio
 * e a função devolve 1 (sem erro) — comportamento correcto na primeira
 * execução do programa.
 * Intolerância: se o CSV existir mas tiver um registo malformado,
 * devolve 0 e reinicia o estado para evitar dados parcialmente carregados.
 */
int plantas_carregar_csv(const char* caminho) {
    if (!texto_valido(caminho)) {
        return 0;
    }

    FILE* f = fopen(caminho, "r");
    if (!f) {
        resetar_plantas(); /* Ficheiro ausente: começar com lista vazia. */
        return 1;
    }

    resetar_plantas();

    while (total_plantas < MAX_PLANTAS) {
        Planta temporaria;
        int lidos = fscanf(f,
                           "%d,%49[^,],%49[^,],%10[^,],%d,%d",
                           &temporaria.id,
                           temporaria.nome,
                           temporaria.especie,
                           temporaria.data_plantio,
                           &temporaria.intervalo_rega,
                           &temporaria.ultima_rega);

        if (lidos == EOF) {
            break; /* Fim de ficheiro normal. */
        }

        if (lidos != 6) {
            /* Linha malformada: rejeitar todo o ficheiro. */
            fclose(f);
            resetar_plantas();
            return 0;
        }

        plantas[total_plantas++] = temporaria;
    }

    fclose(f);
    return 1;
}
