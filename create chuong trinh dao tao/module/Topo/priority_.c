#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "priority_.h"

PriorityQueue_i* createPriorityQueueI(){
    PriorityQueue_i *new = (PriorityQueue_i*)malloc(sizeof(PriorityQueue_i));
    assert(new != NULL);
    new->front = new->rear = NULL;
    return new;
}

node* createNode(int key,int priority){
    node* new = (node*)malloc(sizeof(node));
    assert(new != NULL);
    new->key = key;
    new->priority = priority;
    new->next = NULL;
    return new;
}

void InitQueue(PriorityQueue_i* src){
    src->front = src->rear = NULL;
}

int isEmtry(PriorityQueue_i* src){
    return src->front == NULL;
}

void enqueue(PriorityQueue_i* src,node* data){
    // frist element in queue
    if(isEmtry(src)){
        src->front = src->rear = data;
    }else{
        node *prev = NULL, *curr;
        curr = src->front;prev = NULL;
        while(curr != NULL && curr->priority <= data->priority){
            prev = curr;
            curr = curr->next;
        }

        // data is hightest priority
        if(prev == NULL){
            data->next = src->front;
            src->front = data;
        }else if(curr == NULL){
            // data have low prioriry
            src->rear->next = data;
            src->rear = src->rear->next;
        }else{
            // data have priority around in queue
            prev->next = data;
            data->next = curr;
        }
    }
}

node* dequeue(PriorityQueue_i* src){
    if(isEmtry(src)){
        printf("Queue is Emtry\n");
        return NULL;
    }

    node* temp = src->front;
    src->front = src->front->next;

    if(src->front == NULL)InitQueue(src);

    return temp;
}

void freePriorityQueue(PriorityQueue_i* src){
    if(!isEmtry(src)){
        node *curr = src->front,*temp;
        while(curr != NULL){
            temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(src);
}