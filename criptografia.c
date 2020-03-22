#include <stdio.h>
#include <stdlib.h>

#define max_caracteres_no_arquivo 10000
#define max_caracteres_nome_do_arquivo 100

/*Esse exercicio foi feito tendo como base
  e ajuda de alunos da computação que já fizeram esse exercicio
*/

char *le_arquivo(char *nome_arquivo);
int total_char(const char s[]);
char *passo2(char *s);
char *passo3(char *s);
char *passo4(char *s);
char *passo5(char *s);
void criptografia(char *s);

int main(){
    char *nome_arquivo, *arquivo_origem;
    nome_arquivo = malloc(sizeof(char)*max_caracteres_nome_do_arquivo);
    printf("Digite o nome do arquivo: ");
    scanf("%s", nome_arquivo);
    printf("\n--------------------\nMensagem codificada:\n--------------------\n");
    arquivo_origem = le_arquivo(nome_arquivo);
    printf("%s\n\n", arquivo_origem);
    printf("----------------------\nMensagem decodificada:\n----------------------\n");
    criptografia(arquivo_origem);
    return 0;
}

//funcao para leitura do arquivo
char *le_arquivo(char *nome_arquivo){
    FILE *f;
    char *dados_arquivo;
    dados_arquivo = malloc(sizeof(char)*max_caracteres_no_arquivo);
    f = fopen(nome_arquivo, "r");
    fscanf(f, "%s", dados_arquivo);
    fclose(f);
    return dados_arquivo;
}

//conta o total de caracteres da mensagem
int total_char(const char s[]){
    int i =0;
    do{
        i++;
    }while(s[i] != '\0');
    return i;
}

//monta a mensagem no formato do alfabeto da cifra de cesar dividindo em blocos de palavras
char *passo2(char *s){
    char aux[2];
    int total_s = total_char(s);
    for(int i = 0; i < total_s / 2; i = i + 4){
        aux[0] = s[i];
        aux[1] = s[i + 1];
        s[i] = s[total_s - i - 2];
        s[i + 1] = s[total_s - i - 1];
        s[total_s - i - 2] = aux[0];
        s[total_s - i - 1] = aux[1];
    }
    return s;
}

//inverte o bloco de palavras
char *passo3(char *s){
    char aux;
    int total_s = total_char(s);
    for(int i = 0; i < total_s - 2; i = i + 2){
        aux = s[i];
        s[i] = s[i + 1];
        s[ i + 1] = aux;
    }
    aux = s[total_s - 2];
    s[total_s - 2] = s[total_s - 1];
    s[total_s - 1] = aux;
    return s;
}

//inverte cada letra da palavra
char *passo4(char *s){
    char *s2;
    int i,t = total_char(s), ASC;
    s2 = malloc(t*sizeof(int));
    for(i = 0; i < t; i++){
        ASC = s[i];
        if(ASC >= 65 && ASC <= 90){
            if(ASC <= 67){
                ASC = 90 - (67 - ASC);
            }
            else{
                ASC = ASC - 3;
            }
        }
        else if(ASC >= 97 && ASC <= 122){
            if(ASC <= 99){
                ASC = 122 - (99 - ASC);
            }
            else{
                ASC = ASC - 3;
            }
        }
        s2[i] = ASC;
    }
    s2[i] = '\0';
    return s2;
}

//faz a subtitiuicao de cada letra na cifra de cesar
char *passo5(char *s){
    int total_s;
    char *s2;
    total_s = total_char(s);
    s2 = malloc(sizeof(char)*total_s);
    for(int i = 0; s[i] != '\0'; i++){
        if(s[i] != '#'){
            s2[i] = s[i];
        }
        else{
            s[i] = ' ';
        }
    }
    return s;
}

//funcao que contempla cada um dos passos descritos nesse execicio
void criptografia(char *s){
    char *resposta;
    resposta = passo2(s);
    resposta = passo3(resposta);
    resposta = passo4(resposta);
    resposta = passo5(resposta);
    printf("%s", resposta);
}
