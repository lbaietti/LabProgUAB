#include <stdio.h>

/*Calcula a soma dos pares positivos*/


/**
* @attention
* 1. Problemas de nomenclaturas... variáveis com nomes não intuitivos
* 2. Nested Code (Aninhamento excessivo). O código possui ciclo condicional
* @todo
* -> Refatorar o código de forma a reduzir o nesting 
* -> Renomear variáveis, de forma com que quem faça a leitura possa compreender melhor
*/

/*int p(int *a, int n){
    int i, s = 0;
    for(i = 0; i < n; i++){
        if(a[i] > 0){
            if(a[i] % 2 == 0){
                s += a[i];
            }
        }
    }
    return s;
}*/

/* Imprime os valores do array*/

/**
 * @attention
 * 3. Novamente, nesting excessivo 
 * 4. Variáveis com nomes pouco intuitivos
 * 5. variável int i foi declarada fora do ciclo no entanto só foi utilizada dentro do mesmo. 
 * 6. ambas as funções, para além de terem nomes vagos, tem parâmetros com nomes iguais, 
 * do qual não causará problemas de compilação, mas à nível de ligibilidade e organização de código
 * isto acaba por ser categorizado como um problema crítico. 
 */

/*int f(int *a, int n, int lim){
    int i, c = 0; // Não há a necessidade de declaração do i sendo que ele não será utilizado fora do bloco for()
    for(i = 0; i < n; i++){
        if(a[i] > 0){
            if(a[i] <= lim){
                printf("%d\n", a[i]);
                c++;
            }
        }
    }
    return c;
}

int main(){
    int v[] = {-3, 4, 7, 8, -1, 10, 2, 15};
    int r = p(v, 8);
    printf("Resultado: %d\n", r);

    int x = f(v, 8, 10);
    printf("Contagem: %d\n", x);

    return 0;
}*/

/**
 * @note
 * 7. Funções não foram prototipadas, mesmo com 8. código monotílitco poderiam haver protótipos das mesmas.
 * 9. O código possui comentários vagos, sem justificações e explicações efetivas.
 * @todo
 * -> Modularizar o programa, separando interface de implementação.
 * -> Melhorar a legibilidade do código, desenvolvendo uma melhor nomenclatura das variáveis, parâmetros e funções
 * -> Inserir comentários que expliquem propósito.
 * 
 * @brief
 * Questão para refletir:
 * - Quando é que uma função de uma linha justifica existir como
 * função separada ?
 */

