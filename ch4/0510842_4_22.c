#include <stdio.h>
#include <time.h>
#include "0510842_4_22.h"


struct NODEDATA{
	int custNum;
	int arriveTime;
};

struct CUSTSTATUS{
	int custNum;
	int arriveTime;
	int startTime;
	int svcTime;
};

struct SIMSTATS{
	int numCust;
	int idleTime;
	int waitTime;
	int serviceTime;
	int maxQueueSize;
};

int endTime;
int maxServiceTime; 

void input();
void newCustomer(struct QUEUE*, int, int*);
void serverFree(struct QUEUE*, int, struct CUSTSTATUS*, int*, struct SIMSTATS*);
void svcComplete(struct QUEUE*, int, struct CUSTSTATUS*, struct SIMSTATS*, int*);
void printStats(struct SIMSTATS*);

int main(void){
	struct QUEUE* waitQueue;
	struct SIMSTATS runStas;
	struct CUSTSTATUS systemStatus;	
	int clock;
	int custNum;
	int moreCusts;  //flag
	
	runStas.idleTime = 0;
	runStas.maxQueueSize = 0;
	runStas.numCust = 0;
	runStas.serviceTime = 0;
	runStas.waitTime = 0;
	systemStatus.arriveTime = 0;
	systemStatus.svcTime = 0;
	systemStatus.startTime = 0;
	systemStatus.custNum = 0;
	
	waitQueue = createQueue();
	clock = 1;
	custNum = 0;
	moreCusts = false;	 
	srand(time(NULL));
	
	input();
	
	printf("ClockTime \t Call number \t Arrival time \t Wait time \t Start time \t Service time \t Queue size \n"); 
	
	while(clock <= endTime || moreCusts){
		if(clock <= endTime){
			newCustomer(waitQueue, clock, &custNum);
		}
		serverFree(waitQueue, clock, &systemStatus, &moreCusts, &runStas);
		svcComplete(waitQueue, clock, &systemStatus, &runStas, &moreCusts);
		
		if(!emptyQueue(waitQueue)){
			moreCusts = true;
		}
		
		clock++;
	}
	
	printStats(&runStas);
	
	return 0;
}



void newCustomer(struct QUEUE* waitQueue, int clock, int* custNum){
	int randNum = rand()%10 + 1;
	
	if(randNum <= 5){
		struct NODEDATA* custData;
		custData = (struct NODEDATA*)malloc(sizeof(struct NODEDATA));
		
		(*custNum)++;
		custData->custNum = *custNum;
		custData->arriveTime = clock;
		enQueue(waitQueue, custData);
	}
}

void serverFree(struct QUEUE* waitQueue, int clock, struct CUSTSTATUS* systemStatus, int* moreCusts, struct SIMSTATS* runStas){
	if(clock > systemStatus->startTime + systemStatus->svcTime - 1){
		if(!emptyQueue(waitQueue)){
			struct NODEDATA* newSvcCust;
			deQueue(waitQueue, (void*)&newSvcCust);
			systemStatus->custNum = newSvcCust->custNum;
			systemStatus->arriveTime = newSvcCust->arriveTime;
			systemStatus->startTime = clock;
			systemStatus->svcTime = rand() % maxServiceTime + 1;
			*moreCusts = true;
		}else{
			if(clock - (systemStatus->startTime + systemStatus->svcTime) > 0){
				runStas->idleTime++;
			}
		}
	}
}

void svcComplete(struct QUEUE* waitQueue, int clock, struct CUSTSTATUS* systemStatus, struct SIMSTATS* runStas, int* moreCusts){
	if(clock == systemStatus->startTime + systemStatus->svcTime - 1){
		int waitTime = systemStatus->startTime - systemStatus->arriveTime;
		runStas->numCust = systemStatus->custNum;
		runStas->serviceTime += systemStatus->svcTime;
		runStas->waitTime += waitTime;
		int queueSize = waitQueue->count;
		if(runStas->maxQueueSize < queueSize){
			runStas->maxQueueSize = queueSize;
		}
		
		printf("%d \t\t %d \t\t %d \t\t %d \t\t %d \t\t %d \t\t %d \n", clock, systemStatus->custNum, systemStatus->arriveTime, waitTime, systemStatus->startTime, systemStatus->svcTime, queueSize);
		*moreCusts = false;
	}
}

void printStats(struct SIMSTATS* runStas){
	printf("\n\n");
	printf("total calls:%d\n", runStas->numCust);
	printf("total idel time:%d\n", runStas->idleTime);
	printf("all wait time:%d\n", runStas->waitTime);
	printf("all service time:%d\n", runStas->serviceTime);
	printf("maximum queue size:%d\n", runStas->maxQueueSize);
	printf("average wait time:%f\n", ((float)runStas->waitTime) / runStas->numCust);
	printf("average service time:%f\n", ((float)runStas->serviceTime) / runStas->numCust);
}

void input(){
	printf("the length of time in hours that the service is provided:\n");
	scanf("%d", &endTime);
	endTime *= 60;
	printf("the maximum time it takes for the operator to take an order:\n");
	scanf("%d", &maxServiceTime);
}
