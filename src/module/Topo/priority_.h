#ifndef _priority_q_h
#define _priority_q_h

typedef struct _node{
    // data
    int key;
    int priority;
    // link
    struct _node* next;
}node;

typedef struct _queue_i{
    node *front,*rear;
}PriorityQueue_i;

extern PriorityQueue_i* createPriorityQueueI();
extern void InitQueue(PriorityQueue_i* src);
extern int isEmtry(PriorityQueue_i* src);
extern void enqueue(PriorityQueue_i* src,node* data);
extern node* dequeue(PriorityQueue_i* src);
extern void freePriorityQueue(PriorityQueue_i* src);
extern node* createNode(int key,int priority);


#endif