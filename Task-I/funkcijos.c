#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

// eiles sukurimas
Queue createPQ()
{
	Queue q = malloc(sizeof(qType));
	if (q != NULL)
	{
		q->root = NULL;
		q->last = NULL;
	}
	return q;
}
//patikrina ar eile netuscia
int isEmpty(Queue q)
{
	return q->root == NULL;
}
//ideda elementa i eile
void push(Queue q, dataType item, int priority)
{
	if(isEmpty(q) == 1)	//jeigu tuscias, tiesiog sukuria virsune
	{
		Node n = malloc(sizeof(qNode));
		q->root = n;
		q->last = n;
		n->parent = NULL;
		n->child[0] = NULL;
		n->child[1] = NULL;
		n->item = item;
		n->priority = priority;
		return;
	}
	//keliaujam nuo desines i virsu
	Node current = q->last;
	while(current->parent != NULL && current == current->parent->child[1])
		{
			current = current->parent;
		}

	if(current->parent != NULL)
	{
		if(current->parent->child[1] != NULL)
		{
			//priskiriam desinio vaiko kairiniam vaikui
			current = current->parent->child[1];
			while(current->child[0] != NULL)
			{
				current = current->child[0];
			}
		}
		else
		{
			//naujas node'as bus desinys vaikas
			current = current->parent;
		}
	}
	else
	{
		//virsune, reiskia naujas node'as bus naujam lygi kaireje
		while(current->child[0] != NULL)
		{
			current = current->child[0];
		}
	}
	//check if current->link[1] != NULL?

	//sukuriam nauja node'a
	Node n = malloc(sizeof(qNode));
	q->last = n;
	current->child[current->child[0] != NULL] = n;
	n->parent = current;
	n->child[0] = NULL;
	n->child[1] = NULL;
	n->item = item;
	n->priority = priority;

	//sort'inam pagal prioriteta
	while(n->parent != NULL && n->parent->priority < n->priority)
	{
		swapNodes(n, n->parent);
		n = n -> parent;
	}
}
void swapNodes(Node a, Node b)
{
	dataType tempItem = a->item;
	int tempPriority = a->priority;
	a->item = b->item;
	a->priority = b->priority;
	b->item = tempItem;
	b->priority = tempPriority;
}
//isima pirma (prioritetini) elementa
dataType pop(Queue q)
{
	if(isEmpty(q) == 1)
	{
		printf("cannot pop because queue is empty\n");
		return 0;
	}
	dataType tempItem = q->root->item;
	if(q->root->child[0] == NULL && q->root->child[1] == NULL)
	{
		free(q);
		q = createPQ();
		return tempItem;
	}
	else if(q->root->child[0] != NULL && q->root->child[1] == NULL)
	{
		Node helper = q->root;
		q->root->item = q->last->item;
		q->root->priority = q->last->priority;
		q->root = q->last;
		free(helper);
		return tempItem;
	}
	//i virsune ideti eiles galo reiksme ir prioriteta
	q->root->item = q->last->item;
	q->root->priority = q->last->priority;
	//atjungti paskutini node'a
	Node current = q->last;
	//ieskom priespaskutinio node'o
	while(current->parent != NULL && current == current->parent->child[0])
	{
		//ieskom eiles desines puses
		current = current->parent;
	}
	if(current->parent != NULL)
	{
		//persimetam i kaire puse
		current = current->parent->child[0];
	}
	while(current->child[1] != NULL)
	{
		//randam priespaskutini node'a
		current = current->child[1];
	}
	Node help = q->last->parent;
	if(help->child[0] == q->last)
	{
		help->child[0] = NULL;
	}
	help->child[1] = NULL;
	free(q->last);
	q->last = current;
	//perrikiuoti eile
	prioritize(q->root);
	// grazinti virsunes reiksme;
	return tempItem;
}
dataType top(Queue q)
{
	if(isEmpty(q) == 1)
	{
		printf("Cannot get top node, because queue is empty\n");
		return 0;
	}
	return q->root->item;
}
void prioritize(Node n)
{
	if (n->child[0] != NULL && n->child[1] != NULL)
	{
		if (n->priority < n->child[0]->priority && n->priority < n->child[1]->priority)
		{
			if (n->child[0]->priority < n->child[1]->priority)
			{ //desinys
				swapNodes(n, n->child[1]);
				prioritize(n->child[1]);
			}
			else
			{ //kairys
				swapNodes(n, n->child[0]);
				prioritize(n->child[0]);
			}
		}
		else if (n->priority <= n->child[0]->priority && n->priority > n->child[1]->priority)
		{
			// kairys didesnis ir desinys mazesnis
			swapNodes(n, n->child[0]);
			prioritize(n->child[0]);
		}
		else if (n->priority > n->child[0]->priority && n->priority <= n->child[1]->priority)
		{	// desinys didesnis ir kairys mazesnis
			swapNodes(n, n->child[1]);
			prioritize(n->child[1]);
		}
	}
	else if (n->child[1] == NULL && n->child[0] != NULL)
	{	// yra tik kairys vaikas
		if (n->child[0]->priority >= n->priority)
		{	// ir jis didesnis
			swapNodes(n, n->child[0]);
		}
		// pagal ideja sitoj vietoj gaunasi pabaiga
	}
}
