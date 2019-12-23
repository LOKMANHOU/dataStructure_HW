#include <stdio.h>
#include <string.h>
#include "0510842_5_26.h"

const int stringSize = 100;


struct nameData_t{
	char* name;
	struct LIST* scoreList;
};

void displayList(struct LIST* pList);
void addScoreProcess(struct LIST* pList);
void ansProcess(struct LIST* pList);
void openFile(struct LIST* list);
int compareString(struct nameData_t* argu1, struct nameData_t* argu2);
int compareScore(void* argu1, void* argu2);




int main(void){
	struct LIST* list;
	list = createList(compareString);
	
	openFile(list);
	addScoreProcess(list);
	ansProcess(list);
	
	
	return 0;
}

void ansProcess(struct LIST* pList){
	struct nameData_t* tmpNode;
	traverse(pList, 0, &tmpNode);
	do{
		char* score;
		int targetSum = 0;
		int targetNumber = 0;
		
		traverse(tmpNode->scoreList, 0, &score);
		do{
			targetNumber++;			
			targetSum += atoi(score);
		}while(traverse(tmpNode->scoreList, 1, &score));
		
		printf("\nname:%s\n", tmpNode->name);
		printf("\tscore total:%d\n", targetSum);
		printf("\taverage score:%f\n", ((float)targetSum)/targetNumber);
	}while(traverse(pList, 1, &tmpNode));
}

void addScoreProcess(struct LIST* pList){
	char* inputScoreData;
	struct nameData_t* tmpNode;
	char token[2] = " ";
	char* subPtr;
	char *substr;
	
	traverse(pList, 0, &tmpNode);	
	do{	
		inputScoreData = (char*)malloc(sizeof(char) * stringSize);
		substr = (char*)malloc(sizeof(char) * stringSize);
		
		printf("name: %s\n", tmpNode->name);
		printf("please enter the score:  (ex: 52 63 72 => input the three data)\n");
		
		//save score to scoreList
		fgets(inputScoreData , stringSize, stdin);		
		subPtr = strtok(inputScoreData, token);
		strcpy(substr, subPtr);	
		while(true){
			addNode(tmpNode->scoreList, substr);
			subPtr = strtok(NULL, token);	
			if(subPtr == NULL)
				break;
			substr = (char*)malloc(sizeof(char) * stringSize);
			strcpy(substr, subPtr);
		}	
	}while(traverse(pList, 1, &tmpNode));
	
} 

int compareString(struct nameData_t* argu1, struct nameData_t* argu2){
	return strcmp((char*)argu1->name, (char*)argu2->name);
}

int compareScore(void* argu1, void* argu2){
	if(*((int*)argu2) == NULL)
		return -1;
	else
		return 1;
}

void openFile(struct LIST* list){
	FILE* fileStream;
	char* tmpname;
	struct nameData_t* newData;
	
	newData = (struct nameData_t*)malloc(sizeof(struct nameData_t));
	tmpname = (char*)malloc(sizeof(char) * stringSize);
	
	
	fileStream = fopen("0510842_5_26.txt", "r");
	while(fgets(tmpname, stringSize, fileStream) != NULL){
		char token[2] = "\n";
		char* subPtr;
		char *substr;
		substr = (char*)malloc(sizeof(char) * stringSize);
		subPtr = strtok(tmpname, token);
		strcpy(substr, subPtr);
		 
		newData->name = substr;  //tmpname
		newData->scoreList = createList(compareScore);
		addNode(list, newData);
		
		//check list name data
		/*
		struct nameData_t* tmp;
		struct nameData_t* search;
		search	 = (struct nameData_t*)malloc(sizeof(struct nameData_t));			
		search->name = tmpname;		
		searchList(list, search, &tmp);
		printf("%s\n", tmp->name);
		*/
		
		newData = (struct nameData_t*)malloc(sizeof(struct nameData_t));
		tmpname = (char*)malloc(sizeof(char) * stringSize);
	}
}

void displayList(struct LIST* pList){
	struct NODE* tmp;
	tmp = pList->head;
	
	while(tmp != NULL){
		struct nameData_t* nameData = (struct nameData_t*)tmp->dataPtr;
		printf("%s\n", (char*)nameData->name);
		tmp = tmp->link;
	}
	
}
