//header file for pq.c
#ifndef HEADERS_H
#define HEADERS_H

//node'o struktura
typedef int dataType;			//'int' galima pakeisti i koki kita tipa
typedef struct qPtr
{
	struct qPtr *parent;		//rodykle i teva
	struct qPtr *child[2];		//0 - kairinis, 1 - desininis vaikas
	int priority;				//prioritetas
	dataType item;				//node'o reiksme
} qNode, *Node;
//prioritetines eiles struktura
typedef struct priorityQueue
{
	Node root;
	Node last;
} qType, *Queue;
//operacijos
Queue createPQ();				//sukurti eile
int isEmpty(Queue q);			//patikrinti ar eile tuscia
void push(Queue q, dataType item, int priority); //ideti elementa i eile
dataType pop(Queue q);			//isimti elementa su didziausiu prioritetu
dataType top(Queue q);			//grazina virsunes reiksme
void prioritize(Node n);		//rikiavimas naudojamas pop funkcijoje
void swapNodes(Node a, Node b); //apsuka du node'us
#endif
