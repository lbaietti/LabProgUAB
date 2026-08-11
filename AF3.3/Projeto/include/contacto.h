#ifndef CONTACTO_H
#define CONTACTO_H

#define CONTACTO_NOME_MAX 100
#define CONTACTO_EMAIL_MAX 100
#define CONTACTO_TEL_MAX 20

typedef struct {
    char nome[CONTACTO_NOME_MAX];
    char email[CONTACTO_EMAIL_MAX];
    char telefone[CONTACTO_TEL_MAX];
} Contacto;

/**
 * Inicializa os contactos com os dados fornecidos.
 * Valida o email e o telefone antes de aceitar.
 * 
 * Parâmetros:
 *  novo - Ponteiro para Contacto a preencher (não pode ser NULL)
 *  nome - nome do Contacto (não pode ser NULL ou vazio)
 *  email - endereço de email (validado)
 *  telefone - número de telefone (validado)
 * 
 * Retorna: 
 *  1 se o contacto for criado com sucesso, 0 se tiver algum dado inválido
 */

 int contacto_criar(Contacto *novo, const char *nome, const char *email, const char *telefone);

 /**
  * Imprime os dados de um contacto no écran
  * 
  * Parâmetros:
  *     contacto - ponteiro para Contacto a mostrar (não pode ser NULL)
  */

void contacto_mostrar(const Contacto *contacto);

#endif