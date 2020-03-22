#include <stdio.h>

int mult(int base, int expoente);

int main(){
	int base, expoente;
	printf("Digite a base e o expoente inteiros: ");
	scanf("%d %d", &base, &expoente);
	printf("Resultado: %d",mult(base,expoente));
	return 0;
}

int mult(int base, int expoente){
	int res;
	if(expoente == 0){
		return 1;
	}
	else{
		res = base * mult(base, expoente - 1);
	}
	return res;
}