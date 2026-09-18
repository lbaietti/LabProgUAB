#include "temperaturas.h"
#include <stdio.h>

#include <assert.h>

void test_registar_temperatura(){
    float lista[3] = {10.0f, 20.0f, 30.0f};
    int obtido, esperado;

    /*caso válido [ramo: caminho de sucesso]*/
    obtido = registar_temperatura(lista, 3, 1, 27.5f);
    esperado = 1;

    if(obtido != esperado)
        printf("FALHA: registar válido esperado %d, obtido %d\n", esperado, obtido);
    assert(obtido == esperado);

    /*Valores limite [primeiro e último índice]*/
    if(registar_temperatura(lista, 3, 0, 10.0f) != 1)
        printf("FALHA: Primeiro elemento retorna valor incorrecto, valor esperado %d, obtido %d\n", esperado, obtido);
    if(registar_temperatura(lista, 3, 2, 30.0f) != 1)
        printf("FALHA: Último elemento retorna valor incorrecto, valor esperado %d, obtido %d\n", esperado, obtido);
    
    /*pré-condição violada: lista NULL -> retorna 0*/
    if(registar_temperatura(NULL, 3, 0, 10.0f) != 0)
        printf("Erro: lista NULL deveria retorna 0\n");

    /*pré-condição violada: índice maior que capacidade*/
    if(registar_temperatura(lista, 3, 4, 40.0f) != 0)
        printf("Erro: índice > capacidade\n");
    
    /*pré-condição violada: capacidade <= 0 -> retorna 0*/
    if(registar_temperatura(lista, 0, 0, 10.0f) != 0)
        printf("Erro: capacidade <= 0 deveria retornar 0\n");

}

void test_media_temperaturas(){
    float lista[3] = {10.0f, 20.0f, 30.0f};
    float res;
    int obtido, esperado;

    /*caso válido [ramo: caminho de sucesso]*/
    obtido = media_temperaturas(lista, 3, &res);
    esperado = 1;
    
    if(obtido != esperado)
        printf("FALHA: registar válido esperado %d, obtido %d\n", esperado, obtido);
    assert(obtido == esperado);
    assert(res = 20.0f);

    /*limite: n=1 [valor limite]*/
    obtido = media_temperaturas(lista, 1, &res);

    if(obtido != 1)
        printf("FALHA: media n=1, esperado 1, obtido %d\n", obtido);
    assert(obtido == 1);
    assert(res = 10.0f);

    /*erro: lista NULL [caso de erro - ramo condicional]*/
    obtido = media_temperaturas(NULL, 3, &res);

    if(obtido != 0)
        printf("FALHA: lista NULL esperado 0, resultado obtido: %d\n", obtido);
    assert(obtido == 0);

    /*erro: resultado NULL [caso de erro - pré-condição não validada no código original]*/
    obtido = media_temperaturas(lista, 3, NULL);
    
    if(obtido != 0)
        printf("FALHA: resultado NULL esperado 0, obtido %d\n", obtido);
    assert(obtido == 0);
}

int main(){
    printf("    ---- TESTE DE REGISTO DE TEMPERATURA ----   \n");
    test_registar_temperatura();

    printf("    ---- TESTE DE MÉDIA DA TEMPERATURA ----     \n");
    test_media_temperaturas();

    printf("    TESTES CONCLUÍDOS   \n");
    return 0;
}