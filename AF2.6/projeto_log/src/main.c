#include "../AF2.6/projeto_log/include/log.h"
#include <stdio.h>

int main(){
    //Teste 1: Log ativo por padrão 
    printf("=== Teste1: Log ativo por padrão === \n");
    Log_msg("Sistema Iniciado \n");
    Log_erro("Ficheiro não encontrado \n");
    Log_msg("Operação Concluída \n");

    //Teste 2: Desativar o Log
    printf("=== Teste2: Desativar o Log === \n");
    Log_ativar(0); // Desativa o log

    // Estas mensagens não devem aparecer
    Log_msg("Esta mensagem não deve aparecer \n");
    Log_erro("Este erro não deve aparecer \n");

    //Teste 3: Reativar o Log
    printf("=== Teste3: Reativar o Log === \n");
    Log_ativar(1); // Reativa o log

    // Estas mensagens devem aparecer
    Log_msg("Log reativado com sucesso\n");
    Log_erro("Teste final de erro \n");

    // Teste 4: Estad Inválido (Robustez)
    printf("=== Teste4: Estado Inválido === \n");
    Log_ativar(42); // Valor inválido, mas deve ser tratado como "ativo"
    Log_msg("Teste com estado inválido, mas log deve funcionar \n");

    return 0;
}