#include <stdio.h>
#include "../include/geometria.h"

int main(){
    double num;

    printf("Insira o Raio de um Círculo (r = %.3f): %.2f\n",num, areaCirculo(5.0));
    scanf("%lf", &num);
    printf("Insira a Base e a Altura de um Retângulo (%f x %.3f): %.2f", num, num, areaRetangulo(3.0, 4.0));
    scanf("%lf", &num);
}