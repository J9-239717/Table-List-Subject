#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "map_.h"

// create graph with V vertices and E edges
// directed = 1 if graph is directed
// directed = 0 if graph is undirected
void createGraph(Graph *G, int V, int E, int directed){
    G->V = V;
    G->E = E;
    G->directed = (directed > 0) ? 1 : 0;
    G->adj = (int **)malloc((V) * sizeof(int *));
    assert(G->adj != NULL);
    for(int i = 0; i < V; i++){
        G->adj[i] = (int*)calloc(V,sizeof(int));
        assert(G->adj[i] != NULL);
    }
}

// set edge u-v with weight w
void setEdge(Graph *G, int u, int v, int w){
    if(G->directed){
        G->adj[u][v] = w;
    }else{
        G->adj[u][v] = w;
        G->adj[v][u] = w;
    }
}

// print graph type matrix
void printGraph(Graph *G){
    for(int i = 0; i < G->V; i++){
        for(int j = 0; j < G->V; j++){
            printf("%d ",G->adj[i][j]);
        }
        printf("\n");
    }
}

// print graph type vector
void printGraphVector(Graph *G){
    for(int i = 0; i < G->V; i++){
        printf("Vertex %d: ", _Looking_TB_SubJ[i]);
        for(int j = 0; j < G->V; j++){
            if(G->adj[i][j] != 0){
                printf("%d ", _Looking_TB_SubJ[j]);
            }
        }
        printf("\n");
    }
}

// free graph
void freeGraph(Graph *G){
    for(int i = 0; i < G->V; i++){
        free(G->adj[i]);
    }
    free(G->adj);
}

// parse map data
// "*" for new vertex
void parse_map_data(const char* name_file_path, Graph *G){
    FILE *file;
    int temp;
    char buffer[5],bufferhead[25];
    int V,E,directed;

    file = fopen(name_file_path,"r");
    assert(file != NULL);
    
    fgets(bufferhead,25,file);
    bufferhead[strcspn(bufferhead,"\n\r")] = '\0';
    temp = sscanf(bufferhead,"%d %d %d",&V,&E,&directed);
    assert(temp == 3);

    createGraph(G,V,E,directed);

    int u = 0,v;
    while(fgets(buffer,5,file) != NULL){
        buffer[strcspn(buffer,"\n\r")] = '\0';
        assert(u < G->V);
        if(buffer[0] == '*'){
            u++;
            continue;
        }else{
            temp = sscanf(buffer,"%d",&v);
            assert(temp == 1);

            v = v - 1; // base 0
            setEdge(G,u,v,1);
        }
    }
    fclose(file);
}