#include <stdio.h>
#include "map_.h"

int _Looking_TB_SubJ[100];
Graph G;
int _Looking_TB_SubJ_priority[100];
extern size_t parse_table_data_to_local(char *name_file_path,int *dest_array,int *dest_priority);
extern void parse_map_data(const char* name_file_path, Graph *G);

// function to initialize data
// return size of array and return -1 if error
int InitData(){ 
    int size = parse_table_data_to_local("Topo/data.tbl",_Looking_TB_SubJ,_Looking_TB_SubJ_priority);
    if(size == -1){
        printf("Can't find file data.tbl\n");
        return -1;
    }
    return size;
}

// function to initialize graph
void InitGraph(){
    parse_map_data("Topo/Edge.list",&G);
}