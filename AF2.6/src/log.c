#include<stdio.h>
#include "../include/log.h"

static int ativo = 1; // inicialmente ativo


/**
 * Implementação: Registra mensagem apenas se log estiver ativo
 * Princípio: Ocultação de informação - cliente não vê a variável 'ativo'
 */
void Log_msg(const char *mensagem){
    if(ativo){
        printf("%s\n", mensagem); // Imprime apenas se ativo
    }
}

/**
 * Implementação: Registra erro com prefixo especial
 * Mesmo princípio de ocultação: estado controlado internamente
 */
void Log_erro(const char *erro){
    if(ativo == 1){
        printf("[ERRO] %s\n", erro);
    }
}

/**
 * Implementação: função setter para controlar estado
 * Única forma de modificar a variável privada 'ativo' de fora
 * Exemplo de encapsulamento: acesso controlado via função
 * Log_ativar() imprime mensagens diretamente é uma decisão de design, porque a função mistura controlo de estado com output
 * Não é errado, mas não é a única opção.
 */
void Log_ativar(int estado){
    ativo = estado;

    if(estado){
        Log_msg("Log ativado");
    } 
    else{
        printf("Log desativado\n");
    }
}