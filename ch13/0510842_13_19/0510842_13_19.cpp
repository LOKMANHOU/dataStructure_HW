#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linkedListADT.h"

#define ROWSIZE 100 
#define hashArraySize 4
struct DATANODE{
	int number;
	int quantity;
	DATANODE *sameHashNumber;
};


DATANODE** createHashArray(FILE *file, int arraySize);
int hashFunc(int number, int arraySize);
void search(DATANODE **hashArray, int arraySize);
void display(DATANODE **hashArray, int arraySize);

int main(){
	FILE *file;
	DATANODE **hashArray;
	
	file = fopen("0510842_13_19.txt", "r");
	hashArray = createHashArray(file, hashArraySize);

	display(hashArray, hashArraySize);
	printf("\n\n");
	search(hashArray, hashArraySize);

	return 0;
}

void display(DATANODE **hashArray, int arraySize){
	printf("HomeAddr.\t PrimeArea\t OverflowList\n");
	
	int longListIndex;
	int longListNum = 0;
	int countNode = 0;
	
	for(int i = 0; i < arraySize; i ++){
		int tmpCount = 0;
		
		printf("%-8d\t", i);
		DATANODE *walker;
		walker = hashArray[i];
		while(walker != NULL){
			printf("%6d/%d\t", walker->number, walker->quantity);
			walker = walker->sameHashNumber;
			tmpCount++;
			countNode++;
		}
		printf("\n");
		
		if(tmpCount > longListNum){
			longListIndex = i;
			longListNum = tmpCount;
		}
	}
	
	printf("fullest address:%d\n", longListIndex);
	printf("node of fullest address:%d\n", longListNum);
	printf("avg. node in linked list:%lf\n", ((double)countNode) / arraySize);
}

void search(DATANODE **hashArray, int arraySize){
	int searchNum;
	int index; 
	
	while(true){
		printf("search number:");
		scanf("%d", &searchNum);
		
		index = hashFunc(searchNum, arraySize);
		
		if(hashArray[index] == NULL)
			printf("Not find.\n");
		else{
			DATANODE *walker;
			walker = hashArray[index];
			
			while(walker != NULL){
				if(walker->number == searchNum){
					printf("Nnumber:%d\tQuantity:%d\n", walker->number, walker->quantity);
					break;
				}
				
				walker = walker->sameHashNumber;
			}
			
			if(walker == NULL)
				printf("Not find.\n");
		}
	}
}

int hashFunc(int number, int arraySize){
	int index;
	index = number % arraySize;
	return index;
}

DATANODE** createHashArray(FILE *file, int arraySize){	
	DATANODE** hashArray;
	char *rowStr;
	char *subStr;

	hashArray = (DATANODE**)malloc(sizeof(DATANODE*) * arraySize);
	for(int i = 0; i < arraySize; i++)
		hashArray[i] = NULL;
	char token[3] = " \n";
	rowStr = (char*)malloc(sizeof(char) * ROWSIZE);
	
	while(fgets(rowStr, ROWSIZE, file)){
		int number;
		int quan;
		int index;
		int hashNumber;
		
		number = atoi(strtok(rowStr, token));
		quan =  atoi(strtok(NULL, token));
			
		index = hashFunc(number, arraySize);
		
		
		DATANODE *newNode;
		newNode = (DATANODE*)malloc(sizeof(DATANODE));
		newNode->number = number;
		newNode->quantity = quan;
		newNode->sameHashNumber = NULL;
		
		if(hashArray[index] == NULL){
			hashArray[index] = newNode;
		}else{
			DATANODE* preNewPos;
			preNewPos = hashArray[index];
			
			while(preNewPos->sameHashNumber != NULL)
				preNewPos = preNewPos->sameHashNumber;
				
			preNewPos->sameHashNumber = newNode;
		}
	}
	
	return hashArray;
}
