#ifndef IO_H
#define IO_H

#include "contacto.h"

int io_guardar(const char *ficheiro, const Contacto contactos[], int total);

int io_carregar(const char *ficheiro, Contacto contactos[], int max);



#endif