#include "module_topo.h"
#include <assert.h>
#include <stdlib.h>

int getTermRecomment(int id,int size){
    for(int i = 0; i < size; i++){
        if(_Looking_TB_SubJ[i] == _Looking_TB_SubJ[id]){
            return _Looking_TB_SubJ_priority[i];
        }
    }
    return -1;
}

void showFile(char* path){
    char c;
    FILE* f = fopen(path,"r");
    if(f == NULL){
        printf("Can't open file or please create \"file\" floder\n");
        assert(f != NULL);
    }

    while((c = fgetc(f)) != EOF){
        printf("%c",c);
    }
    fclose(f);
}

// please parse array of pass subject correct order like data.tbl
// please using check size of array and pass to size_data
// 1 for pass and 0 for not pass
void RunTopo(int *dataSubjectPass,int size_data){
    if(size_data < SizeOfSubject){
        printf("Please enter all subject your array size is %d ,we want %d\n",size_data,SizeOfSubject);
        return;
    }
    printf("Init data...\n");
    // Init Data and Graph
    int size = InitData();
    assert(size != -1);
    InitGraph();
    printf("Init data Completed...\n");
    // Init Indegree
    int Indegree[size+1];
    for(int i = 0; i < size; i++)Indegree[i] = 0;

    for(int i = 0; i < G.V; i++){
        for(int j = 0; j < G.V; j++){
           if(G.adj[i][j] != 0){
               Indegree[j]++;
            }
        }
    }

    // Init Queue
    PriorityQueue_i* r_no_priority = createPriorityQueueI();
    PriorityQueue_i* r = createPriorityQueueI();
    Queue_i* Q = createQueueI();
    // Topological Sort
    for(int i = 0; i < size; i++){
        if(Indegree[i] == 0){
            enqueueQ(Q,createNodeQ(i));
        }
    }

    while(!isEmtryQ(Q)){
        node_q* u = dequeueQ(Q);
        enqueue(r,createNode(u->key,_Looking_TB_SubJ_priority[u->key]));
        enqueue(r_no_priority,createNode(u->key,0));
        for(int i = 0; i < G.V; i++){
            if(G.adj[u->key][i] != 0){
                Indegree[i]--;
                if(Indegree[i] == 0){
                    enqueueQ(Q,createNodeQ(i));
                }
            }
        }
        free(u);
    }

    // Print Result
    FILE* f1 = fopen("file/Topo_table.txt","w");
    if(f1 == NULL){
        printf("Can't open file or please create \"file\" floder\n");
        assert(f1 != NULL);
    }
    int count = 0;
    blue(f1);
    fprintf(f1,"          <?*---TOPOSORT---*?> \n");
    fprintf(f1,"            // RECOMMENT //\n"
                " colum 1 -> term recomment of subject colum 2\n"
                " colum 4 -> term recomment of subject colum 3\n");
    fprintf(f1,"<////////////////////////////////////////////>\n");
    reset(f1);
    fprintf(f1,"        +---+---------+--------+----+            list name of subject");
    while(!isEmtry(r) && !isEmtry(r_no_priority)){
        node* u = dequeue(r);
        node* u_no_priority = dequeue(r_no_priority);

        if(dataSubjectPass[u->key] == 1 && dataSubjectPass[u_no_priority->key] == 1 ){
            goto FreePhrases;
        }

        if(dataSubjectPass[u_no_priority->key] != 1){
            fprintf(f1,"\n        | %-2d | IT%d |", getTermRecomment(u_no_priority->key,size), _Looking_TB_SubJ[u_no_priority->key]);
        }
        else{
            fprintf(f1,"\n        | 00 | IT0000 |");
        }

        if(dataSubjectPass[u->key] != 1){
            fprintf(f1," IT%d | %-2d |            %s",_Looking_TB_SubJ[u->key],u->priority,courses_IT[count]);
        }
        else{
            fprintf(f1," IT0000 | 00 |            %s",courses_IT[count]);
        }
        count++;
    FreePhrases:
        free(u);
        free(u_no_priority);
    }

    if(count == SizeOfSubject){
        fprintf(f1,"\n        +---+---------+--------+----+            ");
        goto EndPhrases;
    }

    if(count < SizeOfSubject){
        fprintf(f1,"\n        +---+---------+--------+----+            %s",courses_IT[count++]);
    }

    while(count < SizeOfSubject){
        fprintf(f1,"\n                                                 %s",courses_IT[count++]);
    }

    EndPhrases:
    fclose(f1);
    // Free Graph
    freePriorityQueue(r);
    freePriorityQueue(r_no_priority);
    freeQueueI(Q);
    freeGraph(&G);

    showFile("file/Topo_table.txt");
    return;
}