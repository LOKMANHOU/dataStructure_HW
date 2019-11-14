#include <stdio.h>
#include <stdlib.h>
#include "0510842_1_32.h"

int main(void){
	FILE *fp;

	struct DATA* newData;  
	struct DATA* nodeData; //show specific node's data
	struct NODE* firstNode = NULL;  //linked list head
	struct NODE* newNode;  
	struct NODE* tmpNode;   //recursive node
	struct NODE* beforeTmpNode; //previous recursive node
	
	//open file
	fp = fopen("test.txt" , "r");
	if(fp == NULL) {
		perror("open error");
		return 1;
	}
	
   	struct DATA temp; 
   	char str[60];
   	while(fgets(str, 60, fp) != NULL){
		sscanf(str, "%d %f", &temp.id, &temp.grade);
		
		//create new node	
		newData = (struct DATA*)malloc(sizeof(struct DATA));
		newData->id = temp.id;
		newData->grade = temp.grade;
		newNode = createNode(newData);	

		
		if(firstNode == NULL){
			//point the first(origin) node
			firstNode = newNode;
		}else{
			//total of node > 1
			//insert sort (from small to large)
			tmpNode = firstNode;

			beforeTmpNode = NULL;
			while(1){
				
				if(compare(&tmpNode->dataPtr->grade, &newNode->dataPtr->grade) == 1){
					//first is bigger than second
					//change the new node and the sorted linked list last node position
					newNode->link = tmpNode;
					if(beforeTmpNode == NULL){
						//first is orign node
						firstNode = newNode;
					}else{
						beforeTmpNode->link = newNode;		
					}
					break;
				}
				
				//first is small than second
				//put the new node to the sorted linked list			
				if(tmpNode->link == NULL){
					tmpNode->link = newNode;
					break;	
				}else{				
					beforeTmpNode = tmpNode;
					tmpNode = tmpNode->link;
				}
			}
			
		}
	}
	
	fclose(fp);

	printf("id\tscore(small->large)\n");
	tmpNode = firstNode;
	//show data
	while(tmpNode != NULL){
		printf("%d\t%f \n", tmpNode->dataPtr->id, tmpNode->dataPtr->grade);
		tmpNode = tmpNode->link;
	}

	system("Pause");
	return 0;
}


