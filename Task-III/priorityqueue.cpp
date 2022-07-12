#include "priorityqueue.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>

struct Queue CreateQueue()
{
    struct Queue queue;

    struct Node *headNode = NULL;
    queue.headNode = headNode;
    queue.count = 0;

    return queue;

}

void Enqueue(struct Queue *queue, Data value, int priority) 
{
    struct Node *node = (Node*) malloc(sizeof(struct Node));
    struct Node *headNode = queue -> headNode;

    node -> value = value;
    node -> priority = priority;


    if(headNode == NULL)
    {
        node->nextNode = NULL;
        headNode = node;
    }
    else if((headNode) -> priority > priority)
    {
        node->nextNode = headNode;
        headNode = node;
    }
    else
    {
        struct Node *currentNode;
        currentNode = headNode;

        while(currentNode->nextNode != NULL && currentNode->nextNode->priority < priority)
        {
            currentNode = currentNode->nextNode;
        }

        node->nextNode = currentNode ->nextNode;
        currentNode ->nextNode = node;
    }

    queue -> headNode = headNode;
    queue -> count++;
}

void Pop(struct Queue *queue) 
{
    struct Node *temp = queue -> headNode;

    if(temp != NULL)
    {
        queue->headNode = queue->headNode->nextNode;
        free(temp);
        queue->count--;
    }
}

Data Peek(struct Queue queue)
{
    if(queue.headNode != NULL)
    {
        return queue.headNode->value;
    }
    else
    {
        Data d;
        d.priority = -1;
        return d;
    }
}

int Count(struct Queue queue)
{
    return queue.count;
}

void PrintQueue(struct Queue queue) 
{
    struct Node *current = queue.headNode;
    struct Node *headNode = queue.headNode;

    if(headNode == NULL)
    {
        printf("List is empty");
        return;
    }

    while (current != NULL) /* traverse list and print each node's value */
    {
        printf("%d ", current -> value.value.wait_time);
        current = current -> nextNode;
    }
    printf("\n");
}

int IsEmpty(struct Queue queue)
{
    if(queue.headNode == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void EmptyQueue(struct Queue *queue) 
{
    struct Node *current = queue -> headNode;
    struct Node *next;

    while (current != NULL) 
    {
        next = current -> nextNode;
        free(current);
        current = next;
    }
    queue -> headNode = NULL;
}