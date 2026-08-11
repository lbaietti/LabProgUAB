/*
 * main.c — Ponto de entrada do GreenTrack
 *
 * Responsabilidade: interacção com o utilizador através de um menu
 * em loop. Delega toda a lógica de negócio aos módulos especializados
 * (plantas, regas, tarefas) e a persistência ao módulo persistencia.
 *
 * Decisão de I/O: leitura via fgets + strtol em vez de scanf directamente,
 * para evitar que entradas inválidas deixem o stdin num estado indefinido.
 * Alternativa considerada: scanf com %d — rejeitada porque não consome o
 * restante da linha em caso de erro, causando loops infinitos no menu.
 *
 * Gravação automática: cada operação que modifica dados chama guardar_dados()
 * imediatamente a seguir, garantindo que o estado fica persistido sem
 * depender de que o utilizador escolha a opção 8 explicitamente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plantas.h"
#include "regas.h"
#include "tarefas.h"
#include "persistencia.h"

/* ------------------------------------------------------------------ */
/* Funções auxiliares de leitura de input                              */
/* ------------------------------------------------------------------ */

/*
 * ler_inteiro — lê uma linha do stdin e converte para inteiro.
 *
 * Rejeita: linhas vazias, valores não numéricos, e linhas com caracteres
 * extra após o número (ex: "3abc" é recusado). Devolve 1 em caso de
 * sucesso e 0 em caso de falha, sem deixar o stdin em estado inválido.
 */
static int ler_inteiro(const char* prompt, int* valor) {
    char  linha[64];
    char* fim = NULL;
    long  convertido;

    if (!prompt || !valor) {
        return 0;
    }

    printf("%s", prompt);
    if (!fgets(linha, sizeof(linha), stdin)) {
        return 0;
    }

    convertido = strtol(linha, &fim, 10);
    if (fim == linha) {
        return 0; /* Nenhum dígito lido. */
    }

    /* Consumir espaços em branco finais antes de verificar fim da string. */
    while (*fim == ' ' || *fim == '\t' || *fim == '\n' || *fim == '\r') {
        fim++;
    }

    if (*fim != '\0') {
        return 0; /* Caracteres extra após o número. */
    }

    *valor = (int)convertido;
    return 1;
}

/*
 * ler_texto — lê uma linha do stdin para um buffer com limite de capacidade.
 * Remove o '\n' final e rejeita strings vazias (devolve 0 se vazia).
 */
static int ler_texto(const char* prompt, char* destino, size_t capacidade) {
    if (!prompt || !destino || capacidade == 0) {
        return 0;
    }

    printf("%s", prompt);
    if (!fgets(destino, (int)capacidade, stdin)) {
        return 0;
    }

    destino[strcspn(destino, "\n")] = '\0';
    return destino[0] != '\0'; /* Retorna 0 se o utilizador não escreveu nada. */
}

/* ------------------------------------------------------------------ */
/* Menu principal                                                       */
/* ------------------------------------------------------------------ */

static void mostrar_menu(void) {
    printf("\n=== GreenTrack ===\n");
    printf("1. Listar plantas\n");
    printf("2. Adicionar planta\n");
    printf("3. Registar rega\n");
    printf("4. Criar tarefa\n");
    printf("5. Listar tarefas pendentes\n");
    printf("6. Listar regas\n");
    printf("7. Concluir tarefa\n");
    printf("8. Guardar dados\n");
    printf("9. Sair\n");
}

/* ------------------------------------------------------------------ */
/* Ponto de entrada                                                     */
/* ------------------------------------------------------------------ */

int main(void) {
    int opcao = 0;

    /* Carregar o estado persistido; erros são tolerados na primeira execução. */
    carregar_dados();

    do {
        mostrar_menu();

        if (!ler_inteiro("Opcao: ", &opcao)) {
            printf("Entrada invalida.\n");
            continue;
        }

        if (opcao == 1) {
            listar_plantas();

        } else if (opcao == 2) {
            char nome[50];
            char especie[50];
            char data_plantio[11];
            int  intervalo_rega;

            if (!ler_texto("Nome: ", nome, sizeof(nome)) ||
                !ler_texto("Especie: ", especie, sizeof(especie)) ||
                !ler_texto("Data de plantio (DD/MM/AAAA): ", data_plantio, sizeof(data_plantio)) ||
                !ler_inteiro("Intervalo de rega (dias): ", &intervalo_rega)) {
                printf("Dados invalidos.\n");
                continue;
            }

            if (adicionar_planta(nome, especie, data_plantio, intervalo_rega)) {
                if (!guardar_dados()) {
                    printf("Planta adicionada, mas ocorreu erro ao guardar os dados.\n");
                } else {
                    printf("Planta adicionada com sucesso.\n");
                }
            } else {
                printf("Nao foi possivel adicionar a planta.\n");
            }

        } else if (opcao == 3) {
            int id_planta;
            int data_rega;
            int quantidade_agua;

            if (!ler_inteiro("ID da planta: ", &id_planta) ||
                !ler_inteiro("Data da rega (timestamp): ", &data_rega) ||
                !ler_inteiro("Quantidade de agua (ml): ", &quantidade_agua)) {
                printf("Dados invalidos.\n");
                continue;
            }

            if (registar_rega(id_planta, data_rega, quantidade_agua)) {
                if (!guardar_dados()) {
                    printf("Rega registada, mas ocorreu erro ao guardar os dados.\n");
                } else {
                    printf("Rega registada com sucesso.\n");
                }
            } else {
                printf("Nao foi possivel registar a rega.\n");
            }

        } else if (opcao == 4) {
            char descricao[100];
            int  data_prevista;

            if (!ler_texto("Descricao: ", descricao, sizeof(descricao)) ||
                !ler_inteiro("Data prevista (timestamp): ", &data_prevista)) {
                printf("Dados invalidos.\n");
                continue;
            }

            if (criar_tarefa(descricao, data_prevista)) {
                if (!guardar_dados()) {
                    printf("Tarefa criada, mas ocorreu erro ao guardar os dados.\n");
                } else {
                    printf("Tarefa criada com sucesso.\n");
                }
            } else {
                printf("Nao foi possivel criar a tarefa.\n");
            }

        } else if (opcao == 5) {
            listar_tarefas_pendentes();

        } else if (opcao == 6) {
            listar_regas();

        } else if (opcao == 7) {
            int id_tarefa;

            if (!ler_inteiro("ID da tarefa: ", &id_tarefa)) {
                printf("Dados invalidos.\n");
                continue;
            }

            if (concluir_tarefa(id_tarefa)) {
                if (!guardar_dados()) {
                    printf("Tarefa concluida, mas ocorreu erro ao guardar os dados.\n");
                } else {
                    printf("Tarefa concluida com sucesso.\n");
                }
            } else {
                printf("Tarefa nao encontrada.\n");
            }

        } else if (opcao == 8) {
            if (guardar_dados()) {
                printf("Dados guardados com sucesso.\n");
            } else {
                printf("Erro ao guardar dados.\n");
            }

        } else if (opcao == 9) {
            printf("A sair...\n");

        } else {
            printf("Opcao invalida.\n");
        }

    } while (opcao != 9);

    return 0;
}
