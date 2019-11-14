#include <stdio.h>
#include <stdlib.h>
#include "0510842_3_16.h"

int main(void){
	struct STACK* stack;
	char fileName[25] = "0510842_3_16.txt";
	FILE* fp; 
	int tem;
	int* dataPtr;
	
	fp = fopen(fileName, "r");
	if(fp == NULL) {
		perror("open error");
		system("Pause");
		return 1;
	}
	
	stack = createStack();
	
	while(fscanf(fp, "%d", &tem) != EOF){
		dataPtr = (int*)malloc(sizeof(int));
		*dataPtr = tem;
		
		if((*dataPtr) >= 0){
			pushStack(stack, dataPtr);
		}else{
			printf("it detect a negative number:\n");
			//number is negative
			if(countStack(stack) < 5){
				printf("stack size is less than five!\n");
				system("Pause");
				return 1;
			}else{
				int i;
				for(i = 0; i < 5; i++)	{
					printf("%d\n", *((int*)popStack(stack)));
				}
				printf("\n\n");
			}
		}
	}
	
	fclose(fp);
	
	printf("The remaing items in the stack:\n");
	while(!emptyStack(stack)){
		printf("%d\n", *((int*)popStack(stack)));
	}
	printf("\n\n");
	
	system("Pause");
	return 0;
}
