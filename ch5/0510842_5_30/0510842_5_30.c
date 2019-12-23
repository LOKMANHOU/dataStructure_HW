#include <stdio.h>
#include <string.h>
#include "0510842_5_30.h"

#define true 1
#define false 0

const int STRINGSIZE = 100;

void inputProcess(struct LIST *pList1, struct LIST *pList2);
int compareInput(void* argu1, void* argu2);
int compareCarry(void* argu1, void* argu2);
void displayList(struct LIST* pList);
struct LIST* addProcess(struct LIST* pList1, struct LIST* pList2, struct LIST* pCarry, struct LIST* pAns);

struct NODEDATA{
	int value;
};


int main(void){
	struct LIST *first;
	struct LIST *second;
	struct LIST *carry;
	struct LIST *ans; 
	
	first = createList(compareInput);
	second = createList(compareInput);
	carry = createList(compareCarry);
	ans = createList(compareCarry);
	
	inputProcess(first, second);
	addProcess(first,second, carry, ans);

	printf("Output:\n");
	displayList(ans);
	printf("(value)\n");
	displayList(carry);
	printf("(carry value)\n");
	return 0;
}

struct LIST* addProcess(struct LIST* pList1, struct LIST* pList2, struct LIST* pCarry, struct LIST* pAns){
	int* firstData;
	int* secondData;
	int* pCarryData;
	int* pSumData;
	int elementSum;
	int notEndList1;
	int notEndList2;
	
	//pCarryData = (int*)malloc(sizeof(int));
	pCarryData = NULL;
	
	notEndList1 = traverse(pList1, 0, &firstData);
	notEndList2 = traverse(pList2, 0, &secondData);
	
	do{
		if(!notEndList1 && !notEndList2){
			break;
		}else if(!notEndList1){
			while(notEndList2){
				addNode(pCarry, pCarryData);
				pSumData = (int*)malloc(sizeof(int));
				*pSumData = *secondData + *pCarryData;
				
				pCarryData = (int*)malloc(sizeof(int));
				if(*pSumData >= 10){
					*pSumData -= 10;
					*pCarryData = 1;
				}else{
					*pCarryData = 0;
				}
				
				addNode(pAns, pSumData);
				
				
				notEndList2 = traverse(pList2, 1, &secondData);
			}
			break;
		}else if(!notEndList2){
			while(notEndList1){
				addNode(pCarry, pCarryData);
				pSumData = (int*)malloc(sizeof(int));
				*pSumData = *firstData + *pCarryData;
				
				pCarryData = (int*)malloc(sizeof(int));
				if(*pSumData >= 10){
					*pSumData -= 10;
					*pCarryData = 1;
				}else{
					*pCarryData = 0;
				}
				
				addNode(pAns, pSumData);
				
				notEndList1 = traverse(pList1, 1, &firstData);
			}
			break;
		}else{
			pSumData = (int*)malloc(sizeof(int));
			if(pCarryData == NULL)
				*pSumData = *firstData + *secondData;
			else{
				addNode(pCarry, pCarryData);
				*pSumData = *firstData + *secondData + *pCarryData;
			}
			
			pCarryData = (int*)malloc(sizeof(int));
			if(*pSumData >= 10){
				*pSumData -= 10;
				*pCarryData = 1;
			}else{
				*pCarryData = 0;
			}
			
			addNode(pAns, pSumData);
			
			notEndList1 = traverse(pList1, 1, &firstData);
			notEndList2 = traverse(pList2, 1, &secondData);
		}
	}while(true);
}

int compareInput(void* argu1, void* argu2){
	return -1;
}

int compareCarry(void* argu1, void* argu2){
	return -1;
}

void inputProcess(struct LIST *pList1, struct LIST *pList2){
	char input[STRINGSIZE];
	char token[2] = " ";
	int *newSpace;
	char *strsub;
	int i = 0;
	
	printf("Input:\n");
	
	gets(input);
	
	strsub = strtok(input, token);
	
	while(true)	{
		if(strsub[i] == '\0')
			break;
		newSpace = (int*)malloc(sizeof(int));
		
		*newSpace = strsub[i] - 48;		
		addNode(pList1, newSpace);
		i++;
	}
	
	i = 0;
	strsub = strtok(NULL, token);
	while(true)	{
		if(strsub[i] == '\0')
			break;
		newSpace = (int*)malloc(sizeof(int));
		*newSpace = strsub[i] - 48;		
		addNode(pList2, newSpace);
		i++;
	}
	
}

void displayList(struct LIST* pList){
	int* data;
	int notEndList = 0;
	
	notEndList = traverse(pList, 0, &data);	
	while(notEndList){
		printf("%d", *data);
		notEndList = traverse(pList, 1, &data);
	}
}
