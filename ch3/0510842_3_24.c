#include <stdio.h>
#include "0510842_3_24.h"
#define true 1
#define false 0

int maze[10][12] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
					{1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1},
					{1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
					{1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
					{1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
					{1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
					{1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
					{1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
					{1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
					{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
int map[11][13];

struct SPOT{
	int row;
	int col;
};

enum NEIGHBORSTATE{
	EXIT = -1,
	DEADROAD = 0,
	GOAHEAD = 1,
	INTERSECTION = 2
};

enum COLOR{
	BLACK = 1,
	WHITE = 0
};


struct SPOT* createSpot();
struct SPOT* copySpot(struct SPOT*);
int canMoveSpot(struct SPOT*);
int neighborState(struct STACK*, struct SPOT*);
int neighborCheck(struct SPOT* , struct SPOT* );
int isEqualSpot(struct SPOT*, struct SPOT*);
int isExit(struct SPOT*);
void goAHeadFunc(struct STACK**);
void displayMap();
int reset(struct STACK* , struct STACK* , struct SPOT* );

int main(void){
	struct STACK* firstStack;
	struct STACK* secondStack;
	struct SPOT* lastSpot;
	int state;

	
	firstStack = createStack();
	secondStack = createStack();
	lastSpot = createSpot();
	
	//it decide the start position.
	while(true){
		struct SPOT tem;
		printf("Enter the start position:\n");
		scanf("%d %d", &tem.row, &tem.col);
		if(canMoveSpot(&tem)){
			struct SPOT* startPos = createSpot();		
			startPos->row = tem.row;
			startPos->col = tem.col;
			pushStack(firstStack, startPos);
			break;
		}
		printf("it can't set here. Please enter the new position:\n");
	}
	
	printf("\n");
	
	while(true){
		state = neighborState(firstStack, lastSpot);
		printf("(%d,%d)->", ((struct SPOT*)topStack(firstStack))->row, ((struct SPOT*)topStack(firstStack))->col);  //
		map[((struct SPOT*)topStack(firstStack))->row][((struct SPOT*)topStack(firstStack))->col] += 1;
		if(state == EXIT){

			printf("Exit\n\n");

			displayMap();
			
			if(!reset(firstStack, secondStack, lastSpot))
				break;
			else{
				while(true){
					struct SPOT tem;
					printf("Enter the start position:\n");
					scanf("%d %d", &tem.row, &tem.col);
					if(canMoveSpot(&tem)){
						struct SPOT* startPos = createSpot();		
						startPos->row = tem.row;
						startPos->col = tem.col;
						pushStack(firstStack, startPos);
						break;
					}
					printf("it can't set here. Please enter the new position:\n");
				}
				continue;
			}
		}else if(state == DEADROAD){

			struct SPOT* token = createSpot();
			int tokenNum = 0;
			int gameover = 0;
				
			while(!isEqualSpot((struct SPOT*)topStack(firstStack), token)){
				popStack(firstStack);
				
				if(countStack(firstStack) != 0 && countStack(secondStack) != 0 && !isEqualSpot((struct SPOT*)topStack(firstStack), token)){
					printf("(%d,%d)*->", ((struct SPOT*)topStack(firstStack))->row, ((struct SPOT*)topStack(firstStack))->col);  //
					map[((struct SPOT*)topStack(firstStack))->row][((struct SPOT*)topStack(firstStack))->col] += 1;
				}
				
				if(countStack(firstStack) == 0){
					printf("gameover\n");
					displayMap();
					gameover = true;
					break;
				}
				
			}
			
			if(gameover){
				if(!reset(firstStack, secondStack, lastSpot))
					break;
				else{
					while(true){
						struct SPOT tem;
						printf("Enter the start position:\n");
						scanf("%d %d", &tem.row, &tem.col);
						if(canMoveSpot(&tem)){
							struct SPOT* startPos = createSpot();		
							startPos->row = tem.row;
							startPos->col = tem.col;
							pushStack(firstStack, startPos);
							break;
						}
						printf("it can't set here. Please enter the new position:\n");
					}
					continue;
				}
			}
			
			while(isEqualSpot((struct SPOT*)topStack(firstStack), token)){
				tokenNum++;
				popStack(firstStack);
			}
			
			printf("(%d,%d)*->", ((struct SPOT*)topStack(firstStack))->row, ((struct SPOT*)topStack(firstStack))->col);  //
			map[((struct SPOT*)topStack(firstStack))->row][((struct SPOT*)topStack(firstStack))->col] += 1;
			lastSpot = copySpot((struct SPOT*)topStack(firstStack));
			int i;
			for(i = 1; i <= (tokenNum - 1); i++){
				pushStack(firstStack, createSpot());
			}
			

			
			pushStack(firstStack, (struct SPOT*)popStack(secondStack));
			
		}else if(state == GOAHEAD){

			struct SPOT* currentSpot;
			struct SPOT* neighborSpot;
			currentSpot = createSpot();
			neighborSpot = createSpot();
	
			currentSpot->row = ((struct SPOT*)topStack(firstStack))->row;
			currentSpot->col = ((struct SPOT*)topStack(firstStack))->col;
			
			//left
			neighborSpot->row = currentSpot->row;
			neighborSpot->col = currentSpot->col - 1;
			if(neighborCheck(neighborSpot, lastSpot) == WHITE){
				lastSpot = copySpot(currentSpot);
				pushStack(firstStack, copySpot(neighborSpot));
				
				free(currentSpot);
				free(neighborSpot);
				continue;
			}
			
			//right
			neighborSpot->row = currentSpot->row;
			neighborSpot->col = currentSpot->col + 1;
			if(neighborCheck(neighborSpot, lastSpot) == WHITE){
				lastSpot = copySpot(currentSpot);
				pushStack(firstStack, copySpot(neighborSpot));
				
				free(currentSpot);
				free(neighborSpot);
				continue;
			}
			
			//upper
			neighborSpot->row = currentSpot->row - 1;
			neighborSpot->col = currentSpot->col;
			if(neighborCheck(neighborSpot, lastSpot) == WHITE){
				lastSpot = copySpot(currentSpot);
				pushStack(firstStack, copySpot(neighborSpot));
				
				free(currentSpot);
				free(neighborSpot);
				continue;
			}
			
			//below
			neighborSpot->row = currentSpot->row + 1;
			neighborSpot->col = currentSpot->col;
			
			
			if(neighborCheck(neighborSpot, lastSpot) == WHITE){
				lastSpot = copySpot(currentSpot);
				pushStack(firstStack, copySpot(neighborSpot));
				
				free(currentSpot);
				free(neighborSpot);
				continue;
			}
			
			
			
		}else if(state == INTERSECTION){
				
			struct SPOT* currentSpot;
			struct SPOT* neighborSpot;
			currentSpot = createSpot();
			neighborSpot = createSpot();
	
			currentSpot->row = ((struct SPOT*)topStack(firstStack))->row;
			currentSpot->col = ((struct SPOT*)topStack(firstStack))->col;
			
			//left
			neighborSpot->row = currentSpot->row;
			neighborSpot->col = currentSpot->col - 1;
			if(neighborCheck(neighborSpot, lastSpot) == WHITE){
				pushStack(firstStack, createSpot());
				pushStack(secondStack, copySpot(neighborSpot));
			}
			
			//right
			neighborSpot->row = currentSpot->row;
			neighborSpot->col = currentSpot->col + 1;
			if(neighborCheck(neighborSpot, lastSpot) == WHITE){
				pushStack(firstStack, createSpot());
				pushStack(secondStack, copySpot(neighborSpot));
				
			}
			
			//upper
			neighborSpot->row = currentSpot->row - 1;
			neighborSpot->col = currentSpot->col;
			if(neighborCheck(neighborSpot, lastSpot) == WHITE){
				pushStack(firstStack, createSpot());
				pushStack(secondStack, copySpot(neighborSpot));
				
			}
			
			//below
			neighborSpot->row = currentSpot->row + 1;
			neighborSpot->col = currentSpot->col;
			if(neighborCheck(neighborSpot, lastSpot) == WHITE){
				pushStack(firstStack, createSpot());
				pushStack(secondStack, copySpot(neighborSpot));
			}
			
			lastSpot = copySpot(currentSpot);
			popStack(firstStack);
			pushStack(firstStack, (struct SPOT*)popStack(secondStack));
			
			free(currentSpot);
			free(neighborSpot);
			continue;
		}
	}
	
	
	return 0;
}

int reset(struct STACK* firstStack, struct STACK* secondStack, struct SPOT* lastSpot){
	int ans;
	printf("Continue?1:yes,0:no\n");
	scanf("%d", &ans);
	if(ans){
		while(countStack(firstStack))
			popStack(firstStack);
		while(countStack(secondStack))
			popStack(secondStack);
		lastSpot->row = -1;
		lastSpot->col = -1;
		int i,j;
		for(i = 0; i < 11; i++)
			for(j = 0; j < 13; j++)
				map[i][j] = 0;
		
		return true;
	}
	
	return false;
}

void displayMap(){
	int i;
	int j;
	for(i =1; i < 11; i++){
		for(j = 1; j < 13; j++){
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}

struct SPOT* copySpot(struct SPOT* spot){
	struct SPOT* newSpot = createSpot();
	
	newSpot->row = spot->row;
	newSpot->col = spot->col;
	
	return newSpot;
}

int neighborCheck(struct SPOT* neighborSpot, struct SPOT* lastSpot){  //
	if(!isEqualSpot(neighborSpot, lastSpot)){
		if(isExit(neighborSpot)){
			return EXIT;
		}
		if(canMoveSpot(neighborSpot)){
			return WHITE;
		}
	}
	return BLACK;
}


int neighborState(struct STACK* firstStack, struct SPOT* lastSpot){  //firstStack get current spot
	int whiteNum = 0;
	int oneState;
	struct SPOT* currentSpot;
	struct SPOT* neighborSpot;
	currentSpot = createSpot();
	neighborSpot = createSpot();
	
	currentSpot->row = ((struct SPOT*)topStack(firstStack))->row;
	currentSpot->col = ((struct SPOT*)topStack(firstStack))->col;
	
	//left
	neighborSpot->row = currentSpot->row;
	neighborSpot->col = currentSpot->col - 1;
	oneState = neighborCheck(neighborSpot, lastSpot);
	if(oneState == EXIT){
		free(currentSpot);
		free(neighborSpot);
		return EXIT;
	}else if(oneState == WHITE){
		whiteNum++;
	}
	
	//right
	neighborSpot->row = currentSpot->row;
	neighborSpot->col = currentSpot->col + 1;
	oneState = neighborCheck(neighborSpot, lastSpot);
	if(oneState == EXIT){
		free(currentSpot);
		free(neighborSpot);
		return EXIT;
	}else if(oneState == WHITE){
		whiteNum++;
	}
	
	//upper
	neighborSpot->row = currentSpot->row - 1;
	neighborSpot->col = currentSpot->col;
	oneState = neighborCheck(neighborSpot, lastSpot);
	if(oneState == EXIT){
		free(currentSpot);
		free(neighborSpot);
		return EXIT;
	}else if(oneState == WHITE){
		whiteNum++;
	}
	
	//below
	neighborSpot->row = currentSpot->row + 1;
	neighborSpot->col = currentSpot->col;
	oneState = neighborCheck(neighborSpot, lastSpot);
	if(oneState == EXIT){
		free(currentSpot);
		free(neighborSpot);
		return EXIT;
	}else if(oneState == WHITE){
		whiteNum++;
	}
	
	free(currentSpot);
	free(neighborSpot);
	
	if(whiteNum == 1)
		return GOAHEAD;
	else if(whiteNum == 0)
		return DEADROAD;
	
	return INTERSECTION;	//whiteNum > 1	
}


int isExit(struct SPOT* spot){
	if(spot->col < 0 || spot->col > 12){
		return true;
	}else if(spot->row < 0 || spot->row > 10){
		return true;
	}
	return false;
}

int isEqualSpot(struct SPOT* a, struct SPOT* b){
	if(a->row == b->row){
		if(a->col == b->col){
			return true;
		}
	}
	return false;
}

struct SPOT* createSpot(){
	struct SPOT* tem = (struct SPOT*)malloc(sizeof(struct SPOT));
	tem->row = -1;
	tem->col = -1;
	return tem;
}

int canMoveSpot(struct SPOT* spot){
	if(maze[spot->row - 1][spot->col - 1] == WHITE)
		return true;
	return false;	
}
