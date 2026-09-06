#include "../include/lista.h"
#include <stdio.h>
#include <string.h>

/*Estado interno - encapsulado, não acessível ao exterior*/
static Contacto contactos[LISTA_MAX];
static int total = 0;

int lista_adicionar(const Contacto *contacto){
    if(contacto == NULL || total >= LISTA_MAX)  return 0;

    contactos[total] = *contacto;
    total++;
    return 1;
}

void lista_mostrarTodos(void){
    int i;
    if(total == 0){
        printf("A lista está vazia.\n");
        return;
    }

    for(i = 0; i < total; i++){
        printf("--- Contacto %d ---\n", i + 1);
        contacto_mostrar(&contactos[i]);
    }
}

int lista_procurarPorNome(const char *nome){
    int i, encontrados = 0;

    if(nome == NULL) return 0;

    for(i = 0; i < total; i++){
        if(strstr(contactos[i].nome, nome) != NULL){
            contacto_mostrar(&contactos[i]);
            encontrados++;
        }
    }
    return encontrados;
}

int lista_total(void){
    return total;
}

int lista_obterTodos(Contacto destino[], int max){
    int i, quantidade;

    if(destino == NULL || max <= 0) return 0;

    quantidade = total < max ? /*true*/ total : /*false*/ max;

    for(i = 0; i < quantidade; i++){
        destino[i] = contactos[i];
    }
    return quantidade;
}