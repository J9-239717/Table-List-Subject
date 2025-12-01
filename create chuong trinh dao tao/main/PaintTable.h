#ifndef Paint_Table_H
#define Paint_Table_H

#include <stdio.h>
#include "Struct_Table.h"

void paint_table(FILE *fp, const char* headers[], int num_columns, const char* rows[][MAX_COLUMNS], int num_rows);
void paint_TKB_file(Player* player,FILE* fp);


#endif