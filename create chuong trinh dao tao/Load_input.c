#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

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

int check_num_of_correct_str(const char* str, const char* query){
    int count = 0;
    if(str == NULL || query == NULL){
        fprintf(stderr, "Error: NULL string passed to check_num_of_correct_str\n");
        return 0;
    }
    int len = strlen(query);
    int min_len = strlen(str) < len ? strlen(str) : len;
    for (int i = 0; i < min_len; i++)
    {
        if(str[i] == query[i]){
            count++;
        }
    }
    return count;
}

int handle_search_subject(Player* p,int index_subject ,const char* query){
    size_t init_size = 50;
    Subject_Node* store[init_size];
    memset(store,0,sizeof(store));
    Subject_Node* curr = NULL;
    curr = p->numofSubjectType[index_subject].head;
    do{
        bool found = false;
        int len_check = 0;
        int count_subject_likely = 0;
        int real_len = 0;
        while(curr){
            len_check = check_num_of_correct_str(curr->ID,query);
            real_len = strlen(curr->ID);
            if(len_check == real_len){
                // found
                found = true;
                goto finish;
            }else if (len_check >= 2){
                // found but not exact
                if(count_subject_likely >= init_size){
                    continue;
                }
                store[count_subject_likely] = curr;
                count_subject_likely++;
            }
            curr = curr->next;
        }
        if(!found){
            fprintf(stdout ,"Cant find ID --- Please Enter Correct ID\n");
            fprintf(stdout ,"You mean this subject: \n");
            for(int i = 0; i < count_subject_likely; i++){
                if(store[i] != NULL){
                    printf("%s %s\n",store[i]->ID, store[i]->name);
                }
            }
            fprintf(stdout ,"Please Enter again\n");
            return 0;
        }
    }while(1);
    finish:
    return 1;
}

void PayLoad_input(Player* p){
    int indextype;
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
        init_again:
        indextype = 0;
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
        get_id:
        char id[MAXSIZEID];
        printf("Please Enter id to setup or Enter back to choose new Index: ");fgets(id,sizeof(id),stdin);
        if(memcmp(id,"back",4) == 0 || memcmp(id,"Back",4) == 0 || memcmp(id,"BACK",4) == 0){
            fflush(stdin);
            goto init_again;
        }
        if(!handle_search_subject(p,indextype,id)){
            goto get_id;
        }
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