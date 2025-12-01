#include <stdio.h>
#include "Struct_Table.h"
#include "functionhleperstr.h"
#include "Write_dataB.h"

int write_dataB_node(const Subject_Node* node,FILE* fp){
    if(node == NULL)return 0;

    fprintf(fp,"$%s %s %c %.2f %.2f %d %d %d %d$\n", 
                node->name,
                node->ID,
                node->score_letter,
                node->score_number_mid,
                node->score_number_final,
                node->status_pass,
                node->status_ever_been_study,
                node->credit,
                node->term_recomment_to_studie);
    return 1;
}

int write_dataB_type(const Subject_Type* node,FILE* fp){
    char copy[MAXSIZENAME];
    change_space_v(node->nameoftype,copy);
    fprintf(fp,"< %s %d %d %d %d >\n",
    copy,
    node->Total_Subject,
    node->count_passSubject,
    node->Total_Credit,
    node->count_passCredit);

    Subject_Node* curr = node->head;
    while(curr){
        if(!write_dataB_node(curr,fp))return 0;
        curr = curr->next;
    }

    fprintf(fp,"</>\n");
    return 1;
}

// write to txt
int write_dataB_player(const Player* p,FILE* fp){
    fprintf(fp,"[%s %d %d %d %d]\n",
    p->name_player,
    p->ToTal_credit_pass,
    p->ToTal_credit_npass,
    p->status_can_grauate,
    p->status_alert);

    for (int i = 0; i < sizeSubjectType; i++) {
        write_dataB_type(&p->numofSubjectType[i],fp);
    }

    fprintf(fp,"MADE BY J9\n");
    return 1;
}