#ifndef VALIDACAO_H
#define VALIDACAO_H

/**
 * Tem de retornar 1 caso válido, caso o contrário retornará 0
 * Critério mínimo: contém exactamente um @ e um "." após o @
*/
int validacao_email(const char *email);


/**
 * Critério mínimo: Apenas dígitos e opcionamente "+" no início.
 * Tem entre 9 a 15 caracteres
 */
int validacao_telefone(const int *telefone);


#endif