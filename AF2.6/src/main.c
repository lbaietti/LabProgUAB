#include "../include/log.h"

int main(){
    /*Demonstração completa das funcionalidades*/

    // Teste 1: Log ativo por padrão 
    printf("==== Teste 1: Log ativo (padrão) ====\n");
    Log_msg("Sistema iniciado");
    Log_erro("Ficheiro não encontrado");
    Log_msg("Operação Concluída");

    // Teste 2: Desativar o log 
    printf("\n==== Teste 2: Desativar Log ====\n");
    Log_ativar(0);

    // Teste 3: Reativar Log 
    printf("\n ==== Teste 3: Reativar Log ====\n");
    Log_ativar(0);
    printf("reativando...\n");
    Log_ativar(1);
    Log_msg("Log reativado com sucesso");
    Log_erro("Teste final de erro");

    // Teste 4: Estado Inválido
    printf("\n ==== Teste 4: Estado Inválido ====\n");
    Log_ativar(42); /* Valor inválido mas tratado como ativo, pois o que for =! 0 em C é tratado 
    como verdadeiro (ativado), e 0 é tratado como falso (desativado).... valor booleano*/
    Log_msg("Teste com estado inválido");
}