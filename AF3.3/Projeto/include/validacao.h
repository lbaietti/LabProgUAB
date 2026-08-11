#ifndef VALIDACAO_H
#define VALIDACAO_H

/*
* Verifica se um endereço de email tem formato válido.
* Critério mínimo: contém exactamente um '@' e pelo menos um '.' após o '@'.
*
* Parâmetros:
*    email - string a verificar (não pode ser NULL)
*
* Retorna:
*    1 se válido, 0 caso contrário
**/

int validacao_emailValido(const char *email);

/*
* Verifica se um número de telefone tem formato válido.
* Critério: apenas dígitos e opcionalmente '+' no início, entre 9 e 15 caracteres.
*
* Parâmetros:
*   telefone - string a verificar (não pode ser NULL)
*
* Retorna: 
*   1 se válido, 0 caso contrário
*/
int validacao_telefoneValido(const char *telefone);

#endif