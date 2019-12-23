#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "0510842_7_23.h"

#define STRINGSIZE 50

struct NODEDATA{
	char *name;
	char *telephone;
};

int compare(void* argu1, void* argu2);
void displayProcess(void* argu);
void writeFileProcess(void* argu);
void addProcess(struct BST_TREE *pTree);
void deleteProcess(struct BST_TREE *pTree);
void searchProcess(struct BST_TREE *pTree);
void printProcess(struct BST_TREE *pTree);

FILE *fp;

int main(){
	struct BST_TREE* pTree;
	char *rowStr;
	char *subStr;
	char token[3] = " \n";
	
	rowStr = (char*)malloc(sizeof(char) * STRINGSIZE);
	pTree = BST_Create(30, compare);
	fp = fopen("0510842_7_23.txt", "r");
	
	printf("maximum number of node is 10.\n");
	while(fgets(rowStr, STRINGSIZE, fp)){
		struct NODEDATA *newData;
		
		newData = (struct NODEDATA*)malloc(sizeof(struct NODEDATA));
		
		if(!strcmp(rowStr,"\n"))
			continue;
		subStr = strtok(rowStr, token);
		newData->name = subStr;
		subStr = strtok(NULL, token);
		newData->telephone = subStr;
		
		BST_Insert(pTree, newData);
		rowStr = (char*)malloc(sizeof(char) * STRINGSIZE);
	}
	
	
	fclose(fp);
	
	while(true){
		printf("-------Menu-------\n");
		printf("Menu:(A: add, D: delete, F: find, P:print list, E: exit)\n");
		gets(rowStr);
		
		if(!strcmp(rowStr, "A") || !strcmp(rowStr, "a")){
			addProcess(pTree);
		}else if(!strcmp(rowStr, "D") || !strcmp(rowStr, "d")){
			deleteProcess(pTree);
		}else if(!strcmp(rowStr, "F") || !strcmp(rowStr, "f")){
			searchProcess(pTree);
		}else if(!strcmp(rowStr, "P") || !strcmp(rowStr, "p")){
			printProcess(pTree);
		}else if(!strcmp(rowStr, "E") || !strcmp(rowStr, "e")){
			break;
		} 
		
	}
	
	fp = fopen("0510842_7_23.txt", "w");
	
	printf("\n\nWrite reback to the file.\n\nList:\n");
	BST_Traverse(pTree, writeFileProcess);
	BST_Traverse(pTree, displayProcess);
			
	return 0;
}

void writeFileProcess(void* argu){
	struct NODEDATA* data;
	
	data = (struct NODEDATA*)argu;
	
	fprintf(fp,"%s %s\n", data->name, data->telephone);
}

void printProcess(struct BST_TREE *pTree){
	BST_Traverse(pTree, displayProcess);
	printf("\n\n");
}

void searchProcess(struct BST_TREE *pTree){
	struct NODEDATA *keyPtr;
	char *rowStr;

	keyPtr = (struct NODEDATA*)malloc(sizeof(struct NODEDATA));
	rowStr = (char*)malloc(sizeof(char) * STRINGSIZE);

	printf("-------SearchProcess:-------\n");
	printf("please enter the name:(ex: tony)\n");	
	gets(rowStr);
	keyPtr->name = rowStr;
	
	keyPtr = (struct NODEDATA*)BST_Retrieve(pTree, keyPtr);
	
	printf("name:%s\ttelephone:%s\n", keyPtr->name, keyPtr->telephone);
	printf("\n\n");
}

void addProcess(struct BST_TREE *pTree){
	struct NODEDATA *newData;
	char *rowStr;
	char *subStr;
	char token[3] = " \n";
	
	newData = (struct NODEDATA*)malloc(sizeof(struct NODEDATA));
	rowStr = (char*)malloc(sizeof(char) * STRINGSIZE);
	
	printf("-------AddProcess:-------\n");
	printf("please enter the name and telphoneNumber:(ex: tony 1234567891)\n");
	gets(rowStr);
	subStr = strtok(rowStr, token);
	newData->name = subStr;
	subStr = strtok(NULL, token);
	newData->telephone = subStr;
	
	BST_Insert(pTree, newData);
	printf("\n\n");
}

void deleteProcess(struct BST_TREE *pTree){
	struct NODEDATA *delData;
	char *rowStr;
	
	delData = (struct NODEDATA*)malloc(sizeof(struct NODEDATA));
	rowStr = (char*)malloc(sizeof(char) * STRINGSIZE);
	
	printf("-------DeleteProcess:-------\n");
	printf("please enter the name:(ex: tony)\n");
	gets(rowStr);
	delData->name = rowStr;

	BST_Delete(pTree, delData);
	printf("\n\n");
}

void displayProcess(void* argu){
	struct NODEDATA* data;
	
	data = (struct NODEDATA*)argu;
	printf("name:%s\ttelephone:%s\n", data->name, data->telephone);
}

int compare(void* argu1, void* argu2){
	struct NODEDATA* data1;
	struct NODEDATA* data2;
	
	data1 = (struct NODEDATA*)argu1;
	data2 = (struct NODEDATA*)argu2;
	
	return strcmp(data1->name, data2->name);
}
