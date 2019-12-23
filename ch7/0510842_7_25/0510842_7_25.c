#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "0510842_7_25.h"

#define MAXSTRINGSIZE 50

int compare(void *argu1, void *argu2){	
	char* data[2];
	int grade[2];
	int i;
	
	data[0] = (char*)argu1;
	data[1] = (char*)argu2;
	
	for(i = 0; i < 2; i++){
		if(strcmp(data[i], "A") == 0)
			grade[i] = 5;
		else if(strcmp(data[i], "C") == 0)
			grade[i] = 3;
		else if(strcmp(data[i], "B") == 0)
			grade[i] = 2;
		else if(strcmp(data[i], "D") == 0)
			grade[i] = 4;
		else if(strcmp(data[i], "E") == 0)
			grade[i] = 6;
	}
	
	if(grade[0] > grade[1])
		return 1;
	else if(grade[0] < grade[1])
		return -1;
	else
		return 0;
}
void process(void *data){
	printf("data:%s\n", (char*)data);
}


int main(void){
	struct BST_TREE *tree;
	char nodeData[5] = {'A', 'C', 'E', 'B', 'D'};
	int i;
		
	tree = BST_Create(compare);
	
	for(i = 0; i < 5; i++){
		char *data;
		data = (char*)malloc(sizeof(char) * MAXSTRINGSIZE);
		snprintf(data, MAXSTRINGSIZE, "%c" , nodeData[i] );
		BST_Insert(tree, data);
	}
	
	BST_Thread(tree, process);
	
	return 0;
}


