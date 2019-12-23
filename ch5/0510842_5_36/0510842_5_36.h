#include <stdlib.h> 

#define false 0
#define true 1
#define COMPARE ( (*(pList->compare))(pArgu, (*pLoc)->dataPtr) )
#define COMPARE_LAST ( (*(pList->compare))(pArgu, pList->rear->dataPtr) )

struct NODE{
	void* dataPtr;
	struct NODE* forwardLink;
	struct NODE* backwardLink;
};

struct LIST{
	int count;
	struct NODE* pos;
	struct NODE* head;
	struct NODE* rear;
	int (*compare)(void* argu1, void* argu2);  //return 1: first > second, 0: first = second, -1: first < second
};

struct LIST* createList(int (*compare)(void* argu1, void* argu2));
struct LIST* destroyList(struct LIST* pList);
int addNode(struct LIST* pList, void* dataInPtr);										// return 0: OK, 1: found, -1: inserting error.
int removeNode(struct LIST* pList, void* keyPtr, void** dataOutPtr);
int searchList(struct LIST* pList, void* pArgu, void** pDataOut);
int retrieveNode(struct LIST* pList, void* pArgu, void** dataOutPtr);
int traverse(struct LIST* pList, int fromWhere, void** dataOutPtr);
int countList(struct LIST* pList);
int emptyList(struct LIST* pList);
int fullList(struct LIST* pList);
static int _insert(struct LIST* pList, struct NODE* pPre, void* dataInPtr);
static void _delete(struct LIST* pList, struct NODE* pPre, struct NODE* pLoc, void** dataOutPtr);
static int _search(struct LIST* pList, struct NODE** pPre, struct NODE** pLoc, void* pArgu);



struct LIST* createList(int (*compare)(void* argu1, void* argu2)){
	struct LIST* pList;
	
	pList = (struct LIST*)malloc(sizeof(struct LIST));
	if(pList){
		pList->head = NULL;
		pList->pos = NULL;
		pList->rear = NULL;
		pList->count = 0;
		pList->compare = compare;
	}
	
	return pList;
}

int addNode(struct LIST* pList, void* dataInPtr){
	int found;
	int success;
	
	struct NODE* pPre;
	struct NODE* pLoc;
	
	found = _search(pList, &pPre, &pLoc, dataInPtr);
	if(found)
		return 1;
	
	success = _insert(pList, pPre, dataInPtr);
	
	if(!success)
		return -1;
	
	return 0;
}

static int _insert(struct LIST* pList, struct NODE* pPre, void* dataInPtr){
	struct NODE* pNew;
	
	if(!(pNew = (struct NODE*)malloc(sizeof(struct NODE)))){
		return false;
	}
	
	pNew->dataPtr = dataInPtr;
	
	if(pPre == NULL){
		pNew->backwardLink = NULL; 
		pNew->forwardLink = pList->head;
		
		if(pList->head != NULL)
			pList->head->backwardLink = pNew;
		
		pList->head = pNew;
		if(pList->count == 0){
			pList->rear = pNew;
		}
	}else{
		pNew->forwardLink = pPre->forwardLink;
		pNew->backwardLink = pPre;
		
		if(pPre->forwardLink == NULL)
			pList->rear = pNew;
		else
			pPre->forwardLink->backwardLink = pNew;
		pPre->forwardLink = pNew;
	}

	(pList->count)++;
	return true;
}

static int _search(struct LIST* pList, struct NODE** pPre, struct NODE** pLoc, void* pArgu){
	int result;
	
	*pPre = NULL;
	*pLoc = pList->head;   //it's my position.
	
	if(pList->count == 0)
		return false;
	
	if(COMPARE_LAST > 0){  //return 1: first > second, 0: first = second, -1: first < second
		*pPre = pList->rear; 
		*pLoc = NULL;
		return false;
	}
	
	while((result = COMPARE) > 0){ //return 1: first > second, 0: first = second, -1: first < second
		*pPre = *pLoc;
		*pLoc = (*pLoc)->forwardLink; 
	}
	
	if(result == 0){
		return true;
	}
	else
		return false;
}

//
int removeNode(struct LIST* pList, void *keyPtr, void** dataOutPtr){
	int found;
	struct NODE* pPre;
	struct NODE* pLoc;
	
	found = _search(pList, &pPre, &pLoc, keyPtr);
	if(found)
		_delete(pList, pPre, pLoc, dataOutPtr);  //it don't need "&" because dataOutPtr variable is the origin pointer address.   
		
	return found;
}
//
static void _delete(struct LIST* pList, struct NODE* pPre, struct NODE* pLoc, void** dataOutPtr){
	*dataOutPtr = pLoc->dataPtr;
	if(pPre == NULL)
		pList->head = pLoc->forwardLink;
	else
		pPre->forwardLink = pLoc->forwardLink;
	
	if(pLoc->forwardLink == NULL)
		pList->rear = pPre;
		
	pList->count--;
	free(pLoc);
	
	return;
}

int searchList(struct LIST* pList, void* pArgu, void** pDataOut){
	int found;
	struct NODE* pPre;
	struct NODE* pLoc;
	
	found = _search(pList, &pPre, &pLoc, pArgu);
	//printf("found:%d\n", found);
	if(found){
		*pDataOut = pLoc->dataPtr;	
	}
	else{
		*pDataOut = NULL;
	}
	
	return found;	
}

int retrieveNode(struct LIST* pList, void* pArgu, void** dataOutPtr){
	int found;
	struct NODE* pPre;
	struct NODE* pLoc;
	
	found = _search(pList, &pPre, &pLoc, pArgu);
	if(found){
		*dataOutPtr = pLoc->dataPtr;
		return true;
	}
	
	*dataOutPtr = NULL;
	return false; 
}

int emptyList(struct LIST* pList){
	return (pList->count == 0);
}

int fullList(struct LIST* pList){
	struct NODE* temp;
	
	if((temp = (struct NODE*)malloc(sizeof(struct NODE)))){
		free(temp);
		return false;
	}
	
	return true;
}

int countList(struct LIST* pList){
	return pList->count;
}

int traverse(struct LIST* pList, int fromWhere, void** dataPtrOut){
	if(pList->count == 0)
		return false;
	if(fromWhere == 0){
		pList->pos = pList->head;
		*dataPtrOut = pList->pos->dataPtr;
		return true;
	}else{
		if(pList->pos->forwardLink == NULL)
			return false;
		else{
			pList->pos = pList->pos->forwardLink;
			*dataPtrOut = pList->pos->dataPtr;
			return true;
		}
	}
}

struct LIST* destroyList(struct LIST* pList){
	struct NODE* deletePtr;
	
	if(pList){
		while(pList->count > 0){
			free(pList->head->dataPtr);
			
			deletePtr = pList->head;
			pList->head = pList->head->forwardLink;
			pList->count--;
			free(deletePtr);
		}
		free(pList);
	}
	return NULL;
}


