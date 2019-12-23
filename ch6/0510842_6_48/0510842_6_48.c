#include <stdio.h> 
#include <string.h>
#include "0510842_6_48.h"

const char FILENAME[]="0510842_6_48.txt";
const int MAXSTRINGSIZE = 200;

struct NODEDATA{
	struct NODEDATA *pLeft;
	struct NODEDATA *pRight;
	int sum;
	char *alphabet;
}; 

struct MAPDATA{
	char *alphabet;
	char *code;
};

int compare(struct NODEDATA* argu1, struct NODEDATA* argu2);
void readFile(struct LIST *pList);
void displayList(struct LIST* pList);
struct NODEDATA* huffman(struct LIST* pList);
void createMap(struct NODEDATA* root,struct LIST *pMap , char* code);
int compareMap(struct MAPDATA *argu1, struct MAPDATA *argu2);
char* textToHuf(struct LIST *pMap, char *inputArray);
char* hufToText(struct NODEDATA* root, char *inputCode);
void displayMap(struct LIST* pList);

int main(void){
	struct LIST *pList; //order list
	struct LIST	*pMap;
	struct NODEDATA* root;  //huffmancode root
	char *inputArray;
	char *convertToCode;
	char *convertToText;
	char *emptyCode;
		
	pList = createList(compare);
	pMap = createList(compareMap);
	inputArray = (char*)malloc(sizeof(char) * MAXSTRINGSIZE);
	emptyCode = (char*)malloc(sizeof(char) * MAXSTRINGSIZE);
	strcpy(inputArray, "");
	strcpy(emptyCode, "");
	
	
	readFile(pList);
	root = huffman(pList);
	printf("Character\tCode\n");
	createMap(root, pMap, emptyCode);
	
	printf("\nplease enter the text:\n");
	gets(inputArray);
	printf("your answer is: %s\n", inputArray);
	
	convertToCode = textToHuf(pMap, inputArray);
	convertToText = hufToText(root, convertToCode);
	
	printf("Text to code: %s\n", convertToCode);
	printf("Code to text: %s\n", convertToText);
	
	return 0;
}

char* hufToText(struct NODEDATA* root, char *inputCode){
	int i;
	char *text;
	struct NODEDATA* currentNode;
	
	i = 0;
	text = (char*)malloc(sizeof(char) * MAXSTRINGSIZE);
	strcpy(text, "");
	currentNode = root;
	
	while(inputCode[i]){
		if(inputCode[i] == '1')
			currentNode = currentNode->pRight;
		else if(inputCode[i] == '0')
			currentNode = currentNode->pLeft;
		
		if(currentNode->pLeft == NULL && currentNode->pRight == NULL){
			strcat(text, currentNode->alphabet);
			currentNode = root;
		}
		
		i++;
	}
	
	return text;
}

char* textToHuf(struct LIST *pMap, char *inputArray){
	int i;
	char *code;
	
	i = 0;
	code = (char*)malloc(sizeof(char) * MAXSTRINGSIZE);
	strcpy(code, "");
	
	while(inputArray[i]){
		struct MAPDATA *targetNode;
		struct MAPDATA *key;
		char *character;
		
		key = (struct MAPDATA*)malloc(sizeof(struct MAPDATA));
		character = (char*)malloc(sizeof(char) * MAXSTRINGSIZE);
		strncpy(character, &inputArray[i], 1);
		strcat(character, "\0");
		key->alphabet = character;
		retrieveNode(pMap, key, &targetNode);	
		strcat(code, targetNode->code);
		i++;
	}
	
	return code;
}

void createMap(struct NODEDATA* root,struct LIST *pMap, char* code){
	
	if(root->pLeft == NULL && root->pRight == NULL){
		struct MAPDATA *newMapData;
		
		newMapData = (struct MAPDATA*)malloc(sizeof(struct MAPDATA));
		newMapData->alphabet = root->alphabet;
		newMapData->code = code;
		addNode(pMap, newMapData);
		
		printf("%s\t\t%s\n", root->alphabet, code);
		
		return;
	}else{
		char *leftCode;
		char *rightCode;
		
		leftCode = (char*)malloc(sizeof(char) * MAXSTRINGSIZE);
		rightCode = (char*)malloc(sizeof(char) * MAXSTRINGSIZE);
		strcpy(leftCode, code);
		strcpy(rightCode, code);
		
		strcat(leftCode, "0");
		createMap(root->pLeft,pMap , leftCode);
		strcat(rightCode, "1");
		createMap(root->pRight,pMap , rightCode);
	}
	
}

void displayMap(struct LIST* pList){
	struct MAPDATA* tmpData;
	traverse(pList, 0, &tmpData);
	printf("%s\t", tmpData->alphabet);
	printf("%s\n", tmpData->code);
	while(traverse(pList, 1, &tmpData)){
		printf("%s\t", tmpData->alphabet);
		printf("%s\n", tmpData->code);	
	}
}

void displayList(struct LIST* pList){
	struct NODEDATA* tmpData;
	traverse(pList, 0, &tmpData);
	printf("%s\t", tmpData->alphabet);
	printf("%d\n", tmpData->sum);
	while(traverse(pList, 1, &tmpData)){
		printf("%s\t", tmpData->alphabet);
		printf("%d\n", tmpData->sum);	
	}
}

struct NODEDATA* huffman(struct LIST *pList){
	struct NODEDATA *s1;
	struct NODEDATA *s2;
	struct NODEDATA *newNode;
	char *catStr;
	
	while(true){
		s1 = NULL;
		s2 = NULL;
		newNode = (struct NODEDATA*)malloc(sizeof(struct NODEDATA));
		catStr = (char*)malloc(sizeof(char) * MAXSTRINGSIZE);
		strcpy(catStr,"");
		
		traverse(pList, 0, &s1);
		removeNode(pList, s1, &s1);
		
		if(emptyList(pList)){
			break;
		}
		
		traverse(pList, 0, &s2);
		removeNode(pList, s2, &s2);
		
		newNode->pLeft = s1;
		newNode->pRight = s2;
		newNode->sum = s1->sum + s2->sum;
		
		strcat(catStr, s1->alphabet);
		strcat(catStr, s2->alphabet);
		newNode->alphabet = catStr;
		addNode(pList, newNode);	
	}
	
	return s1;
}

void readFile(struct LIST *pList){
	int dsum = 0;
	FILE *pFile;
	struct NODEDATA *newNode;
	char *tmpStr;
	char *substr;
	char token[3] = " \n";
	
	tmpStr = (char*)malloc(sizeof(char) * MAXSTRINGSIZE);
	pFile = fopen(FILENAME, "r");
	
	while(fgets(tmpStr, MAXSTRINGSIZE, pFile)){
		char *newAlphabet;
		
		newAlphabet = (char*)malloc(sizeof(char) * 2);
		newNode = (struct NODEDATA*)malloc(sizeof(struct NODEDATA));
		
		substr = strtok(tmpStr, token);
		strcpy(newAlphabet, substr);
		substr = strtok(NULL, token);
		
		newNode->pLeft = NULL;
		newNode->pRight = NULL;
		newNode->sum = atoi(substr);
		newNode->alphabet = newAlphabet;
		addNode(pList, newNode);

	}
	fclose(pFile);
}

int compareMap(struct MAPDATA *argu1, struct MAPDATA *argu2){
	int ans;
	ans = strcmp(argu1->alphabet, argu2->alphabet);
	if(ans == 0)
		return 0;
	else if(ans == 1)
		return 1;
	else if(ans == 0)
		return -1;
}

int compare(struct NODEDATA* argu1, struct NODEDATA* argu2){
	if(argu1->sum > argu2->sum)
		return 1;
	else if(argu1->sum < argu2->sum)
		return -1;
	else if(argu1->sum == argu2->sum){
		if(strcmp(argu1->alphabet, argu2->alphabet) == 0)
			return 0;
		return -1;		
	}
}
