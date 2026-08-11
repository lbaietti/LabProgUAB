#include "../AF2.6/projeto_log/include/log.h"
#include <stdio.h>

static int ativo = 1; // ativo por defeito

void Log_msg(const char *mensagem){
    if (ativo) {
        printf("Log: %s\n", mensagem);
    }
}

void Log_erro(const char *erro){
    if(ativo == 1){
        printf("[ERRO] Ficheiro não encontrado");
    }
}

void Log_ativar(int estado){
    ativo = estado;

    if(estado){
        printf("LOG ativado");
    }
    else{
        printf("LOG desativado");
    }
}

