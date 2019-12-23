#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int STRINGMAX = 30;

struct NODE{
	void* dataPtr;
	struct NODE* next;
};

struct LISTELEMENT{
	int count;
	struct NODE* pos;
	struct NODE* head;
};

struct FILENAME{
	char name[50];
};

void inputProcess(struct FILENAME **listName);
struct LISTELEMENT* createList(struct FILENAME* listName);
void displayListAry(struct LISTELEMENT* listAry, struct FILENAME* listName);

int fileCount;

int main(void){
	struct LISTELEMENT *listAry;
	struct FILENAME *listName;
	
	
	inputProcess(&listName);
	listAry = createList(listName);	
	displayListAry(listAry, listName);

	return 0;
}

void displayListAry(struct LISTELEMENT* listAry, struct FILENAME* listName){
	struct NODE* prePtr;
	int i;
	
	for(i = 0; i < fileCount; i++){
		printf("\n\nfile data name:%s\n", listName[i]);
		prePtr = listAry[i].head;
		while(prePtr != NULL){
			printf("\tdata:%s\n", prePtr->dataPtr);
			prePtr = prePtr->next;
		}
	}
	
}

struct LISTELEMENT* createList(struct FILENAME* listName){
	struct LISTELEMENT* listAry;
	struct NODE* prePtr;
	FILE* ptrFile;
	char* tmpData;
	int i;
	
	listAry = (struct LISTELEMENT*)malloc(sizeof(struct LISTELEMENT) * fileCount);
	tmpData = (char*)malloc(sizeof(char) * STRINGMAX);
	
	for(i = 0; i < fileCount; i++){
		prePtr = NULL;
		
		ptrFile = fopen(listName[i].name, "r");
		while(fgets(tmpData, STRINGMAX, ptrFile)){
			struct NODE* newNode;
			char token[2] = " ";
			char* subStr;
			char* copyStr;
		
			subStr = strtok(tmpData, token);
			do{
				newNode = (struct NODE*)malloc(sizeof(struct NODE));
				copyStr = (char*)malloc(sizeof(char) * STRINGMAX);
				
				if(prePtr == NULL){
					listAry[i].head = newNode;
				}else{
					prePtr->next = newNode;	
				} 
			
				strcpy(copyStr, subStr);
				newNode->dataPtr = copyStr;
				newNode->next = NULL;
			
				prePtr = newNode;
			}while(subStr = strtok(NULL, token));		
		}
		fclose(ptrFile);
	}

	return listAry;
}


void inputProcess(struct FILENAME **listName){
	char *tmpInput; 
	int i;
	
	i = 0;
	
	printf("number of files:\n");
	gets(tmpInput);
	fileCount = atoi(tmpInput);
	*listName = (struct FILENAME*)malloc(sizeof(struct FILENAME) * fileCount);
	
	printf("enter the all file name:(newline is delimiter.)\n");
	for(i = 0; i < fileCount; i++){
		gets(tmpInput);
		strcpy((*listName)[i].name, tmpInput);
		printf("your input file name:%s\n", (*listName)[i].name);
	}
}
