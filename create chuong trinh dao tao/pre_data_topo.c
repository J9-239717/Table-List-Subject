#include "Struct_Table.h"
#include <stdio.h>
#include <assert.h>

int FindSubject(int* dest,int size,int index){
    for(int i = 0; i < size; i++){
        if(dest[i] == index){
            return i;
        }
    }
    return -1;
}

void PreData(Player* src,int* ret,int* dest,int size){
    for(int i = 0; i < size; i++){
        ret[i] = 0;
    }
    printf("Init return array completed...\n");

    // Find in dai_cuong types
    Subject_Node* curr = src->numofSubjectType[dai_cuong].head;
    assert(curr != NULL);
    while(curr != NULL){
        int temp;
        sscanf(curr->ID, "IT%d", &temp);
        int get_ = FindSubject(dest,size,temp);
        if(get_ != -1 && curr->status_pass)ret[get_] = 1;
        curr = curr->next;
    }

    // Find in co_so_nganh types
    curr = src->numofSubjectType[co_so_nganh].head;
    assert(curr != NULL);
    while(curr != NULL){
        int temp;
        sscanf(curr->ID, "IT%d", &temp);
        int get_ = FindSubject(dest,size,temp);
        if(get_ != -1 && curr->status_pass)ret[get_] = 1;
        curr = curr->next;
    }

    // Find in ModunI types
    curr = src->numofSubjectType[modunI].head;
    assert(curr != NULL);
    while(curr != NULL){
        int temp;
        sscanf(curr->ID, "IT%d", &temp);
        int get_ = FindSubject(dest,size,temp);
        if(get_ != -1 && curr->status_pass)ret[get_] = 1;
        curr = curr->next;
    }

    // Find in ModunIV types
    curr = src->numofSubjectType[modunIV].head;
    assert(curr != NULL);
    while(curr != NULL){
        int temp;
        sscanf(curr->ID, "IT%d", &temp);
        int get_ = FindSubject(dest,size,temp);
        if(get_ != -1 && curr->status_pass)ret[get_] = 1;
        curr = curr->next;
    }

    // Find in thuc_tap types
    curr = src->numofSubjectType[thuc_tap].head;
    assert(curr != NULL);
    while(curr != NULL){
        int temp;
        sscanf(curr->ID, "IT%d", &temp);
        int get_ = FindSubject(dest,size,temp);
        if(get_ != -1 && curr->status_pass)ret[get_] = 1;
        curr = curr->next;
    }

    // Find in do_an_tot_nghiep types
    curr = src->numofSubjectType[do_an_tot_nghiep].head;
    assert(curr != NULL);
    while(curr != NULL){
        int temp;
        sscanf(curr->ID, "IT%d", &temp);
        int get_ = FindSubject(dest,size,temp);
        if(get_ != -1 && curr->status_pass)ret[get_] = 1;
        curr = curr->next;
    }

    return;
}