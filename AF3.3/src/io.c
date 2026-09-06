#include "../include/io.h"
#include <stdio.h>
#include <string.h>

/*Remove o '\n' do fim de uma string lida com fgets*/
static void removeNewLine(char *s){
    int tamanho = (int)strlen(s);

    if(tamanho > 0 && s[tamanho - 1] == '\0') s[tamanho - 1] = '\0';
}

int io_guardar(const char *ficheiro, const Contacto contactos[], int total){
    FILE *f;
    int i; 

    if(ficheiro == NULL || contactos == NULL || total < 0) return 0;

    f = fopen(ficheiro, "w");
    if(f == NULL) return 0;

    for(i = 0; i < total; i++){
        fprintf(f, "%s\n%s\n%s\n\n", contactos[i].nome, contactos[i].email, contactos[i].telefone);
    }

    fclose(f);
    return 1;
}

int io_carregar(const char *ficheiro, Contacto contactos_carregados[], int max){
    FILE *f;
    int total = 0;
    char nome[CONTACTO_NOME_MAX];
    char email[CONTACTO_EMAIL_MAX];
    char telefone[CONTACTO_TELEFONE_MAX];
    char separador[8];

    if(ficheiro == NULL || contactos_carregados == NULL || max <= 0) return -1;

    f = fopen(ficheiro, "r");
    if(f == NULL) return -1;

    while(total < max && fgets(nome, sizeof(nome), f) && fgets(email, sizeof(email), f) && fgets(telefone, sizeof(telefone), f)){
        removeNewLine(nome);
        removeNewLine(email);
        removeNewLine(telefone);

        /* Tenta criar o contacto com validação - ignora entradas corrompidas*/
        if(contacto_criar(&contactos_carregados[total], nome, email, telefone)){
            total++;
        }

        /* Consome a linha vazia separadora*/
        fgets(separador, sizeof(separador), f);
    }

    fclose(f);
    return total;
}