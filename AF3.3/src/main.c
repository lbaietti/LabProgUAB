#include <stdio.h>
#include "../include/contacto.h"
#include "../include/lista.h"
#include "../include/io.h"

#define FICHEIRO "contactos.txt"

int main(void){
    Contacto c;     // contacto temporário para criação e validação
    Contacto buffer[100];       // array auxiliar para operações de ficheiro
    int total, encontrados;

    /* Criação e adição de contactos válidos */
    if (contacto_criar(&c, "Ana Silva", "ana@email.com", "912345678"))
        lista_adicionar(&c);

    if (contacto_criar(&c, "Bruno Costa", "bruno@exemplo.pt", "+351961234567"))
        lista_adicionar(&c);

    /* Email inválido — deve ser rejeitado por contacto_criar */
    if (!contacto_criar(&c, "Carlos", "email-invalido", "910000000"))
        printf("Contacto rejeitado: email inválido.\n");

    printf("\n=== Todos os contactos ===\n");
    lista_mostrarTodos();

    printf("\n=== Pesquisa por 'Silva' ===\n");
    encontrados = lista_procurarPorNome("Silva");
    printf("Encontrados: %d\n", encontrados);

    /* Guardar lista em ficheiro usando lista_obterTodos */
    total = lista_obterTodos(buffer, 100);
    if (io_guardar(FICHEIRO, buffer, total))
        printf("\nGuardados %d contactos em '%s'.\n", total, FICHEIRO);

    /* Recarregar do ficheiro e mostrar */
    total = io_carregar(FICHEIRO, buffer, 100);
    if (total >= 0) {
        int i;
        printf("\n=== Recarregados do ficheiro (%d) ===\n", total);
        for (i = 0; i < total; i++)
            contacto_mostrar(&buffer[i]);
    }

    return 0;
}