//Refatore a seguinte função dividindo-a em funções auxiliares apropriadas:

void processarDados(int *arr, int n) {
    int i, j, temp, validos = 0;
    /* validação */
    for(i = 0; i < n; i++) {
        if(arr[i] >= 0 && arr[i] <= 100) validos++;
    }
    /* ordenação */
    for(i = 0; i < n-1; i++) {
        for(j = 0; j < n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    /* impressão */
    printf("Validos: %d\n", validos);
    for(i = 0; i < n; i++) printf("%d ", arr[i]);
}