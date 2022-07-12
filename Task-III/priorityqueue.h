#ifndef priorityqueue_h
#define priorityqueue_h

#include <cstddef>
#include <cstring>

typedef struct Plane
{
    int type;
    int remaining_time;
    size_t wait_time;
} Plane;

typedef struct Data
{
    Plane value;
    int priority;
} Data;

typedef struct Queue
{
    struct Node *headNode;
    
    int count;
} Queue;

struct Node /* node struct used for implementing linked lists */
{
    Data value;
    int priority;

    struct Node *nextNode;
};

struct Queue CreateQueue(); // Returns a queue ready for use

void PrintQueue(struct Queue queue); // Prints every queue element's value.
int Count(struct Queue queue); // Returns the number of elements in the queue
void Enqueue(struct Queue *queue, Data value, int priority); // Adds an element to queue
void Pop(struct Queue *queue); // Removes one element from queue
Data Peek(struct Queue queue); // Returns the first element's value (if there are no elements, returns 0)
void EmptyQueue(struct Queue *queue); // Removes every queue element's value and frees memory
int IsEmpty(struct Queue queue); // Checks whether the queue is empty - returns 1 if empty, 0 if not.

#endif