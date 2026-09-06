#include "../include/contacto.h"
#include "../include/validacao.h"
#include <stdio.h>
#include <string.h>

/* Verifica se uma string é não nula e não vazia*/
static int stringValida(const char *s){
    return s != NULL && s[0] != '\0';
}

int contacto_criar(Contacto *novo, const char *nome, const char *email, const char *telefone){
    /** Tudo o que não utilizar destes parâmetros, deverá retornar 0.
     * Que de certa forma acaba por explicitar o dever de utilizar os mesmos.
     */
    if(novo == NULL) return 0; 
    if(!stringValida(nome)) return 0;
    if(!validacao_emailValido(email)) return 0;
    if(!validacao_telefoneValido(telefone)) return 0;

    strncpy(novo->nome, nome, CONTACTO_NOME_MAX - 1);
    novo->nome[CONTACTO_NOME_MAX - 1] = '\0';

    strncpy(novo->email, email, CONTACTO_EMAIL_MAX -1);
    novo->email[CONTACTO_EMAIL_MAX - 1] = '\0';

    strncpy(novo->telefone, telefone, CONTACTO_TELEFONE_MAX - 1);
    novo->telefone[CONTACTO_TELEFONE_MAX - 1] = '\0';

    return 1;
}

void contacto_mostrar(const Contacto *contacto){
    if(contacto == NULL) return;

    printf("Nome:   %s\n", contacto->nome);
    printf("Email:   %s\n", contacto->email);
    printf("Telefone:   %s\n", contacto->telefone);
}