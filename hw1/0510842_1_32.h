#ifndef A
#define A

#include <stdio.h>
#include <stdlib.h>

int compare(void*, void*);
struct NODE* createNode(void*);

struct DATA{
	int id;
	float grade;
};

struct NODE{
	struct DATA* dataPtr;
	struct NODE *link; 
};

//program 1-2
NODE* createNode(DATA* itemPtr){
	NODE* nodePtr;
	nodePtr = (NODE*) malloc(sizeof(NODE));
	nodePtr->dataPtr = itemPtr;
	nodePtr->link = NULL;
	return nodePtr;
}
	
//program 1-6
int compare(void *ptr1, void *ptr2){
	if(*(float*)ptr1 >= *(float*)ptr2)
		return 1;
	else
		return -1;
}


#endif

