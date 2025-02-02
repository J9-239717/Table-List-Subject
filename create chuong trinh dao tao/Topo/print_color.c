#include <stdio.h>
#include "print_color.h"

void yellow(FILE* f){
    fprintf(f,"\033[1;33m");
}

void red(FILE* f){
    fprintf(f,"\033[1;31m");
}

void green(FILE *f){
    fprintf(f,"\033[1;32m");
}

void blue(FILE *f){
    fprintf(f,"\033[1;34m");
}

void reset(FILE *f){
    fprintf(f,"\033[0m");
}