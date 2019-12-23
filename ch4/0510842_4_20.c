#include <stdio.h>
#include "0510842_4_20.h"
#include <stdlib.h>
#include <string.h>

const int size = 80;

void inputArray(struct QUEUE*);
struct QUEUE* scanAfter(struct QUEUE*);
int evaluated(struct QUEUE*);

int main(void){
	struct QUEUE *queue;
	queue = createQueue();

	inputArray(queue);
	printf("Output:\n%d\n", evaluated(queue));
	
	system("pause");
	return 0;
}

int evaluated(struct QUEUE* queue){
	char* itemPtr;
	
	while(queue->count != 1){
		queue = scanAfter(queue);
	//	displayQueue(queue);
	}
	
	frontQueue(queue, (void*)&itemPtr);
	return atoi(itemPtr);
}

struct QUEUE* scanAfter(struct QUEUE* queue){
	struct QUEUE* tmpQueue;
	struct QUEUE* newQueue;
	char* tmpDataPtr;

	tmpQueue = createQueue();
	newQueue = createQueue();

	while(!emptyQueue(queue)){
		deQueue(queue, (void*)&tmpDataPtr);
		enQueue(tmpQueue, tmpDataPtr);
		
		if(tmpQueue->count == 3){
			char* n1;
			char* n2;
			char* n3;
			
			deQueue(tmpQueue, (void*)&n1);
			if(atoi(n1) == 0){
				deQueue(tmpQueue, (void*)&n2);
				deQueue(tmpQueue, (void*)&n3);
				if(atoi(n2) != 0 && atoi(n3) != 0){
					int ans = 0;
					if(strcmp(n1,"+") == 0){
						ans = atoi(n2) + atoi(n3);
					}else if(strcmp(n1,"-") == 0){
						ans = atoi(n2) - atoi(n3);
					}else if(strcmp(n1,"*") == 0){
						ans = atoi(n2) * atoi(n3);
					}else if(strcmp(n1,"/") == 0){
						ans = atoi(n2) / atoi(n3);
					}
					char* ansPtr;
					ansPtr = (char*)malloc(sizeof(char) * size);
					itoa(ans, ansPtr, 10);
					enQueue(newQueue, ansPtr);
				}else{
					enQueue(newQueue, n1);	
					enQueue(tmpQueue, n2);
					enQueue(tmpQueue, n3);
				}
			}else{
				enQueue(newQueue, n1);
			}
		}
	
	}
	
	while(!emptyQueue(tmpQueue)){
		deQueue(tmpQueue, (void*)&tmpDataPtr);
		enQueue(newQueue, tmpDataPtr);
	}

	return newQueue;
}

void inputArray(struct QUEUE* queue){
	char input[size];
	char token[2] = " ";
	char* subPtr;
	char *substr;

	printf("Input:\n");
	fgets(input, size, stdin);
	substr = (char*)malloc(sizeof(char) * 50);
	subPtr = strtok(input, token);
	strcpy(substr, subPtr);
	
	while(true){
		enQueue(queue,  substr);
		subPtr =  strtok(NULL, token);
		if(subPtr == NULL)
			break;
		substr = (char*)malloc(sizeof(char) * 50);
		strcpy(substr, subPtr);
	}
}
