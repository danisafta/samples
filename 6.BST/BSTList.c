/*
 * BSTList.c
 *
 *  Created on: Apr 2, 2016
 *      Author: dan
 */

typedef long Item;
#include "BST.h"
typedef BSTNode* Item2;
#include "List.h"
#include "Queue.h"


BSTree* buildTree(Item *array, long len);

// -----------------------------------------------------------------------------
List* bstToList(BSTree* tree){ 
	//TODO: Cerinta 4
}
void printList(List* list){
	//TODO: Cerinta 4
}
// -----------------------------------------------------------------------------

int main(void){
	Item array[] = {5,3,2,4,7,6,8};

	BSTree *tree = buildTree(array, sizeof(array)/sizeof(Item));	

	//printList(list);

	destroyTree(tree);

	return 0;
}

BSTree* buildTree(Item *array, long len){
	BSTree* newTree = createTree();
	for(int i = 0; i < len; i++){
		insert(newTree,array[i]);
	}
	return newTree;
}
