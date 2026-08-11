#include "validacao.h"
#include<stdio.h>



static int i, validos = 0;


void validarDados(int *arr, int n){
    for(i = 0; i < n; i++){
        if(arr[i] >= 0 && arr[i] <= 100) validos++;
    }
}