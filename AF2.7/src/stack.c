#include <stdio.h>
#include "../include/stack.h"

struct Stack{
    int *dados;     // Array dinâmico de inteiros
    int topo;       // Índice do topo (-1 se vazia)
    int capacidade; // Capacidade Máxima
};

// Aloca memória para a pilha e para o array de dados
StackPtr stack_criar(int capacidade);

// Adiciona valor no topo; se cheia, imprime erro
void stack_push(StackPtr s, int valor);

// Remove e retorna o valor do topo; se vazia, imprime erro e retorna -1
int stack_pop(StackPtr s);

// Retorna 1 se topo == -1, senão 0
int stack_vazia(StackPtr s);

// Liberta memória e define s = NULL
void stack_destruir(StackPtr *s);




/**
 * @note
 * 1. A definição completa da estrutura Stack (campos internos: dados, topo, capacidade)
 * 2. Implementação de todas as cinco funções declaradas em stack.h
 * 3. Gestão correta de memória dinâmica (usar malloc/free)
 * 4. Tratamento de erros (pilha cheia / vazia)
 */




/**
 * @attention 
 * A estrutura deve estar definida APENAS em stack.c, não em stack.h;
 * Todas as funções devem funcionar corretamente;
 * Gestão de memória sem leaks (verificar com valgrind se disponível);
 * Mensagens de erro apropriadas em caso de pilha cheia/vazia
 * O código deve compilar: gcc stack.c main.c -o teste_pilha
 */