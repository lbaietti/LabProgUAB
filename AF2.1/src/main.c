#include <stdio.h>
#include "../include/calculadora.h"

int main(void){

    int opcao;
    int num;

    do{
        printf("\n========MENU==========\n");
        printf("Digite a opeação que deseja realizar: \n");
        printf("1. Soma\n");
        printf("2. Subtração\n");
        printf("3. Divisão\n");
        printf("4. Multiplicação\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("Insira os números que pretende somar: \n");
                scanf("%d", &num);
                scanf("%d", &num);
                somar(num, num);
                printf("A operação resultou o valor: %d\n", num);
                break;
            case 2:
                printf("Insira os números que pretende subtrair: \n");
                scanf("%d", &num);
                scanf("%d", &num);
                subtrair(num, num);
                printf("A operação resultou o valor: %d\n", num);
                break;
            case 3:
                printf("Insira os números que pretende somar: \n");
                scanf("%d", &num);
                scanf("%d", &num);
                dividir(num, num);
                printf("A operação resultou o valor: %d\n", num);
                break;
            case 4:
                printf("Insira os números que pretende somar: \n");
                scanf("%d", &num);
                scanf("%d", &num);
                multiplicar(num, num);
                break;
        }
    } while(opcao != 0);
    return 0;
}