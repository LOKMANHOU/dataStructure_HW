#include <stdio.h>
#include <string.h>
#include "graphADT.h"

#define STRSIZE 50

GRAPH* fileRead(FILE *pFile);
int compare(void *argu1, void *argu2);

int main(void) {
	GRAPH *pGraph;
	FILE *pFile;
	
	pFile = fopen("0510842_11_23.txt", "r");
	pGraph = fileRead(pFile);
	
	printf("\n\n\nShortPath(each row represent a line(not directional line)):\n");
	shortestPath(pGraph);
	
	return 0;
}

GRAPH* fileRead(FILE* pFile){
	GRAPH* pGraph;
	char token[3] = " \n";
	char *find;
	char *lineStr;
	char *subStr;
	char *vertex1;
	char *vertex2;
	int cost;

	
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
		cost = atoi(subStr);
		
		
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
		
		graphInsArc(pGraph, vertex1, cost, vertex2);
		graphInsArc(pGraph, vertex2, cost, vertex1);
		
		strcpy(lineStr, "");
	}

	traverse(pGraph);
	return pGraph;
}

int compare(void *argu1, void *argu2){
	return strcmp((char*)argu1, (char*)argu2);
}
