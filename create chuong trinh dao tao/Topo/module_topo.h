#ifndef _module_1_h
#define _module_1_h

#include<stdio.h>
#include "map_.h"
#include "priority_.h"
#include "queue.h"
#include "const_value.h"
#include "print_color.h"

extern size_t parse_table_data_to_local(char *name_file_path,int *dest_array,int *dest_priority);
extern int InitData();
extern int _Looking_TB_SubJ[100];
extern int _Looking_TB_SubJ_priority[100];
extern void InitGraph();
extern Graph G;
extern void RunTopo(int *dataSubjectPass,int size_data);

#define SizeOfArray(x) sizeof(x)/sizeof(x[0])
#define SizeOfSubject 28

#endif