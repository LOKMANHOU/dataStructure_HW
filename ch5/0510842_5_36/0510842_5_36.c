#include <stdio.h>
#include "0510842_5_36.h"

#define NAMESIZE 50
#define ROWSTRINGSIZE 100

struct NODEDATA{
	char name[NAMESIZE];
	int popu2000;
	int popu1990;
};

void readFile(struct LIST *pList);
int comparePopu(struct NODEDATA* argu1, struct NODEDATA* argu2);
void displayList(struct LIST *pList);

int main(void){
	struct LIST* pList;
	
	pList = createList(comparePopu);
	
	readFile(pList);
	displayList(pList);
	
	return 0;
}


void readFile(struct LIST *pList){
	FILE *pFile;
	char* tmpFileData;
	char *strsub;
	char token[2] = "|";
	
	tmpFileData = (char*)malloc(sizeof(char) * ROWSTRINGSIZE);
	
	pFile = fopen("0510842_5_36.txt", "r");
	while(fgets(tmpFileData, ROWSTRINGSIZE, pFile)){
		struct NODEDATA *newData;
		
		newData = (struct NODEDATA*)malloc(sizeof(struct NODEDATA));
		
		strsub = strtok(tmpFileData, token);
		strcpy(newData->name, strsub);
		strsub = strtok(NULL, token);
		newData->popu2000 = atoi(strsub);
		strsub = strtok(NULL, token);
		newData->popu1990 = atoi(strsub);
		
		addNode(pList, newData);
	}
	
}

void displayList(struct LIST *pList){
	struct NODE *tmpNode;
	struct NODEDATA *tmpData;
	int index = 0;
	
	tmpNode = pList->head;
	
	printf(" %-34s \t %12s \t %-34s \t %12s \t\n\n", "Census Data for 2000","Population", "Census Data for 1990", "Population");
	
	while(tmpNode != NULL){
		index++;
		tmpData = tmpNode->dataPtr;
		printf("%02d %32s \t %10d \t %02d %32s \t %10d \t\n", index, tmpData->name, tmpData->popu2000, index, tmpData->name, tmpData->popu1990); 
		tmpNode = tmpNode->forwardLink;
	}
	
	tmpNode= pList->rear;
	printf("\n\n");
	
	while(tmpNode != NULL){
		tmpData = tmpNode->dataPtr;
		printf("%02d %32s \t %10d \t %02d %32s \t %10d \t\n", index, tmpData->name, tmpData->popu2000, index, tmpData->name, tmpData->popu1990); 
		tmpNode = tmpNode->backwardLink;
		index--;
	}
	
}


int comparePopu(struct NODEDATA* argu1, struct NODEDATA* argu2){
	return -1;
}


