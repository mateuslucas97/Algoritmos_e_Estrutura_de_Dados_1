#include <stdio.h>

void dec2bin(int dec);

int main(){
	int dec;
	printf("Digite um numero inteiro: ");
	scanf(" %d", &dec);
	printf("Resultado: ");
	dec2bin(dec);
	return 0;
}

void dec2bin(int dec){
	
	if (dec / 2 != 0){
		dec2bin(dec / 2);
	}

	printf("%d", dec % 2);
}