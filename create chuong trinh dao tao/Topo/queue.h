#ifndef _queue_h
#define _queue_h

typedef struct _node_q{
    // data
    int key;
    // link
    struct _node_q* next;
}node_q;

typedef struct _queue_q{
    node_q *front,*rear;
}Queue_i;

extern Queue_i* createQueueI();
extern void InitQueueI(Queue_i* src);
extern int isEmtryQ(Queue_i* src);
extern void enqueueQ(Queue_i* src,node_q* data);
extern node_q* dequeueQ(Queue_i* src);
extern void freeQueueI(Queue_i* src);
extern node_q* createNodeQ(int key);

#endif