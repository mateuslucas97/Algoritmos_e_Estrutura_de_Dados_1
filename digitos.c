#include <stdio.h>

int Digitos(int N);

int main(){
    int N;
    printf("Digite um numero inteiro: ");
    scanf("%d", &N);
    printf("Resultado: %d", Digitos(N));
    return 0;
}

int Digitos(int N){
    int cont = 1;

    if (N >= 10){
       N = N/ 10;
       cont = cont + Digitos(N);
    }

    return cont;
}
