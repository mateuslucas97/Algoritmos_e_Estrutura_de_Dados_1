#include <stdio.h>
#include <stdlib.h>
#define MAX 1000000

/*  Esse exercicio foi resolvido usando como base esses enderços na internet
    https://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html
    https://www.ime.usp.br/~fmario/mac2166/challenge/fatorial.html
    https://www.youtube.com/watch?v=XPYZzv_lEsQ
 */

void resultadooperacao(int *r, int TAM);
int fatorial(int n, int *resultado, int TAM);

int main(){
    int n,i, TAM = 0, *r;
    printf("Digite um numero inteiro: ");
    scanf(" %d", &n);
    if(n == 1 || n ==0){ // o fatorial de 0 e/ ou 1 é 1
        printf("1");
    }
    else{
        r = calloc(MAX, sizeof(int)); //aloca um espaco em memoria para mostrar o resultado
        r[0] = 1; // o resultado é transformado em um vetor e inicializado com 1
        for(i = 0; i <= n ; i++){
            if(i > 1){
                TAM = fatorial(i, r, TAM);
            }
        }
        printf("Resultado: ");
        resultadooperacao(r, TAM);
    }
    free(r);
    return 0;
}
//procedimento para exibir o resultado na tela
void resultadooperacao(int *r, int TAM){
    int i;
    for(i = TAM; i >= 0; i--){
        printf("%d", r[i]);
    }
}

/*essa função realiza o calculo propriamente dito
como estamos lidando com numeros muito grandes, a operação é feita com numeros de bits
mairoes que o usual e armazenados em um vetor previamente alocado na memoŕia
para essa ocasiao*/
int fatorial(int n, int *resultado, int TAM){
    int i, res = 0, op;
    //aqui é feito o calculo do numero transformado em vetor
    // pois aqui é feito a multiplicação direta de um num de dois algarismos
    for(i = 0; i <= TAM; i++){
        op = resultado[i]*n + res;
        res = op / 10;
        resultado[i] = op % 10;
    }
    while(res != 0){
        resultado[i] = res % 10;
        res = res / 10;
        i++;
    }
    i--;
    return i;
}
