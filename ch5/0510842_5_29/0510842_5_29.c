#include <stdio.h>
#include <string.h>
#include "0510842_5_29.h"

#define true 1
#define false 0

const int STRINGSIZE = 50;

void inputFile(struct LIST* pList1, struct LIST* pList2);
struct LIST* addProcess(struct LIST* pList1, struct LIST* pList2);
void displayList(struct LIST* pList);
int comparePower(void* argu1, void* argu2);


struct NODEDATA{
	int coefficient;
	int power;
};

int main(void){
	struct LIST* polyList1;
	struct LIST* polyList2;
	struct LIST* ansList;
	
	polyList1 = createList(comparePower);
	polyList2 = createList(comparePower);

	inputFile(polyList1, polyList2);
	
	
	ansList = addProcess(polyList1, polyList2);
	
	printf("polynomial 1:\n");
	displayList(polyList1);
	printf("\npolynomial 2:\n");
	displayList(polyList2);
	printf("\nSum:\n");
	displayList(ansList);
	
	return 0;
}

struct LIST* addProcess(struct LIST* pList1, struct LIST* pList2){
	struct LIST* ansList;
	struct NODEDATA* nodeData1;
	struct NODEDATA* nodeData2;
	int notEndList1;
	int notEndList2;

	ansList = createList(comparePower);
	
	notEndList1 = traverse(pList1, 0, (void*)&nodeData1);
	notEndList2 = traverse(pList2, 0, (void*)&nodeData2);
	
	
	struct NODEDATA* removeTmp;
	int tmpCoefficient;
	int tmpPower;

	while(true){		
		
		if(nodeData1->power > nodeData2->power || !notEndList2){
			addNode(ansList, nodeData1);
		//	removeNode(pList1, nodeData1, (void*)&removeTmp);			//not use removeNde because the pointer will point a disapeared point in the traverse function.
			if(notEndList1)
				notEndList1 = traverse(pList1, 1, (void*)&nodeData1);
		}
		
		if(nodeData1->power < nodeData2->power || !notEndList1){
			addNode(ansList, nodeData2);
		//	removeNode(pList2, nodeData2, (void*)&removeTmp);
			if(notEndList2)
				notEndList2 = traverse(pList2, 1, (void*)&nodeData2);
		}
	
		if(nodeData1->power == nodeData2->power && notEndList1 && notEndList2){
			struct NODEDATA* ansNode;
			int sum;
			int pow;
			
			ansNode = (struct NODEDATA*)malloc(sizeof(struct NODEDATA));
			sum = nodeData1->coefficient + nodeData2->coefficient;
			pow = nodeData1->power;
			ansNode->coefficient = sum;
			ansNode->power = pow;
			
		//	removeNode(pList2, nodeData2, (void*)&removeTmp);
			if(ansNode->coefficient != 0)
				addNode(ansList, ansNode);
		//	removeNode(pList1, nodeData1, (void*)&removeTmp);
			
			if(notEndList1){
				notEndList1 = traverse(pList1, 1, (void*)&nodeData1);
			}
			if(notEndList2){
				notEndList2 = traverse(pList2, 1, (void*)&nodeData2);
			}
		}
		
		if(!notEndList1 && !notEndList2){
			break;
		}
	}
	
	
	return ansList;
}

int comparePower(void* argu1, void* argu2){  // default is small to large (by the 115 row in 0510842_5_29.h )
	if(((struct NODEDATA*)argu1)->power > ((struct NODEDATA*)argu2)->power)
		return -1;
	else if(((struct NODEDATA*)argu1)->power < ((struct NODEDATA*)argu2)->power)
		return 1;
	else
		return 0;
}

void inputFile(struct LIST* pList1, struct LIST* pList2){
	FILE* fileStream;
	char* tmpFileData;
	char token[2] = " ";
	char* substr;
	struct NODEDATA* ptrData;
	
	ptrData = (struct NODEDATA*)malloc(sizeof(struct NODEDATA*));
	tmpFileData = (char*)malloc(sizeof(char) * STRINGSIZE);
	
	fileStream = fopen("polynomial1.txt", "r");
	while(fgets(tmpFileData, STRINGSIZE, fileStream) != NULL){
		substr = strtok(tmpFileData, token);
		ptrData->coefficient = atoi(substr);
		substr = strtok(NULL, token);
		ptrData->power = atoi(substr);
		
		addNode(pList1, ptrData);
		
		ptrData = (struct NODEDATA*)malloc(sizeof(struct NODEDATA*));
		free(tmpFileData);
		tmpFileData = (char*)malloc(sizeof(char) * STRINGSIZE);
	}
	fclose(fileStream);
	
	fileStream = fopen("polynomial2.txt", "r");
	while(fgets(tmpFileData, STRINGSIZE, fileStream) != NULL){
		substr = strtok(tmpFileData, token);
		ptrData->coefficient = atoi(substr);
		substr = strtok(NULL, token);
		ptrData->power = atoi(substr);
		
		addNode(pList2, ptrData);
		
		ptrData = (struct NODEDATA*)malloc(sizeof(struct NODEDATA*));
		free(tmpFileData);
		tmpFileData = (char*)malloc(sizeof(char) * STRINGSIZE);
	}
	
	fclose(fileStream);
}

void displayList(struct LIST* pList){
	int first = true;
	struct NODEDATA* nodeData;
	traverse(pList, 0, (void*)&nodeData);
	do{
		if(nodeData->coefficient > 0 && !first)
			printf(" +%d", nodeData->coefficient);
		else
			printf(" %d", nodeData->coefficient);
		
		if(nodeData->power != 0)
			printf("x^%d", nodeData->power);
		
		first = false;
	}while(traverse(pList, 1, (void*)&nodeData));
	printf("\n");
}


