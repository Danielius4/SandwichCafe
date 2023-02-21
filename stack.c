#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"

int createStack(Stack *a)       // returns 1 if everything is ok
{                               // returns 0 if memory can't be allocated
    if(a->head != NULL)         // returns -9999 if stack head is not NULL
    {
        return -9999;
    }

    if((a->head = (struct List*)malloc(sizeof(struct List))) == NULL)
        return 0;

    (a->head)->link = NULL;

    return 1;
}

int countStackElements(Stack a)     // returns number of elements in the stack
{                                   // returns -9999 if stack does not exist
    int counter = 0;

    if(a.head == NULL)
        return -9999;

    else
    {
        struct List *current = NULL;

        counter = 0;
        current = a.head;

        while(current->link != NULL)
        {
            counter++;
            current = current->link;
        }
    }
    return counter;
}

int deleteStack(Stack *a)           // delete stack from memory, free memory
{                                   // returns -9999 if list does not exist
    if(a->head == NULL)             // returns 1 if success
    {
        return -9999;
    }
    List *current = a->head;
    while(current != NULL)
    {
        current = a->head->link;
        free(a->head);
        a->head = current;
    }

    return 1;
}

int push(Stack *a, int data)        // push new element
{                                   // returns -9999 if stack is full or does not exist
    if(a->head == NULL)             // returns 1 if success
        return -9999;

    if(isStackFull(*a) == 1)
        return -9999;

    List *current = (struct List*)malloc(sizeof(struct List));

    current->link = a->head;
    current->data = data;
    a->head = current;
    return 1;
}

int deleteNodeByLocation(Stack *a ,int location)    // delete data at specified location
{                                                   // returns -9999 if error
    if(location < 1)                                // returns 1 if success
    {
        return -9999;
    }
    if(a == NULL)
    {
        return -9999;
    }
    List *prev = NULL;
    List *current = NULL;

    current = a->head;
    prev = a->head;
    for(int i = 1; i < location; ++i)
    {
        if(current->link == NULL)
        {
            return -9999;
        }
        prev = current;
        current = current->link;
    }
    if(current == a->head)
    {
        a->head = a->head->link;
        free(current);
        return 1;
    }
    if(current->link == NULL)
    {
        prev->link = NULL;
        free(current);
    }
    else
    {
        prev->link = current->link;
        free(current);
    }
    return 1;
}

int findData(Stack a, int location)         // find data at specified location
{                                           // returns -9999 if stack is empty or does not exist
    int nodes = countStackElements(a);      // returns -8888 if location is not found
    if(nodes > 0)
    {
        if(a.head == NULL)
        {
            return -9999;
        }
        List *current = a.head;
        for(int i = 1; i != location; ++i)
        {
            if(current->link->link == NULL)
            {
                return -8888;
            }
            current = current->link;
        }
        return current->data;
    }
    return -9999;
}

int pop(Stack *a)               //returns -9999 if stack is empty
{                               //returns first element of stack
    if(countStackElements(*a) > 0)
    {
        int data = findData(*a, 1);

        deleteNodeByLocation(a, 1);
        return data;
    }
    else
        return -9999;
}

int isStackFull(Stack a)            //returns 1 if stack is full
{                                   //returns 0 if stack is not full
    if(a.head == NULL)              //returns -9999 if stack is not created
    {
        return -9999;
    }
    if((a.head = (struct List*)malloc(sizeof(struct List))) == NULL)
    {
        return 1;
    }
    else
    {
        free(a.head);
        return 0;
    }
}

int isStackEmpty(Stack a)               //returns 1 if stack is empty
{                                       //returns 0 if stack is not empty
    if(a.head == NULL)                  //returns -9999 if stack is not created
        return -9999;

    if(countStackElements(a) == 0)
        return 1;
    else
        return 0;
}

int init(Stack *a)
{
    a->head = NULL;

    return 1;
}
