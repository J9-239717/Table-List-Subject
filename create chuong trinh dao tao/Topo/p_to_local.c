#include<stdio.h>
#include<assert.h>
// function parse table data 
// return size of array and return -1 if error
size_t parse_table_data_to_local(char *name_file_path,int *dest_array,int *dest_priority){
    FILE *file;
    file = fopen(name_file_path,"r");
    assert(file != NULL);
    if(file == NULL){
        return -1;
    }
    size_t size = 0;
    char buffer[100];
    while(fgets(buffer,100,file) != NULL){
        sscanf(buffer,"%d-%d",&dest_priority[size],&dest_array[size]);
        size++;
    }
    fclose(file);
    return size;
}