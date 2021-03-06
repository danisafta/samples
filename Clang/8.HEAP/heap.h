#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>


/* We assume there is a defined primitive type Item. */

typedef struct {
    Item content;
    int prior; /* You will compare elements based on this. */
} ItemType;

typedef struct heap {
    long int capacity;
    long int size;
    ItemType *elem;
} PriQueue, *APriQueue;


APriQueue makeQueue(int capacity) {
	APriQueue q;
	q=malloc(sizeof(PriQueue));
	q->capacity=capacity;
	q->size=0;
	q->elem=malloc(capacity*sizeof(ItemType));
	return q;
}

int getLeftChild(int i) {
	return 2*i+1;
}

int getRightChild(int i) {
	return 2*i+2;
}

int getParent(int i) {
	return (i-1)/2;
}

ItemType getMax(APriQueue h) {
	//printf("%d\n", h->elem[0].content);
	return h->elem[0];
}

void siftUp(APriQueue h, int i) {
	ItemType t;

	while(i>=0 && h->elem[i].prior > h->elem[getParent(i)].prior)
	{
		t=h->elem[i];
		h->elem[i]=h->elem[getParent(i)];
		h->elem[getParent(i)]=t;
		i=getParent(i);
	}

}

void insert(APriQueue h, ItemType x) {
	if(h->size==h->capacity)
	{
		h->capacity++;
		h->elem=realloc(h->elem,sizeof(h->capacity));
	}

	h->size=h->size+1;

	h->elem[h->size-1]=x;
	siftUp(h,h->size-1);
}

void siftDown(APriQueue h, int idx) {

	int maxind=idx;
	int left=getLeftChild(idx);
	if(left<h->size && h->elem[maxind].prior<h->elem[left].prior)
	{
		maxind=left;
	}
	int right=getRightChild(idx);
	if(right<h->size && h->elem[maxind].prior<h->elem[right].prior)
	{
		if(h->elem[left].prior<h->elem[right].prior)
		{
			maxind=right;
		}
	}

	ItemType t;

	if(idx!=maxind)
	{
		t=h->elem[idx];
		h->elem[idx]=h->elem[maxind];
		h->elem[maxind]=t;
		siftDown(h,maxind);
	}
}

ItemType removeMax(APriQueue h) {
	ItemType rez=getMax(h);
	h->elem[0]=h->elem[h->size-1];
	h->elem[h->size-1]=rez;
	h->size--;
	siftDown(h,0);
	return rez;
}

#endif

