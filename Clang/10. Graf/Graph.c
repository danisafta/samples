#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Util.h"
#include "Graph.h"

TGraphL* createGraphAdjList(int numberOfNodes) {
	TGraphL *g=(TGraphL *)malloc(sizeof(TGraphL));
	g->nn=numberOfNodes;
	g->adl=(TNode **)calloc(numberOfNodes,sizeof(TNode*));
	return g;
}

void addEdgeList(TGraphL* graph, int v1, int v2) {
	TNode *n1=malloc(sizeof(TNode));
	TNode *n2=malloc(sizeof(TNode));
	n1->v=v2;
	n2->v=v1;
	n1->next=graph->adl[v1];
	n2->next=graph->adl[v2];
	graph->adl[v1]=n1;
	graph->adl[v2]=n2;
}

List* dfsIterative(TGraphL* graph, int s) {
	//TODO
	List *path=createList();
	int *visited=(int*)calloc(graph->nn,sizeof(int));
	Stack *stack=createStack();
	push(stack,s);
	
	while(isStackEmpty(stack)!=1){

		s=top(stack);
		pop(stack);
		visited[s]=1;
		enqueue(path,s);


			for(TNode *it=graph->adl[s];it!=NULL;it=it->next){
			if(!visited[it->v])
			push(stack,it->v);	

			}


	}	
	destroyStack(stack);
	free(visited);
	return path;
}

void dfsRecHelper(TGraphL* graph, int* visited, List* path, int s) {
	//TODO
	visited[s]=1;
	enqueue(path,s);
	for(TNode *it=graph->adl[s];it!=NULL;it=it->next){
	if(!visited[it->v]) dfsRecHelper(graph,visited,path,it->v);
		
	}
}

List* dfsRecursive(TGraphL* graph, int s) {
	//TODO
	List *path=createList();
	int *visited=(int*)calloc(graph->nn,sizeof(int));
	dfsRecHelper(graph,visited,path,s);
	free(visited);
	return path;
}

List* bfs(TGraphL* graph, int s){
	
	List *path=createList();
	int *visited=(int*)calloc(graph->nn,sizeof(int));
	Queue *queue=createQueue();
	enqueue(queue,s);
	
	while(isQueueEmpty(queue)!=1){

		s=front(queue);
		dequeue(queue);
		visited[s]=1;
		


			for(TNode *it=graph->adl[s];it!=NULL;it=it->next){
			if(!visited[it->v])
				{
					enqueue(queue,it->v);
					visited[it->v]=1;	
				}
			}
	enqueue(path,s);

	}	
	destroyQueue(queue);
	free(visited);
	return path;
}


void destroyGraphAdjList(TGraphL* graph){
	for(int i=0;i<graph->nn;i++)
		free(graph->adl[i]);
	free(graph->adl);
	free(graph);
	//TODO
}

void removeEdgeList(TGraphL* graph, int v1, int v2){
	TNode* it = graph->adl[v1];
	TNode* prev = NULL;
	while(it != NULL && it->v != v2){
		prev = it;
		it = it->next;
	}

	if(it == NULL)return;

	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v1] = it->next;
	free(it);

	it = graph->adl[v2];
	prev = NULL;
	while(it != NULL && it->v != v1){
		prev = it;
		it = it->next;
	}
	if(it == NULL) return;
	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v2] = it->next;

	free(it);
}

void removeNodeList(TGraphL* graph, int v){
	for(int i = 0; i < graph->nn;i++){
		removeEdgeList(graph,v,i);
	}
}
