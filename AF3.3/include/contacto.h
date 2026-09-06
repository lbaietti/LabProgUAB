#ifndef CONTACTO_H
#define CONTACTO_H

#define CONTACTO_NOME_MAX 100
#define CONTACTO_EMAIL_MAX 50
#define CONTACTO_TELEFONE_MAX 15        

typedef struct{
    char nome[CONTACTO_NOME_MAX];
    char email[CONTACTO_EMAIL_MAX];
    char telefone[CONTACTO_TELEFONE_MAX];
} Contacto;

int contacto_criar(Contacto *novo, const char *nome, const char *email, const char* telefone);

void contacto_mostrar(const Contacto *contacto);



#endif