// Lukas Brasiunas, 2110539

#ifndef QUEUE_FUNCTION_DESC_H_INCLUDED
#define QUEUE_FUNCTION_DESC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// A linked list node to store a queue entry
struct QNode
{
    int data;
    struct QNode* next;
};

// The queue structure
struct Queue
{
    struct QNode *front, *rear;
};

// A function to create a new linked list node
struct QNode* newNode(int key);
// A function to create an empty queue
struct Queue* createQueue();
// A function to check if the queue is full
int isFull();
// A function to check if the queue is empty
int isEmpty(struct Queue* queue);
// A function to add a new element in to the queue and returns error = NULL if it is full
void enQueue(struct Queue* queue, int key, int *error);
// A function to remove the first element from the queue
void deQueue(struct Queue* queue);
// A function to return the first element in queue
int peek(struct Queue* queue);
// A function to delete an entire list
void destroyList(struct Queue* queue);
// A function to print out the entire queue
void printList(struct Queue* queue);

#endif // QUEUE_FUNCTION_DESC_H_INCLUDED
