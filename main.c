#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "stack.h"
#include "stack.c"
#include "queue_function_desc.h"
#include "queue_functions.c"

int countQueueElements(struct Queue *a);
int readParameters (int *clientProb, int *newSandwQuantity, int *newSandwTime, int *badSandwTime, int *sandwPrice, int *dayLength);

int main() {
    int clientProb, newSandwQuantity, newSandwTime, badSandwTime;
    int badOldSandwCounter = 0, badNewSandwCounter1 = 0, badNewSandwCounter2 = 0, dayLength;
    int sandwPrice, maxSandwInPlace = 50;

    Stack oldSandwPlace1;
    Stack oldSandwPlace2;
    init(&oldSandwPlace1);
    init(&oldSandwPlace2);
    createStack(&oldSandwPlace1);
    createStack(&oldSandwPlace2);

    //creating newSandwPlaces
    int newSandwError = 1;
    struct Queue* newSandwPlace1 = createQueue();
    struct Queue* newSandwPlace2 = createQueue();
    struct Queue* newSandwPlace3 = createQueue();

    //reading from data.txt file
    if(readParameters(&clientProb, &newSandwQuantity, &newSandwTime, &badSandwTime, &sandwPrice, &dayLength) != 0){
        printf("\nBad data input!\n");
        return -99;
    }

    for(int i = 0; i < 5; ++i){

        push(&oldSandwPlace1, 1000);
        push(&oldSandwPlace2, 1000);
        enQueue(newSandwPlace1, 1000, &newSandwError);
        enQueue(newSandwPlace2, 1000, &newSandwError);
    }
    for(int i = 0; i < 10; ++i) {

        enQueue(newSandwPlace3, 1000, &newSandwError);
    }

    srand(time(0));
    int temp;
    int counter = 0, randomNumber;

    while (dayLength > 0 && newSandwTime != 0) {
                // placing fresh sandwiches
        if (counter % newSandwTime == 0) {

            if ((countStackElements(oldSandwPlace1)) < (countStackElements(oldSandwPlace2))) {
                for (int i = 0; i < newSandwQuantity; ++i) {
                    if(countStackElements(oldSandwPlace1) < maxSandwInPlace){
                        push(&oldSandwPlace1, dayLength);
                        enQueue(newSandwPlace1, dayLength, &newSandwError);
                    }
                    if(countQueueElements(newSandwPlace3) < maxSandwInPlace)
                        enQueue(newSandwPlace3, dayLength, &newSandwError);
                }
            }
            else {
                for (int i = 0; i < newSandwQuantity; ++i) {
                    if(countStackElements(oldSandwPlace2) < maxSandwInPlace){
                        push(&oldSandwPlace2, dayLength);
                        enQueue(newSandwPlace2, dayLength, &newSandwError);
                    }

                    if(countQueueElements(newSandwPlace3) < maxSandwInPlace)
                        enQueue(newSandwPlace3, dayLength, &newSandwError);
                }
            }
        }

                //selling a sandwich

        randomNumber = rand();
        temp = randomNumber % 101;
        if (temp < clientProb) {

            if (randomNumber % 2 == 1){
                pop(&oldSandwPlace1);
                deQueue(newSandwPlace1);
            }
            else {
                pop(&oldSandwPlace2);
                deQueue(newSandwPlace2);
            }

            deQueue(newSandwPlace3);

        }
        --dayLength;
        ++counter;
    }

    int oldCounter1 = countStackElements(oldSandwPlace1);
    int oldCounter2 = countStackElements(oldSandwPlace2);
    int newCounter1 = countQueueElements(newSandwPlace1);
    int newCounter2 = countQueueElements(newSandwPlace2);
    int newCounter3 = countQueueElements(newSandwPlace3);

    //counting old sandwiches in oldSandwPlaces
    for (int i = 1; i <= oldCounter1; ++i) {
     //   printf("%d sandwich | %d old\n", i, findData(oldSandwPlace1, i));
        if(findData(oldSandwPlace1, i) >= badSandwTime)
            ++badOldSandwCounter;
    }
    for (int i = 1; i <= oldCounter2; ++i) {
        if(findData(oldSandwPlace2, i) >= badSandwTime)
            ++badOldSandwCounter;
    }

        //counting bad sandwiches in newSandwPlaces
    for(int i = 1; i <= newCounter1; ++i){
        temp = peek(newSandwPlace1);
        deQueue(newSandwPlace1);
        if(temp >= badSandwTime)
            ++badNewSandwCounter1;
    }
    for(int i = 1; i <= newCounter2; ++i){
        temp = peek(newSandwPlace2);
        deQueue(newSandwPlace2);
        if(temp >= badSandwTime)
            ++badNewSandwCounter1;
    }

        //counting bad sandwiches in newSandwPlace3
    for(int i = 1; i <= newCounter3; ++i){
        temp = peek(newSandwPlace3);
        deQueue(newSandwPlace3);
        if(temp >= badSandwTime)
            ++badNewSandwCounter2;
    }

        //printing results

    FILE *fPtr = NULL;
    fPtr = fopen("C:\\Univeras\\2semestras\\ADS\\3laboras\\1bandymas\\rez.txt", "w");
    fprintf(fPtr, "OLD sandwich places:");
    fprintf(fPtr, "\noldSandwPlace1: %d\n", oldCounter1);
    fprintf(fPtr, "oldSandwPlace2 %d\n", oldCounter2);
    fprintf(fPtr, "Bad sandwiches: %d", badOldSandwCounter);

    fprintf(fPtr, "\n\nNEW sandwich places:");
    fprintf(fPtr, "\nnewSandwPlace1 is made of %d elements", newCounter1);
    fprintf(fPtr, "\nnewSandwPlace2 is made of %d elements", newCounter2);
    fprintf(fPtr, "\nBad sandwiches: %d", badNewSandwCounter1);

    fprintf(fPtr, "\n\nOne NEW sandwich place:");
    fprintf(fPtr, "\nSandwich place is made of %d elements", newCounter3);
    fprintf(fPtr, "\nBad sandwiches: %d", badNewSandwCounter2);

    fclose(fPtr);

    deleteStack(&oldSandwPlace1);
    deleteStack(&oldSandwPlace2);
    destroyList(newSandwPlace1);
    destroyList(newSandwPlace2);
    destroyList(newSandwPlace3);

    return 0;
}

int countQueueElements(struct Queue *a)      // returns number of elements in the stack
{                                            // returns -9999 if stack does not exist
    int counter = 0;

    if(a == NULL)
        return -9999;

    else
    {
        struct QNode *current = NULL;

        current = a->front;

        while(current != NULL)
        {
            counter++;
            current = current->next;
        }
    }
    return counter;
}

int readParameters (int *clientProb, int *newSandwQuantity, int *newSandwTime, int *badSandwTime, int *sandwPrice, int *dayLength){

    int temp, valid;
    char bin = '0';

    FILE* fPtr = fopen ("C:\\Univeras\\2semestras\\ADS\\3laboras\\1bandymas\\data.txt", "r");

    if(fPtr == NULL)
        return 1;


    valid = fscanf(fPtr, "%d", &temp);
    if(valid == 1 && temp >= 0 && temp <= 100)
        *clientProb = temp;
    else
        return 1;

    while(!feof(fPtr) && bin != '\n'){

        fscanf(fPtr, "%c", &bin);
    }
    valid = fscanf(fPtr, "%d", &temp);
    if(valid == 1 && temp >= 0)
        *newSandwQuantity = temp;
    else
        return 1;

    while(!feof(fPtr)){
        fscanf(fPtr, "%c", &bin);
        if(bin == '\n')
            break;
    }
    valid = fscanf(fPtr, "%d", &temp);
    if(valid == 1 && temp >= 0)
        *newSandwTime = temp;
    else
        return 1;

    while(!feof(fPtr)){
        fscanf(fPtr, "%c", &bin);
        if(bin == '\n')
            break;
    }
    valid = fscanf(fPtr, "%d", &temp);
    if(valid == 1 && temp >= 0)
        *badSandwTime = temp;
    else
        return 1;

    while(!feof(fPtr)){
        fscanf(fPtr, "%c", &bin);
        if(bin == '\n')
            break;
    }
    valid = fscanf(fPtr, "%d", &temp);
    if(valid == 1 && temp >= 0)
        *sandwPrice = temp;

    while(!feof(fPtr)){
        fscanf(fPtr, "%c", &bin);
        if(bin == '\n')
            break;
    }
    valid = fscanf(fPtr, "%d", &temp);
    if(valid == 1 && temp >= 0)
        *dayLength = temp;
    else
        return 1;

    fclose(fPtr);
    return 0;
}