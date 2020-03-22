#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITY 10000

/* este exercicio foi feito usando a inplementação do  algoritmo
de Dijkstra implementador por ZIVIANI (dijkstramatriz [c]):
http://www2.dcc.ufmg.br/livros/algoritmos/implementacoes-07.php

e com ajuda de alocação dinamica de memoria implementado
com ajuda de alunos da computação*/

typedef struct{
    char cidade[21];
}string;

void Dijkstra(int indexCidadeOrigem, int indexCidadeDestino, int **matriz, int qtdeCidades, int *visitadoAntes, int *menorDistancia);
int** Aloca_matriz(int **matriz, int lin, int col);
int percorreCidades(string *demaisCidades, char *cidade, int qtdeCidades);


int main(){

string *cidade1, *cidade2, *demaisCidades, cidadeOrigem, cidadeDestino;
char nomeArq[21];
int **ponteiroMatriz;
int numeroCaminhos, menorDistancia, *distancia, *menorCaminho, *visitadoAntes, posOrigem, posDestino;
int qtdeCidades = 2;
FILE *arq;

    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", nomeArq);

    arq = fopen(nomeArq, "r");
    fscanf(arq,"%d\n", &numeroCaminhos);

    if (arq == NULL)
    {
         printf("Problemas na abertura do arquivo\n");
         return 0;
    }

    cidade1 = malloc(sizeof(string) * numeroCaminhos);
    cidade2 = malloc(sizeof(string) * numeroCaminhos);
    demaisCidades = malloc(sizeof(string) * qtdeCidades);
    distancia = malloc(sizeof(int) * numeroCaminhos);

    for(int i=0; i<numeroCaminhos; i++){

        fscanf(arq,"%s %s %d\n", cidade1[i].cidade, cidade2[i].cidade, &distancia[i]);

        if(i == 0){
            strcpy(demaisCidades[0].cidade,cidade1[0].cidade);
            strcpy(demaisCidades[1].cidade,cidade2[0].cidade);
        }else{

            if(percorreCidades(demaisCidades,cidade1[i].cidade,qtdeCidades)){
                qtdeCidades++;
                demaisCidades = realloc(demaisCidades,sizeof(string) * qtdeCidades);
                strcpy(demaisCidades[(qtdeCidades-1)].cidade,cidade1[i].cidade);
            }
            if(percorreCidades(demaisCidades,cidade2[i].cidade,qtdeCidades)){
                qtdeCidades++;
                demaisCidades = realloc(demaisCidades,sizeof(string) * qtdeCidades);
                strcpy(demaisCidades[(qtdeCidades-1)].cidade,cidade2[i].cidade);
            }
        }
    }

    ponteiroMatriz = (int**)malloc(1 * sizeof(int*));
    ponteiroMatriz[0] = (int*) malloc(1 * sizeof(int));

    ponteiroMatriz = Aloca_matriz(ponteiroMatriz,qtdeCidades,qtdeCidades);

    for(int i,j, k = 0; k < numeroCaminhos; k++){
        for(i = 0; i < qtdeCidades; i++){
            if(!strcmp(demaisCidades[i].cidade, cidade1[k].cidade))
                break;
        }
        for(j = 0; j < qtdeCidades; j++){
            if(!strcmp(demaisCidades[j].cidade, cidade2[k].cidade))
                break;
        }
        ponteiroMatriz[i][j] = distancia[k];
        ponteiroMatriz[j][i] = distancia[k];
    }
    for(int i = 0; i < qtdeCidades; i++){
        for(int j = 0; j < qtdeCidades; j++){
            if(ponteiroMatriz[i][j] == 0){
                ponteiroMatriz[i][j] = INFINITY;
            }
        }
    }

    fscanf(arq,"%s %s\n", cidadeOrigem.cidade, cidadeDestino.cidade);
    for(int i = 0; i < qtdeCidades; i++){
        if(!strcmp(demaisCidades[i].cidade,cidadeOrigem.cidade))
            posOrigem = i;
        if(!strcmp(demaisCidades[i].cidade,cidadeDestino.cidade))
            posDestino = i;
    }

    menorCaminho = malloc(sizeof(int) * qtdeCidades);
    visitadoAntes = malloc(sizeof(int) * qtdeCidades);

    Dijkstra(posOrigem,posDestino,ponteiroMatriz,qtdeCidades,visitadoAntes,&menorDistancia);

    printf("Menor percurso: ");
    int j = posDestino, i = 0;

    do{
        j = visitadoAntes[j];
        menorCaminho[i] = j;
        i++;
    }while(j != posOrigem);

    for(int k = (i - 1); k >= 0; k--){
        printf("%s ",demaisCidades[menorCaminho[k]].cidade);
    }
    printf("%s",demaisCidades[posDestino].cidade);
    printf("\nDistancia total: %d Km\n", menorDistancia);
    fclose(arq);
    free(ponteiroMatriz);
    free(cidade1);
    free(cidade2);
    free(distancia);
    free(menorCaminho);
    free(visitadoAntes);

    return 0;
}



int percorreCidades(string *demaisCidades, char *cidade, int qtdeCidades){
    for(int i = 0; i < qtdeCidades; i++){
        if(!strcmp(demaisCidades[i].cidade, cidade)){
            return 0;
        }
    }

    return 1;
}

int** Aloca_matriz(int **matriz, int lin, int col){
    matriz = (int **) malloc(sizeof(int*)*lin);
    for(int i=0; i<lin; i++){
        matriz[i] = (int*) calloc(sizeof(int)*col, 0);
    }
    return matriz;
}

void Dijkstra(int indexCidadeOrigem, int indexCidadeDestino, int **matriz, int qtdeCidades, int *visitadoAntes, int *menorDistancia){
    int *visitado, *distancia;
    int i,j;
    visitado = malloc(sizeof(int) * qtdeCidades);
    distancia = malloc(sizeof(int) * qtdeCidades);
    for(i=0; i<qtdeCidades; i++){
        visitado[i] = 0;
        distancia[i] = matriz[indexCidadeOrigem][i];
        visitadoAntes[i] = indexCidadeOrigem;
    }
    distancia[indexCidadeOrigem] = 0;
    visitado[indexCidadeOrigem] = 1;
    for(i=0; i<qtdeCidades; i++){
        int menorCaminho;
        int aux = INFINITY;
        for(j=0; j<qtdeCidades; j++){
            if(distancia[j] < aux && visitado[j] == 0){
                aux = distancia[j];
                menorCaminho = j;
            }
        }
        visitado[menorCaminho] = 1;
        for(j=0; j<qtdeCidades; j++){
            if(!visitado[j] && distancia[menorCaminho] + matriz[menorCaminho][j] < distancia[j]){

                distancia[j] = aux + matriz[menorCaminho][j];
                visitadoAntes[j] = menorCaminho;
            }
        }
    }
    *menorDistancia = distancia[indexCidadeDestino];
}
