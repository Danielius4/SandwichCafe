#ifndef STACK_H_
#define STACK_H_

typedef struct List
{
    int data;
    struct List *link;
}List;

typedef struct Stack
{
    List *head;
}Stack;

int init(Stack *a); // initializes Stack structure elements

int createStack(Stack *a);
int deleteStack(Stack *a);
int push(Stack *a, int data);
int pop(Stack *a);
int isStackFull(Stack a);
int isStackEmpty(Stack a);

int countStackElements(Stack a);
int findData(Stack a, int location);    // finds data at location from the top
int deleteNodeByLocation(Stack *a,int location); // deletes stack element at location from the top


#endif
