#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Struct_Table.h"
#include "Score_LOGIC.h"
#include "Node_LOGIC.h"

int check_status_alert(int credit_np){
    if(credit_np < 8){
        return 0;
    }else if(credit_np < 16){
        return 1;
    }else if(credit_np < 27){
        return 2;
    }else{
        return 3;
    }
}

char check_score_letter(float score){
    if (score > 9.5) {
        return 'A';
    } else if (score >= 8.5) {
        return 'a';
    } else if (score >= 8) {
        return 'B';
    } else if (score >= 7) {
        return 'b';
    } else if(score >= 6.5){
        return 'C';
    }else if(score >= 5.5){
        return 'c';
    }else if(score >= 5){
        return 'D';
    }else if(score >= 4){
        return 'd';
    }else{
        return 'F';
    }
}

int limit_subject(float limit_mid,float limit_final,float score_mid,float score_final,char* score_l){
    float result = limit_mid * score_mid + limit_final * score_final;
    *score_l = check_score_letter(result);
    return (result >= 4) ? 1 : 0;
}

int set_score_mid_and_final(Player* p, float mid, float final, float limit_m, float limit_f,int i, char ID[MAXSIZEID]) {
    if(i < 0 || i > sizeSubjectType-1){
        printf("Invalid index of subject\n");
        return 0;
    }
    char s_letter;
    int pass = limit_subject(limit_m, limit_f, mid, final, &s_letter);

    Subject_Node* curr = p->numofSubjectType[i].head;
    while (curr) {
        if (strcmp(curr->ID, ID) == 0) {
            break;
        }
        curr = curr->next;
    }
    
    if (curr == NULL) {
        // Return 0 if the subject is not found (consider adding a debug message here)
        fprintf(stdout, "Cant find ID --- Please Enter Correct ID\n");
        return 0;
    }

    // Check and update credits based on the new pass/fail status
    if (curr->status_ever_been_study == 1) {
        if (curr->status_pass && !pass) {
            // Subject was passing, now failing
            p->ToTal_credit_pass -= curr->credit;
            p->ToTal_credit_npass += curr->credit;
        } else if (!curr->status_pass && pass) {
            // Subject was failing, now passing
            p->ToTal_credit_pass += curr->credit;
            p->ToTal_credit_npass -= curr->credit;
        }
    } else {
        if (pass) {
            p->ToTal_credit_pass += curr->credit;
        } else {
            p->ToTal_credit_npass += curr->credit;
        }
    }

    // Update subject details
    curr->status_pass = pass;
    curr->status_ever_been_study = 1;
    curr->score_letter = s_letter;
    curr->score_number_mid = mid;
    curr->score_number_final = final;

    // Update the count of passed subjects and passed credits if passing
    if (pass) {
        p->numofSubjectType[i].count_passSubject++;
        p->numofSubjectType[i].count_passCredit += curr->credit;
    }

    // Update the status alert based on non-passed credits
    p->status_alert = check_status_alert(p->ToTal_credit_npass);

    return 1;
}

void check_what_should_studie_node(Subject_Type node,int term){
    Subject_Node* curr = node.head;

    while (curr)
    {
        if(curr->term_recomment_to_studie != 0 && curr->term_recomment_to_studie  <= term + 1 && !curr->status_pass){
            printSubjectNode(curr);
        }
        curr = curr->next;
    }
    
}

void check_what_should_studie(Player p,int term){
    if(term < 1 || term > 12){
        fprintf(stderr, "Invalid number of term\n");
        return;
    }

    for (int i = 0; i < sizeSubjectType; i++)
    {
        printf("    ***%s***\n", p.numofSubjectType[i].nameoftype);
        check_what_should_studie_node(p.numofSubjectType[i],term);
    }
    return;    
}

float get_score_letter_to_score_number(char x){
    float result = 0.0;
    switch (x)
    {
    case 'A':result = 4.5;break;
    case 'a':result = 4.0;break;
    case 'B':result = 3.5;break;
    case 'b':result = 3.0;break;
    case 'C':result = 2.5;break;
    case 'c':result = 2.0;break;
    case 'D':result = 1.5;break;
    case 'd':result = 1.0;break;
    case 'F':result = 0.0;break;
    default:fprintf(stderr,"invalid score letter\n");break;
    }
    return result;
}

void count_cpa_pass(Player *p){
    float cpa = 0;
    float total = 0;
    for (int i = 0; i < sizeSubjectType; i++)
    {
        Subject_Node* curr = p->numofSubjectType[i].head;
        while (curr)
        {   
            if(curr->status_pass){
                total += get_score_letter_to_score_number(curr->score_letter) * curr->credit;
            }
            curr = curr->next;
        }
    }
    cpa = total / p->ToTal_credit_pass;
    printf("CPA PASS : %.4f\n", cpa);
    return;
}

void count_cpa_all(Player *p){
    float cpa = 0;
    float total = 0;
    for (int i = 0; i < sizeSubjectType; i++)
    {
        Subject_Node* curr = p->numofSubjectType[i].head;
        while (curr)
        {   
            if(curr->status_ever_been_study){
                total += get_score_letter_to_score_number(curr->score_letter) * curr->credit;
            }
            curr = curr->next;
        }
    }
    cpa = total / (p->ToTal_credit_pass + p->ToTal_credit_npass);
    printf("CPA ALL : %.4f\n", cpa);
    return;
}