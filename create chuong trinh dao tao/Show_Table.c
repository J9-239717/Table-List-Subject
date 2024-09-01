#include<stdio.h>
#include "Show_Table.h"
void show_table(FILE* f) {
    char c;
    while ((c = fgetc(f)) != EOF) {
        printf("%c", c);
    }
}
