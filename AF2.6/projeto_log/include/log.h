#ifndef LOG_H
#define LOG_H   

// Crie um módulo de log que permite registar mensagens e erros. O módulo deve ter um controlo interno para ativar/desativar o log.

void Log_msg(const char *mensagem);
void Log_erro(const char *erro);
void Log_ativar(int estado); //1 ativo e 0 inativo  

#endif