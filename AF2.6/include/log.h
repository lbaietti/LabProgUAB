#ifndef LOG_H
#define LOG_H

/**
 * @param mensagem Texto da mensagem a registrar
 */
void Log_msg(const char *mensagem);

/**
 * @param erro Texto do erro a registar
 */
void Log_erro(const char *erro);

/**
 * @param estado 1 para ativar, 0 para desativar
 */
void Log_ativar(int estado); // 1 = ativo, 0 = inativo

#endif