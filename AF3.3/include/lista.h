#ifndef LISTA_H 
#define LISTA_H

#include "contacto.h"

#define LISTA_MAX 100

int lista_adicionar(const Contacto *contacto);

void lista_mostrarTodos(void);

int lista_procurarPorNome(const char *nome);

int lista_total(void);

int lista_obterTodos(Contacto destino[], int max);




#endif