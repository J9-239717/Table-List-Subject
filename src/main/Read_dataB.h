#ifndef Read_DB_H
#define Read_DB_H

#include <stdio.h>
#include "Struct_Table.h"

int read_dataB_type(Subject_Type* node, FILE* fp);
int read_dataB_player(Player* p,FILE* fp);

#endif