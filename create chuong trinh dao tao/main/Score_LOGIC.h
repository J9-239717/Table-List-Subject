#ifndef Score_LOGIC_H
#define Score_LOGIC_H

#include "Struct_Table.h"

int check_status_alert(int credit_np);
char check_score_letter(float score);
char check_score_letter(float score);
int limit_subject(float limit_mid,float limit_final,float score_mid,float score_final,char* score_l);
int set_score_mid_and_final(Player* p, float mid, float final, float limit_m, float limit_f, int i, char ID[MAXSIZEID]);
void check_what_should_studie(Player p,int term);
void count_cpa_pass(Player* p);
void count_cpa_all(Player* p);
void count_cpa_type_all(Player *p);
void count_cpa_type_pass(Player *p);
void show_total_subject_npass_type(Player* p);
void check_can_grauate_statue(Player* p);
void Set_all_god(Player* p);
#endif