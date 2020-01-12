#include <time.h> 
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


#define RANDOMSIZE 20 
#define RANDOMRANGE 100


void mergeSorting(int *array, int front, int end);
void mergeProcess(int *array, int front, int end);

int main(void){
	int *array;
	int mid;
	
	srand(time(NULL));
	array = (int*)malloc(sizeof(int) * RANDOMSIZE);
	mid = RANDOMRANGE / 2;
	
	printf("Origin array:\n\t");
	for(int i = 0; i < RANDOMSIZE; i++){
		array[i] = (rand() % RANDOMRANGE) + 1;
		printf("%d\t", array[i]);
	}
	
	printf("\n");
	
	mergeSorting(array, 0, RANDOMSIZE - 1);   //front and end are index.
	
	printf("After merge sorting(small to large):\n\t");
	for(int i = 0; i < RANDOMSIZE; i++){
		printf("%d\t", array[i]);
	}
	
	return 0;
}

void mergeProcess(int *array, int front, int end){
	int mid = (front + end) / 2;
	int LA[mid - front + 1 + 1], RA[end - mid + 1];  //last 1 is very big number. it is used to be a sentinel.
	int LAWalker, RAWalker;
	
	LAWalker = 0;
	RAWalker = 0;
	
	//left array put to LA
	for(int i = front; i <= mid; i++){
		LA[LAWalker] = array[i];
		LAWalker++;
	}
	LA[LAWalker] = INT_MAX;
	
	//right array put to RA
	RAWalker = 0;
	for(int i = mid + 1; i <= end; i++){
		RA[RAWalker] = array[i];
		RAWalker++;
	}
	RA[RAWalker] = INT_MAX;
	
	//LA and RA sort and save to array
	LAWalker = 0;
	RAWalker = 0;
	for(int i = front; i <= end; i++){
		int savedValue;
		
		if(LA[LAWalker] > RA[RAWalker]){
			savedValue = RA[RAWalker];
			RAWalker++;
		}else{
			savedValue = LA[LAWalker];
			LAWalker++;
		}
		array[i] = savedValue;
	}
}

void mergeSorting(int *array, int front, int end){
	if(front < end){
		//first priorty is left subarray sort. second priorty is right subarray sort.
		int mid = (front + end) / 2;
		mergeSorting(array, front, mid);  //divede and get left subarray(first run)
		//printf("left:%d\t %d\n", front, end);
		mergeSorting(array, mid + 1, end); //divide and get right subarray(second priorty)
		//printf("right:%d\t %d\n", front, end);
		
		mergeProcess(array,front, end);
	}
}
