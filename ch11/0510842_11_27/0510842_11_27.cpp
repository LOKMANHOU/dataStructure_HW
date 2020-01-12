#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "0510842_11_27.h"

#define STRSIZE 50

GRAPH* fileRead(FILE *pFile);
int compare(void *argu1, void *argu2);
void process(void* dataPtr);

int main(void){
	GRAPH *pGraph;
	FILE *pFile;
	
	pFile = fopen("0510842_11_27.txt", "r");
	pGraph = fileRead(pFile);
	
	printf("\n\nDFT:\n");
	graphDpthFrst(pGraph, process);
	
	
	return 0;
}

void process(void *dataPtr){
	static bool endFlag = false;
	
	if(strcmp((char*)dataPtr, "O") == 0){
		endFlag = true;
		printf("goal\n");
	}
	
	if(!endFlag){
		printf("%s->", (char*)dataPtr);
	}
	

	
}

GRAPH* fileRead(FILE* pFile){
	GRAPH* pGraph;
	char token[3] = " \n";
	char *find;
	char *lineStr;
	char *subStr;
	char *vertex1;
	char *vertex2;

	
	find = NULL;
	pGraph = graphCreate(compare);
	lineStr = (char*)malloc(sizeof(char) * STRSIZE);
	strcpy(lineStr,"");
	int i = 1;
	while(fgets(lineStr, STRSIZE, pFile)){
		vertex1 = (char*)malloc(sizeof(char) * STRSIZE);
		vertex2 = (char*)malloc(sizeof(char) * STRSIZE);
		
		subStr = strtok(lineStr, token);
		strcpy(vertex1, subStr);
		subStr = strtok(NULL, token);
		strcpy(vertex2, subStr);
		subStr = strtok(NULL, token);
		
		
	//	printf("line:%d\n",i++);
		if(graphRetrVrtx(pGraph, vertex1, (void**)&find) != 1){		
			graphInsVrtx(pGraph, vertex1);
		}else{
		//	printf("name1 has:%s\n", find);
		}
		
		if(graphRetrVrtx(pGraph, vertex2, (void**)&find) != 1){		
			graphInsVrtx(pGraph, vertex2);
		}else{
		//	printf("name2 has:%s\n", find);
		}
		
		graphInsArc(pGraph, vertex1, vertex2);
		graphInsArc(pGraph, vertex2, vertex1);
		
		strcpy(lineStr, "");
	}

	traverse(pGraph);
	return pGraph;
}

int compare(void *argu1, void *argu2){
	return strcmp((char*)argu1, (char*)argu2);
}
