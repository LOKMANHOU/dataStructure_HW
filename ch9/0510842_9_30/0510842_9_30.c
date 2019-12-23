#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 
#include "0510842_9_30.h"

int compare(void *argu1, void *argu2);

int main(void){
	struct HEAP* heap;
	int minSize = INT_MAX;
	int size[4] = {100, 200, 500, 1000};
	int upCount[4] = {0, 0, 0, 0};
	int downCount[4] = {0, 0, 0, 0};
	int i,j;
	
	for(i = 0 ; i < 4; i++){
		printf("-----size:%d-----\n", size[i]);
		heap = heapCreate(size[i], compare);
		for(j = 1; j <= size[i]; j++){
			int *data;
			data = (int*)malloc(sizeof(int));
			*data = j;
			heapInsert(heap, data, &upCount[i]);
		}
		printf("reheap up count:%d\n", upCount[i]);
		
		for(j = 1; j <= size[i]; j++){
			int *dataOutPtr;
			heapDelete(heap, &dataOutPtr, &downCount[i]);
		}
		printf("reheap down count:%d\n\n\n", downCount[i]);
		heapDestroy(heap);
	
	}
	
	for(i = 0; i < size[i]; i++){
		if(size[i] < minSize)
			minSize = size[i];
	}
	
	printf("最符合 big O = N * log_2(N) 的size為:%d\n", minSize);
	
	
	return 0;
}


int compare(void *argu1, void *argu2){
	int *data1;
	int *data2;
	
	data1 = (int*)argu1;
	data2 = (int*)argu2;
	
	if(*data1 > *data2)
		return 1;
	else if(*data1 < *data2)
		return -1;
	else 
		return 0;
}
