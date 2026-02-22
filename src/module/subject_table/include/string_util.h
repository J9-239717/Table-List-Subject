#ifndef F_Helper_STR_H
#define F_Helper_STR_H

#include <string.h>

char* change_underscore(char* src);
void change_underscore_v(const char* src,char* return_s);
void change_space_v(const char* src,char* return_s);
char* change_space(char* src);

// change underscore to space
char* change_underscore(char* src){
    int l = strlen(src);
    for(int i = 0; i < l;i++){
        if(src[i] == '_'){
            src[i] = ' ';
        }
    }
    return src;
}

// change underscore to space
void change_underscore_v(const char* src,char* return_s){
    int l = strlen(src);
    for(int i = 0; i < l; i++){
        if(src[i] == '_'){
            return_s[i] = ' ';
        }else{
            return_s[i] = src[i];
        }
    }
    return_s[l] = '\0';
}

// change space to underscore
void change_space_v(const char* src,char* return_s){
    int l = strlen(src);
    for(int i = 0; i < l; i++){
        if(src[i] == ' '){
            return_s[i] = '_';
        }else{
            return_s[i] = src[i];
        }
    }
    return_s[l] = '\0';
}

// change space to underscore
char* change_space(char* src){
    int l = strlen(src);
    for(int i = 0; i < l;i++){
        if(src[i] == ' '){
            src[i] = '_';
        }
    }
    return src;
}

#endif
