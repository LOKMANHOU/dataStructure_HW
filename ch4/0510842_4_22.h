#ifndef SRC_QUEUEADT_H_
#define SRC_QUEUEADT_H_

#include <stdlib.h>

#define false 0
#define true 1

struct QUEUE_NODE{
	void* dataPtr;
	struct QUEUE_NODE* next;
};

struct QUEUE{
	struct QUEUE_NODE* front;
	struct QUEUE_NODE* rear;
	int count;
};

struct QUEUE* createQueue(void);
struct QUEUE* destroyQueue(struct QUEUE* queue);

int deQueue(struct QUEUE* queue, void** itemPtr);
int enQueue(struct QUEUE* queue, void* itemPtr);
int frontQueue(struct QUEUE* queue, void** itemPtr);
int rearQueue(struct QUEUE* queue, void** itemPtr);
int countQueue(struct QUEUE* queue);

int emptyQueue(struct QUEUE* queue);
int fullQueue(struct QUEUE* queue);

void displayQueue(struct QUEUE* queue);

struct QUEUE* createQueue(){
	struct QUEUE* queue;

	queue = (struct QUEUE*)malloc(sizeof(struct QUEUE));
	if(queue){
		queue->front = NULL;
		queue->rear = NULL;
		queue->count = 0;
	}

	return queue;
}

int enQueue(struct QUEUE* queue, void* itemPtr){
	struct QUEUE_NODE* newPtr;

	if(!(newPtr = (struct QUEUE_NODE*)malloc(sizeof(struct QUEUE_NODE)))){
		return false;
	}

	newPtr->dataPtr = itemPtr;
	newPtr->next = NULL;

	if(queue->count == 0){
		queue->front = newPtr;
	}else{
		queue->rear->next = newPtr;
	}

	(queue->count)++;
	queue->rear = newPtr;
	return true;
}

int deQueue(struct QUEUE* queue, void** itemPtr){
	struct QUEUE_NODE* deleteLoc;

	if(!queue->count){
		return false;
	}

	*itemPtr = queue->front->dataPtr;

	deleteLoc = queue->front;
	if(queue->count == 1){
		queue->rear = queue->front = NULL;
	}else{
		queue->front = queue->front->next;
	}

	(queue->count)--;
	free(deleteLoc);

	return true;
}

int frontQueue(struct QUEUE* queue, void** itemPtr){
	if(!queue->count){
		return false;
	}else{
		*itemPtr = queue->front->dataPtr;
		return true;
	}
}

int rearQueue(struct QUEUE* queue, void** itemPtr){
	if(!queue->count){
		return false;
	}else{
		*itemPtr = queue->rear->dataPtr;
		return true;
	}
}

int emptyQueue(struct QUEUE* queue){
	return (queue->count == 0);
}

int fullQueue(struct QUEUE* queue){
	struct QUEUE_NODE* tmp;

	tmp = (struct QUEUE_NODE*)malloc(sizeof(*(queue->rear)));
	if(tmp){
		free(tmp);
		return false;
	}

	return true;
}

int countQueue(struct QUEUE* queue){
	return queue->count;
}

struct QUEUE* destroyQueue(struct QUEUE* queue){
	struct QUEUE_NODE* deletePtr;

	if(queue){
		while(queue->front != NULL){
			free(queue->front->dataPtr);
			deletePtr = queue->front;
			queue->front = queue->front->next;
			free(deletePtr);
		}
		free(queue);
	}
	return NULL;
}

void displayQueue(struct QUEUE* queue){
	struct QUEUE_NODE* currentNode;
	currentNode = queue->front;

	while(currentNode != NULL){
		printf("%s\n", (char*)currentNode->dataPtr);
		currentNode = currentNode->next;
	}
}

#endif
