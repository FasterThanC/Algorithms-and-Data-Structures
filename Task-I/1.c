#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct List{    //List - queue

    int elementCount;
    int priority;
    int value;
    struct List *next;   //
}List;

void deleteQueue(int index);
void addQueue();
void queueClear(int index);
void enqueue(int priority, int value, int index, int MAX_ELEMENTS);
int dequeue(int index);
int isEmpty(int index);
int getFirst(int index);
void printQueue(int index);


int queueExists[100];
int elementCount[100];
int queues = 0;
int newIndex;

List **queue;



int main(){

    int priority, value;

    int runPriorityQueue = 1;

    int MAX_ELEMENTS;
    int MAX_QUEUES;

    printf("Welcome! This program represents - Priority queue and allows you to do various calculations and actions with it.\n");
    printf("Before you start using the program, please provide the program with the following input:\n");
    printf("Please enter the Maximum number of priority queues in the program:\n");
    scanf("%d", &MAX_QUEUES);
    printf("Please enter the Maximum number of elements in priority queue:\n");
    scanf("%d", &MAX_ELEMENTS);


    while(runPriorityQueue){

        printf("\nMax element number: %d", MAX_ELEMENTS);
        printf("\nMax queue number: %d", MAX_QUEUES);

        printf("\n****************************\n");
        printf(" 0 - Close the program\n 1 - Enqueue the selected queue\n 2 - Dequeue the selected queue\n 3 - Print the first element of the selected queue\n 4 - Clear a queue \n 5 - Print a queue\n 6 - Delete a queue\n 7 - Create a queue\n");
        printf("\n****************************\n");

        scanf("%d", &runPriorityQueue);

        int index;

        if(runPriorityQueue >= 1 && runPriorityQueue <= 6){

            printf("Please enter the index of the priority queue: \n");
            scanf("%d", &index);

           if(queueExists[index - 1] == 0){
                printf("Queue does not exist\n");
                continue;
            }
        }

        if(runPriorityQueue == 1){
            printf("Enter Priority Value\n");
            scanf("%d %d", &priority, &value);

            enqueue(priority, value, index, MAX_ELEMENTS);

        }else if(runPriorityQueue == 2){
            int dequeued = dequeue(index);

            if(dequeued == -1 && isEmpty(index)){
                printf("The priority queue is empty\n");
            }else {
                printf("Dequeued first element, value: %d\n", dequeued);
            }
        }else if(runPriorityQueue == 3){
            printf("First element's, value is): %d\n", getFirst(index));
        }else if(runPriorityQueue == 4){
            queueClear(index);
            printf("The Queue is cleared");
        }else if(runPriorityQueue == 5){
            printQueue(index);
        }else if(runPriorityQueue == 6){
            deleteQueue(index);
        }else if(runPriorityQueue == 7){
            addQueue(MAX_QUEUES);
        }else{
            return 0;
        }

    }
}

void deleteQueue(int index){
    if(queue[index - 1] == NULL) {
        queueExists[index - 1] = 0;
        return;
    }

    while(queue[index - 1] != NULL) {
        List *elementToDelete = queue[index - 1];
        queue[index - 1] = queue[index - 1]->next;
        free(elementToDelete);
        queueExists[index - 1] = 0;
    }

    printf("The Priority queue is deleted!\n");
}

void addQueue(int MAX_QUEUES){

    if(queues == MAX_QUEUES){
        printf("Queue list is full\n");
        return;
    }

    queue = (List**) realloc(queue, sizeof(List *) * (newIndex + 1));
    queue[newIndex] = (List *) malloc(sizeof(List));
    queue[newIndex] = NULL;

    queues++;
    queueExists[newIndex] = 1;
    newIndex++;

    printf("The Priority queue is added!\n");
}

void enqueue(int priority, int value, int index, int MAX_ELEMENTS){

    if(queueExists[index - 1] == 0){
        printf("Such Queue does not exist\n");
        return;
    }

    List *nodeToAdd, *temporaryPointer;
    nodeToAdd = (List *)malloc(sizeof(List));

    if(nodeToAdd == NULL){
        printf("Unfortunately, Memory allocation failed!\n");
        return;
    }else if( queue[index - 1] != NULL){
        if(elementCount[index - 1] == MAX_ELEMENTS) {
            printf("Priority queue is full!\n");
            return;
        }
    }
    nodeToAdd->value = value;
    nodeToAdd->priority = priority;

    int Empty = isEmpty(index);

    if( isEmpty(index) || queue[index - 1]->priority < priority){

        nodeToAdd->next = queue[index - 1];
        queue[index - 1] = nodeToAdd;

        if(Empty) {
            elementCount[index - 1] = 0;
        }

        elementCount[index - 1]++;

    }else{

        temporaryPointer = queue[index - 1];

        while(1) {

            if (temporaryPointer->next == NULL || temporaryPointer->next->priority < priority){
                nodeToAdd->next = temporaryPointer->next;
                temporaryPointer->next = nodeToAdd;
                break;
            }

            temporaryPointer = temporaryPointer->next;
        }

        (queue[index - 1]->elementCount)++;
    }

    printf("Element added to priority queue, value: %d, priority %d", value, priority);

}

int dequeue(int index){

    if(queue[index - 1] == NULL){
        return -1;
    }


    int valueToReturn = queue[index - 1]->value;

    List *temporaryPointer = queue[index - 1];
    queue[index - 1] = queue[index - 1]->next;
    free(temporaryPointer);

    elementCount[index - 1]--;

    return valueToReturn;
}



int isEmpty(int index){
    if(queue[index - 1] == NULL) {
        return 1;
    }else{
        return 0;
    }
}

int getFirst(int index){

    if(queue[index - 1] == NULL){
        printf("ERROR: can't get an element from an empty priority queue\n");
        exit(1);
    }

    return queue[index - 1]->value;

}

void printQueue(int index){

    if(isEmpty(index)){
        return;
    }
    while(queue[index - 1] != NULL) {
        printf("Element's Priority is - %15d    ***  Element's Value is - %15d\n", queue[index - 1]->priority, queue[index - 1]->value);
        queue[index - 1] = queue[index - 1]->next;
    }
}

void queueClear(int index){

    if(queue[index - 1] == NULL) {
        return;
    }

    while(queue[index - 1] != NULL) {
        List *elementToDelete = queue[index - 1];
        queue[index - 1] = queue[index - 1]->next;
        free(elementToDelete);
    }
    elementCount[index - 1] = 0;

}
