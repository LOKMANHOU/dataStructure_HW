#include <stdio.h>
#include <stdlib.h>

int comb(int n, int k){
	if(k==0 || n == k){
		return 1;
	}else{
		return comb(n-1, k) + comb(n-1, k-1);
	}
}

int main(int argc, char *argv[]){
	int n,k;
	n = atoi(argv[1]);
	k = atoi(argv[2]);
	printf("n = %d \t k = %d\n", n, k);
	
	printf("output: %d\n", comb(n, k));

	system("Pause");
	return 0;
} 
