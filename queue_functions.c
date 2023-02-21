// Lukas Brasiunas, 2110539

#include "queue_function_desc.h"

// A function to create a new linked list node
struct QNode* newNode(int key)
{
    // Allocate memory for the new node
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->data = key;
    temp->next = NULL;
    return temp;
}

// A function to create an empty queue
struct Queue* createQueue()
{
    // Allocate memory for the new empty queue
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// A function to check if the queue is full
int isFull()
{
    int temp = malloc(sizeof(struct QNode));
    return temp;
}

// A function to check if the queue is empty
int isEmpty(struct Queue* queue)
{
    if(queue->rear == NULL && queue->front == NULL)
        return 0;
    else
        return 1;
}

// A function to add a new element in to the queue and returns error = NULL if it is full
void enQueue(struct Queue* queue, int key, int *error)
{
    struct QNode* temp = newNode(key);
    if(!isFull)
    {
        *error = 0;
        return;
    }

    // If queue is empty, then the front of the new node and the rear of it is the same
    if(queue->rear == NULL)
    {
        queue->front = queue->rear = temp;
        return;
    }

    // Add the new node at the end of the queue and change rear
    queue->rear->next = temp;
    queue->rear = temp;
}

// A function to remove the first element from the queue
void deQueue(struct Queue* queue)
{
    // Check if the queue is empty
    if(queue->front == NULL)
        return;

    // Store previous front and move front one node ahead
    struct QNode* temp = queue->front;
    queue->front = queue->front->next;

    // If front becomes NULL, then change rear also to NULL
    if(queue->front == NULL)
        queue->rear = NULL;

    // Free up the memory allocated for the stored front
    free(temp);
}

// A function to return the first element in queue
int peek(struct Queue* queue)
{
    // Check if the queue is not empty
    if(queue->front != NULL)
        return queue->front->data;
    else
        exit(0);
}

// A function to delete an entire list
void destroyList(struct Queue* queue)
{
    // Deleting all of the nodes until the front becomes NULL
    while(queue->front != NULL)
        deQueue(queue);
}

// A function to print out the entire queue
void printList(struct Queue* queue)
{
    // Checking if the queue is empty
    if(queue->front == NULL)
    {
        printf("Queue is empty. Nothing to display.\n");
        return;
    }

    struct QNode* temp = queue->front;

    // Printing out all of the elements in the queue
    while(temp)
    {
        printf("%d->",temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
