#ifndef _map_h
#define _map_h

// graph
typedef struct _Graph{
    int V;
    int E;
    int **adj;
    int directed : 1;
}Graph;

extern void printGraph(Graph *G);
extern void freeGraph(Graph *G);
extern void printGraphVector(Graph *G);

extern int _Looking_TB_SubJ[100];

#endif