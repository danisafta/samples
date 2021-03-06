#ifndef BST_H_
#define BST_H_

#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just assume
  some type T was previously defined.
 */

// -----------------------------------------------------------------------------

/*
 * !!!!ATENTION!!!!
 * 1. This implementation uses two sentinels (dummy nodes) root and nil.
 * 2. The convetion is that we always root the tree at root->l (the left of the root sentinel)
 */

typedef struct BSTNode{
	Item elem;
	struct BSTNode *p; // parent - not really needed, but simplifies implementation.
	struct BSTNode *l; // left child.
	struct BSTNode *r; // right child.
}BSTNode;

typedef struct BSTree{
	long size; // This inintially is 0, and is updated by insert/delete
	BSTNode *root; // The sentinel root (a sentinel not the actual root). The actual root node is root->l !
	BSTNode *nil; // The nil sentinel to avoid checks for NULL:
}BSTree;

// TODO: Cerinta 1 si 2

/*
 * IMPLEMENTATION ORDER:
 * 1.  createTree
 * 2.  isEmpty
 * 3.  insert
 * 4.  search
 * 5.  minimum
 * 6.  maximum
 * 7.  successor 
 * 8.  predecessor
 * 9.  destroyTree
 */


BSTree* createTree(){

	BSTree *t=(BSTree*)malloc(sizeof(BSTNode));
	t->nil=(BSTNode*) malloc(sizeof(BSTNode));
	t->nil->l=t->nil->r=t->nil->p=t->nil;
	t->root=(BSTNode*)malloc(sizeof(BSTNode));
	t->root->l=t->root->r=t->root->p=t->nil;

}
int isEmpty(BSTree *t){
	return (t->root->l==t->nil);
}
void insert (BSTree *t, Item elem){

	BSTNode* y=t->root;
	BSTNode* x=t->root->l;
	while( x != t->nil ){
		y=x;
		if( elem < x->elem ) x= x->l;
		else if( elem > x->elem) x=x->r;
		else return;
	}
	BSTNode* n=(BSTNode *)malloc(sizeof(BSTNode));
	n->l=n->r=t->nil;
        n->elem = elem;
	n->p=y;
	if( ( y == t->root ) || ( elem < y->elem )) y->l=n;
	else y->r = n;
	t->size++;
}

BSTNode* search(BSTree *t, Item elem){
	BSTNode *x=t->root->l;
	while( x != t->nil ){
		if( x->elem == elem ) return x;
		else if( elem < x->elem) x=x->l;
			else x=x->r; 
	}
	if( x==t->nil && x->elem == elem ) return x;
	else return NULL;
}
BSTNode* minimum(BSTree *t,BSTNode *n) {
	BSTNode *y=t->root;
	BSTNode *x=t->root->l;
	while( x != t->nil ){
		y=x;
		x=x->l;	
	}
	return y;
}
BSTNode* maximum(BSTree *t,BSTNode *n){
	BSTNode *y=t->root;
	BSTNode *x=t->root->l;
	while( x != t->nil ){
		y=x;
		x=x->r;	
	}
	return y;
}
BSTNode* successor(BSTree *t,BSTNode *x){
        if ( x==NULL ) return NULL;
        if (x->r != t->nil )
                return minimum(t,x->r);
        BSTNode *y = x->p;
        while( y!=t->root && y->r==x){
        x=y;
        y=y->p;        
        }
        if(y==t->root) return NULL;
        return y;
}
BSTNode* predecessor(BSTree *t,BSTNode *x){
        if ( x==NULL ) return NULL;
        if (x->l != t->nil )
                return maximum(t,x->l);
        BSTNode *y = x->p;
        while( y!=t->root && y->l==x){
        x=y;
        y=y->p;        
        }
        if(y==t->root) return NULL;
        return y;}


void dst(BSTree *t, BSTNode *n){
        if( n != t->nil ){   
                if( n->l != t->nil ) dst(t,n->l);
                if( n->r != t->nil ) dst(t,n->r);
                free(n);
        }
} 
void destroyTree(BSTree *t){
        if( !isEmpty(t) ) dst(t,t->root->l);
        free(t->root);
        free(t->nil);
        free(t);
}

void delete(BSTree* tree, Item elem){
	BSTNode* z; // node to be deleted
	BSTNode* y; // Node that is spliced out
	BSTNode* x; // The child of the sliced out node

	// Needed to maintain a similar interface as in the previous labs
	if( (z = search(tree,elem)) == tree->nil)
		return;

	/*
	 * Note:
	 * Case 1: The node has no children
	 * Case 2: The node has one child
	 * Case 3: The node has two children
	 */

	// Are we in cases 1,2 or in case 3
	y = ( (z->l == tree->nil) || (z->r == tree->nil) ) ? z : successor(tree, z);

	// Set x to the child of y
	x = (y->l == tree->nil) ? y->r : y->l;

	/*
	 * Note:
	 * There is no need to check if x is a valid pointer, we have the sentinels!
	 */
	if (tree->root == (x->p = y->p)) // assignment of y->p to x->p is intentional
		tree->root->l = x;
	else if (y == y->p->l)
		y->p->l = x;
	else
		y->p->r = x;

	if (y != z){

		/*
		 * Note:
		 * The data type T might be a very big structure, thus copying the key
		 * from one node to another might be very inefficient. It is better to
		 * modify the actual links.
		 */

		// y is the node to splice out and x is its child
		y->l = z->l;
		y->r = z->r;
		y->p = z->p;
		z->l->p = z->r->p = y;
		if (z == z->p->l) z->p->l = y;
		else z->p->r = y;
		free(z);
	} else {
		free(y);
	}

	tree->size--;
}

#endif /* BST_H_ */

