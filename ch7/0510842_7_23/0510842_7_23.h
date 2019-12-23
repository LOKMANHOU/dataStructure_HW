#ifndef _0510842_7_23
#define _0510842_7_23

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//	Structure Declarations 
struct NODE{
	int pos;
	void* dataPtr;
	int left;
	int right;
};

struct BST_TREE{
	struct NODE** array;
	int count;
	int rootIndex;
	int maxSize;
	int (*compare) (void* argu1, void* argu2);
};
	
//	Prototype Declarations 
struct BST_TREE* BST_Create(int maxSize, int (*compare) (void* argu1, void* argu2));
struct BST_TREE* BST_Destroy(struct BST_TREE* tree);

bool  BST_Insert   (struct BST_TREE* tree, void* dataPtr);
bool  BST_Delete   (struct BST_TREE* tree, void* dltKey);
void* BST_Retrieve (struct BST_TREE* tree, void* keyPtr);
void  BST_Traverse (struct BST_TREE* tree, void (*process)(void* dataPtr));

bool BST_Empty (struct BST_TREE* tree);
bool BST_Full  (struct BST_TREE* tree);
int  BST_Count (struct BST_TREE* tree);

static int _insert(struct BST_TREE* tree, int rootIndex, struct NODE* newPtr); 
static int _delete(struct BST_TREE* tree, int rootIndex, void* dataPtr, bool* success);
static void* _retrieve(struct BST_TREE* tree, void* dataPtr, int rootIndex);
static void _traverse(struct BST_TREE* tree, int rootIndex, void (*process) (void* dataPtr));
static void _destroy (struct BST_TREE* tree, int rootIndex);


struct BST_TREE* BST_Create(int maxSize, int (*compare) (void* argu1, void* argu2)){
	struct BST_TREE *tree;
	int i;
	
	tree = (struct BST_TREE*)malloc(sizeof(struct BST_TREE));
	if(tree){
		tree->count = 0;
		tree->rootIndex = 0;
		tree->maxSize = maxSize;
		tree->array = (struct NODE**)malloc(sizeof(struct NODE*) * maxSize);
		for(i = 0; i < tree->maxSize; i++)
			tree->array[i] = NULL;
		tree->compare = compare;
	}
	
	return tree;
}

bool BST_Insert(struct BST_TREE* tree, void* dataPtr){
	struct NODE* newPtr;
	int i;
	
	newPtr = (struct NODE*)malloc(sizeof(struct NODE));
	if(!newPtr)
		return false;
		
	if(BST_Full(tree)){
		printf("array is full.\n");
		return false;
	}
	
	newPtr->dataPtr = dataPtr;
	newPtr->left = -1;
	newPtr->right = -1;
	for(i = 0; i < tree->maxSize; i++){
		if(!tree->array[i]){
			tree->array[i] = newPtr;
			newPtr->pos = i;
			break;	
		}
	}
	//printf("index:%d\n", newPtr->pos);
	if(tree->count == 0){
		tree->array[tree->rootIndex] = newPtr;
	}else{
		_insert(tree, tree->rootIndex, newPtr);
	}
	(tree->count)++;
	return true;
}

static int _insert(struct BST_TREE* tree, int rootIndex, struct NODE* newPtr){
	if(rootIndex == -1){
		return newPtr->pos;
	}
	
	if(tree->compare(newPtr->dataPtr, tree->array[rootIndex]->dataPtr) < 0){
		tree->array[rootIndex]->left = _insert(tree, tree->array[rootIndex]->left, newPtr);
	}else{
		tree->array[rootIndex]->right = _insert(tree, tree->array[rootIndex]->right, newPtr);
	}
	return rootIndex;
}

bool  BST_Delete(struct BST_TREE* tree, void* dltKey){
	bool success;
	int newRoot;
	
	newRoot = _delete(tree, tree->rootIndex, dltKey, &success);
	if(success){
		tree->rootIndex = newRoot;
		(tree->count)--;
		if(tree->count == 0)
			tree->rootIndex = 0;
	}
	return success;
}

static int _delete(struct BST_TREE* tree, int rootIndex, void* dataPtr, bool* success){
	int dltIndex;
	int exchIndex;
	int newRoot;
	void* holdPtr;
	
	if(rootIndex == -1){
		*success = false;
		return -1;
	}
	
	if(tree->compare(dataPtr, tree->array[rootIndex]->dataPtr) < 0)
		tree->array[rootIndex]->left = _delete(tree, tree->array[rootIndex]->left, dataPtr, success);
	else if(tree->compare(dataPtr, tree->array[rootIndex]->dataPtr) > 0)
		tree->array[rootIndex]->right = _delete(tree, tree->array[rootIndex]->right, dataPtr, success);
	else{
		dltIndex = rootIndex;
		if(tree->array[dltIndex]->left == -1){
			free(tree->array[dltIndex]->dataPtr);
			newRoot = tree->array[dltIndex]->right;
			free(tree->array[dltIndex]);
			*success = true;
			return newRoot;
		}else{
		 	if(tree->array[dltIndex]->right == -1){
				free(tree->array[dltIndex]->dataPtr);
				newRoot = tree->array[dltIndex]->left;
				free(tree->array[dltIndex]);
				*success = true;
				return newRoot;
			}else{
				exchIndex = tree->array[rootIndex]->left;
				while(tree->array[exchIndex]->right != -1)
					exchIndex = tree->array[exchIndex]->right;
			
				holdPtr = tree->array[rootIndex]->dataPtr;
				tree->array[rootIndex]->dataPtr = tree->array[exchIndex]->dataPtr;
				tree->array[exchIndex]->dataPtr = holdPtr;
				tree->array[rootIndex]->left = _delete(tree, tree->array[rootIndex]->left,
											tree->array[exchIndex]->dataPtr, success);	
			}
		}
	}	
	return rootIndex;	
}

void* BST_Retrieve (struct BST_TREE* tree, void* keyPtr){
	if(tree->count != 0)
		return _retrieve(tree, keyPtr, tree->rootIndex);
	else
		return NULL;
}

static void* _retrieve(struct BST_TREE* tree, void* dataPtr, int rootIndex){
	if(rootIndex != -1){
		if(tree->compare(dataPtr, tree->array[rootIndex]->dataPtr) < 0)
			return _retrieve(tree, dataPtr, tree->array[rootIndex]->left);
		else if(tree->compare(dataPtr, tree->array[rootIndex]->dataPtr) > 0)
			return _retrieve(tree, dataPtr, tree->array[rootIndex]->right);
		else
			return tree->array[rootIndex]->dataPtr;
	}else{
		return NULL;
	}
}

void  BST_Traverse (struct BST_TREE* tree, void (*process)(void* dataPtr)){
	_traverse(tree, tree->rootIndex, process);
}

static void _traverse(struct BST_TREE* tree, int rootIndex, void (*process) (void* dataPtr)){
	if(rootIndex != -1 && tree->count != 0){
		_traverse(tree, tree->array[rootIndex]->left, process);
		process(tree->array[rootIndex]->dataPtr);
		_traverse(tree, tree->array[rootIndex]->right, process);
	}
}

bool BST_Empty (struct BST_TREE* tree){
	return (tree->count == 0);
}
bool BST_Full  (struct BST_TREE* tree){
	return (tree->count == tree->maxSize);
}
int  BST_Count (struct BST_TREE* tree){
	return (tree->count);
}

struct BST_TREE* BST_Destroy(struct BST_TREE* tree){
	if(tree->count != 0)
		_destroy(tree, tree->rootIndex);
	free(tree);
	return NULL;
}

static void _destroy (struct BST_TREE* tree, int rootIndex){
	if(rootIndex != -1){
		_destroy(tree, tree->array[rootIndex]->left);
		free(tree->array[rootIndex]->dataPtr);
		_destroy(tree, tree->array[rootIndex]->right);
		free(tree->array[rootIndex]);
	}
}

#endif
