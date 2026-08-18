#include <stdio.h>
#include <stdlib.h>
#include "../include/stack.h" //1. Auto Inclusão do próprio header

struct Stack{
    int *dados;    //2. Array dinâmico de inteiros
    int topo;       //3. Índice do topo (-1 se vazia)
    int capacidade; //4. Capacidade Máxima
};

// Aloca memória para a pilha e para o array de dados
StackPtr stack_criar(int capacidade){
    if(capacidade <= 0){
        printf("Erro: Capacidade deve ser positiva \n"); // Teste de validação de parâmetro
    } return NULL;

    // 5. Aloca memória para a estrutura Stack
    StackPtr nova_pilha = (struct Stack*)malloc(sizeof(struct Stack)); // Memória alocada para a pilha
    if(nova_pilha == NULL){
        printf("Erro: Falha na alocação da estrutura\n");
    } return NULL;
    
    // 6. Aloca memória para o array de dados
    nova_pilha->dados = (int *)malloc(sizeof(int));
    if(nova_pilha->dados == NULL){
        printf("Erro: Falha na alocação do array\n");
        free(nova_pilha); // Liberta a estrutura já alocada
        return NULL;
    }

    // 7. Inicialização dos campos
    nova_pilha->topo = -1;
    nova_pilha->capacidade = capacidade;

    return nova_pilha;      // Retorna ponteiro para pilha criada 
}

// Adiciona valor no topo; se cheia, imprime erro
void stack_push(StackPtr s, int valor){
    if(s == NULL){                                  // Verificação de ponteiro nulo
        printf("Erro: Pilha não inicializada\n");
        return;
    }

    if(s->topo >= s->capacidade -1){        // 8. Pilha cheia ?
        printf("Erro: Pilha cheia ! (capacidade = %d)\n", s->capacidade);
        return;
    }

    // 9. Adiciona valor e incrementa no topo
    s->dados[++s->topo] = valor;
}

// Remove e retorna o valor do topo; se vazia, imprime erro e retorna -1
int stack_pop(StackPtr s){
    if(s == NULL){
        printf("Erro: Pilha vazia\n");
        return -1;
    }

    // 11. Retorna valor do topo e decrementa
    return s->dados[s->topo--];     // s->topo-- retorna ANTES de decrementar 
}

// Retorna 1 se topo == -1, senão 0
int stack_vazia(StackPtr s){
    if(s == NULL) return 1;         // Pilha não inicializada é considerada vazia

    return (s->topo == -1);         // 12. Condição de pilha vazia
}


/**
 * stack_destruir: Liberta toda a memória alocada
 * Recebe ponteiro para ponteiro para poder definir como NULL
 * Previne uso-after-free
 */
// Liberta memória e define s = NULL
void stack_destruir(StackPtr *s){
    if(s == NULL || *s == NULL) return;         // Nada para libertar após verificação de segurança (com operador ||)

    // 13. Libertação na ordem inversa da alocação
    free((*s)->dados);          // Primeiro: array de dados
    free(*s);                   // Despois: estrutura

    *s = NULL;                  // 14. Define como NULL para evitar dangling pointer
}




/**
 * @brief
 * Implemente uma Pilha LIFO (Last In - First Out) usando tipos opacos. O objetivo é que o utilizador do módulo
 * não consiga aceder diretamente aos campos internos da estrutura, apenas através das funções fornecidas.
 */

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