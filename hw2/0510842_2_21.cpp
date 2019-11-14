#include <stdio.h>
#include <stdlib.h>

unsigned long long factorial(int n){	
	unsigned long long answer = 1;
	for(int i = n; i >= 0; i--){
		if(i==0){
			return answer;
		}else{
			answer *= i;
		}
	}
	
}

int main(){
	unsigned long long fib5,fib20;
	fib5 = factorial(5);
	fib20 = factorial(20);
	printf("factorial(5) = %llu\n", fib5);	
	printf("factorial(20) = %llu\n", fib20);
	system("Pause");
	return 0;
}
