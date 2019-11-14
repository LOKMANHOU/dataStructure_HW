#ifndef _STACKSADT 
#define _STACKSADT

#include <stdio.h> 
#include <stdlib.h>

#define true 1
#define false 0

struct STACK_NODE{
	void* dataPtr;
	struct STACK_NODE* link;
};

struct STACK{
	int count;
	struct STACK_NODE* top;
};

struct STACK* createStack(void);
int pushStack(struct STACK*, void*);
void* popStack(struct STACK*);
void* topStack(struct STACK*);
int emptyStack(struct STACK*);
int fullStack(struct STACK*);
int countStack(struct STACK*);
struct STACK* destroyStack(struct STACK*);


struct STACK* createStack(){
	struct STACK* stack;
	stack = (struct STACK*)malloc(sizeof(struct STACK));
	if(stack){
		stack->count = 0;
		stack->top = NULL;
	}
	return stack;
}

int pushStack(struct STACK* stack, void* dataInPtr){
	struct STACK_NODE* newPtr = (struct STACK_NODE*)malloc(sizeof(struct STACK_NODE));

	if(!newPtr)
		return false;
	
	//newNode
	newPtr->dataPtr = dataInPtr;
	newPtr->link = stack->top;
	
	//stack head
	stack->top = newPtr;
	(stack->count)++;
	
	return true;
}

void* popStack(struct STACK* stack){
	void* dataOutPtr;
	struct STACK_NODE* temp;

	if(stack->count == 0)
		dataOutPtr = NULL;
	else{
		temp = stack->top;
		stack->top = temp->link;
		dataOutPtr = temp->dataPtr;
		free(temp);
		(stack->count)--;
	}
	
	return dataOutPtr;
}

void* topStack(struct STACK* stack){
	if(stack->count == 0)
		return NULL;
	else
		return stack->top->dataPtr;
}

int emptyStack(struct STACK* stack){	
	return (stack->count == 0);
}

int fullStack(struct STACK* stack){
	struct STACK_NODE* temp;
	
	if((temp = (struct STACK_NODE*)malloc(sizeof((*stack->top))))){
		free(temp);
		return false;		
	}else
		return true;
}

int countStack(struct STACK* stack){
	return stack->count;
}

struct STACK* destroyStack(struct STACK* stack){
	struct STACK_NODE* temp;
	
	if(stack){
		while(stack->top != NULL){
			temp  = stack->top;
			stack->top = temp->link;
			free(temp->dataPtr);
			free(temp);
		}
		free(stack);
	}
	
	return NULL;
}

#endif

