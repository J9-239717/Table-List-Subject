#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

Queue_i* createQueueI(){
    Queue_i* Q = (Queue_i*)malloc(sizeof(Queue_i));
    if(Q == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    Q->front = Q->rear = NULL;
    return Q;
}

node_q* createNodeQ(int key){
    node_q* temp = (node_q*)malloc(sizeof(node_q));
    if(temp == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    temp->key = key;
    temp->next = NULL;
    return temp;
}

void InitQueueI(Queue_i* src){
    src->front = src->rear = NULL;
}

int isEmtryQ(Queue_i* src){
    return src->front == NULL;
}

void enqueueQ(Queue_i* src,node_q* data){
    if(src->front == NULL){
        src->front = src->rear = data;
    }else{
        src->rear->next = data;
        src->rear = data;
    }
}

node_q* dequeueQ(Queue_i* src){
    if(src->front == NULL){
        return NULL;
    }
    node_q* temp = src->front;
    src->front = src->front->next;
    if(src->front == NULL){
        src->rear = NULL;
    }
    return temp;
}

void freeQueueI(Queue_i* src){
    node_q* temp;
    while(src->front != NULL){
        temp = src->front;
        src->front = src->front->next;
        free(temp);
    }
    free(src);
}
