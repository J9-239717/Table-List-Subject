#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "Struct_Table.h"
#include "Node_LOGIC.h"
#include "Score_LOGIC.h"
#include "Load_input.h"

void set_limit(float* mid,float* final){
    int seletion = 0;
    do
    {
        printf("Please seletion limit your score\n"
               "1.50-50\n"
               "2.40-60\n"
               "3.30-70\n");
               printf("Enter: ");scanf("%d", &seletion);
        if(seletion == 1){
            *mid = 0.5;
            *final = 0.5;
            break;
        }else if(seletion == 2){
            *mid = 0.4;
            *final = 0.6;
            break;
        }else if(seletion == 3){
            *mid = 0.3;
            *final = 0.7;
            break;
        }else{
            printf("Invalid command please enter again\n");
        }
    } while (1);
    
}

void PayLoad_input(Player* p){
    int indextype = 0;
    const char* name_SJ_t[] = {
        "co_so_nganh",
        "dai_cuong",
        "the_thao",
        "ly_luat_chinh_tri",
        "tu_chon",
        "thuc_tap",
        "modunI",
        "modunII",
        "modunIII",
        "modunIV",
        "modunV",
        "do_an_tot_nghiep"
    };

    printf("Please Enter index to seletion you type of Subject\n");
    do{
        for(int i = 0; i < sizeSubjectType ;i++){
            printf("%d.%s\n",i+1,name_SJ_t[i]);
        }fprintf(stdout,"Please Enter(1-12) or enter 0 to end: ");scanf("%d", &indextype);
        char c;
        while ((c = getchar()) != '\n' && c != EOF);
        indextype -= 1;
        if(indextype < -1 || indextype > 11){
            printf("Please enter again\n");
        }
        if(indextype == -1)break;

        char id[MAXSIZEID];
        printf("Please Enter id to setup: ");fgets(id,sizeof(id),stdin);
        id[strcspn(id,"\r\n")] = '\0';
        float limit_mid = 0.0;
        float limit_final = 0.0;
        float score_m = 0.0;
        float score_f = 0.0;
        printf("Please Enter Your score midterm and finalterm\n");
        printf("Midterm: ");scanf("%f", &score_m);
        printf("Finalterm: ");scanf("%f", &score_f);
        if(score_m > 10 || score_f > 10){
            fprintf(stderr, "Invalid score please enter again\n");
            continue;
        }
        set_limit(&limit_mid,&limit_final);
        char clean;
        while ((clean = getchar()) != '\n' && clean != EOF);
        if(!set_score_mid_and_final(p,score_m,score_f,limit_mid,limit_final,indextype,id)){
            continue;
        }else {
            printf("Complete Set up\n");
            printSubjectType(&p->numofSubjectType[indextype]);
            printf("Please Enter to connect...");
            char wait;
            while((wait = getchar()) && wait != '\n');
        }
    }while(1);

    return; 
}