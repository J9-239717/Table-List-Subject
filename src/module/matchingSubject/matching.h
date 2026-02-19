#ifndef MATCHING_SUBJECT_H
#define MATCHING_SUBJECT_H

#include "../../main/Struct_Table.h"

#define RESET       "\033[0m"
#define BLACK_TXT   "\033[30m"

#define BG_BLUE     "\033[44m"
#define BG_GREEN    "\033[42m"
#define BG_YELLOW   "\033[43m"
#define BG_RED      "\033[41m"

#define FG_BLUE     "\033[34m"
#define FG_GREEN    "\033[32m"
#define FG_YELLOW   "\033[33m"
#define FG_RED      "\033[31m"

#define P_NEWLINE        printf("\n");
#define LOG_INFO(msg,...)    printf(FG_BLUE "[INFO] " RESET msg, ##__VA_ARGS__); P_NEWLINE
#define LOG_WARN(msg,...)    printf(FG_YELLOW "[WARN] " RESET msg, ##__VA_ARGS__); P_NEWLINE
#define LOG_ERROR(msg,...)   printf(FG_RED "[ERROR] " RESET msg, ##__VA_ARGS__); P_NEWLINE
#define LOG_TELL(msg,...)    printf(FG_GREEN "[TELL] " RESET msg, ##__VA_ARGS__); P_NEWLINE

float choices[] = {2.0f, 2.5f, 3.2f};
char choices_c[] = {'c', 'C', 'B'};

#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

void start_matching_subject(Player* p);


static float get_score_letter_to_score_number(char x){
    float result = 0.0;
    switch (x)
    {
    case 'A':result = 4.5f;break;
    case 'a':result = 4.0f;break;
    case 'B':result = 3.5f;break;
    case 'b':result = 3.0f;break;
    case 'C':result = 2.5f;break;
    case 'c':result = 2.0f;break;
    case 'D':result = 1.5f;break;
    case 'd':result = 1.0f;break;
    case 'F':result = 0.0f;break;
    case 'X':result = 0.0f;break;
    default:fprintf(stderr,"invalid score letter\n");break;
    }
    return result;
}

char score_4[] = {'F','d','D','c','C','b','B','a','A'};
#define MAX_INDEX 8

static int getIndexScoreChar(char score) {
    for(int i = 0; i < MAX_INDEX + 1; i++) {
        if(score_4[i] == score) {
            return i;
        }
    }
    return -1; // Not found
}

static int finding(Player* p,char target_score,int *index_rt,int8_t visted[][128]) {
  for(int i = co_so_nganh; i < sizeSubjectType; i++) {
      if(i == the_thao) {
          continue; // Skip these types
      }
      Subject_Node* current = p->numofSubjectType[i].head;
      for(int j = 0; j < p->numofSubjectType[i].Total_Subject; j++) {
          if(get_score_letter_to_score_number(current->score_letter) >= get_score_letter_to_score_number(target_score) && current->status_pass && !visted[i][j]) {
              *index_rt = j;
              return i;
          }
          current = current->next;
      }
  }
  return -1; // Not found
}

static char upscale_score(char score,int choice) {
  float current_score = get_score_letter_to_score_number(score);
  if(current_score >= choices[choice]) {
      return score; // No need to upscale
  }

  int index = getIndexScoreChar(score);
  int target_index = getIndexScoreChar(choices_c[choice]);

  if((target_index - index) + target_index > MAX_INDEX) {
      return 'A'; // Max score
  } else {
      return score_4[(target_index - index) + target_index];
  }
}

static void mapscore(char* src) {
    if(strcmp(src, "X") == 0 || strcmp(src, "F") == 0) return;
    if (!islower(*src)) {
        src[1] = '+';
        src[2] = '\0';
    } else {
        *src = toupper(*src);
        src[1] = '\0';
    }
}

static void matching(Player* p, int choice, int8_t visted[][128]) {
    // Payload
    LOG_INFO("Matching subjects for target CPA...");
    // Check for dai_coung subjects first
    Subject_Node* curr = p->numofSubjectType[dai_cuong].head;
    for(int i = 0; i < p->numofSubjectType[dai_cuong].Total_Subject; i++, curr = curr->next)
    {
      if(!curr->status_pass || visted[dai_cuong][i] || get_score_letter_to_score_number(curr->score_letter) >= choices[choice]) {
          continue; // Already passed or visited
      }
      int index = 0,type_index = finding(p,upscale_score(curr->score_letter,choice),&index,visted);
      if(type_index == -1) { // Not found
        char c = curr->score_letter;
        mapscore(&c);
        LOG_WARN("1.Subject mismatch is %s with score %c", curr->name, c);
        visted[type_index][index] = 1;
      }else {
        visted[type_index][index] = 1; // Mark as visited
        visted[dai_cuong][i] = 1; // Mark as visited
      }
    }

    for(int i = co_so_nganh; i < sizeSubjectType; i++) {
        curr = p->numofSubjectType[i].head;
        if(i == dai_cuong || i == the_thao) {
            continue; // Already processed and not required
        }
        for(int j = 0; j < p->numofSubjectType[i].Total_Subject; j++, curr = curr->next) {
            if(!curr->status_pass || visted[i][j] || get_score_letter_to_score_number(curr->score_letter) >= choices[choice]) {
                continue; // Already passed or visited
            }
            int index = 0,type_index = finding(p,upscale_score(curr->score_letter,choice),&index,visted);
            if(type_index != -1) { // Not found
              char c = curr->score_letter;
              mapscore(&c);
              LOG_WARN("2.Subject mismatch is %s with score %c", curr->name, c);
              visted[type_index][index] = 1;
            }else {
              visted[type_index][index] = 1; // Mark as visited
              visted[i][j] = 1; // Mark as visited
            }
        }
    }
}

void start_matching_subject(Player* p) {
    // Payload
    int choice;
    do{
      LOG_TELL("Choose your target type to graduate: ");
      printf("1. Normal (CPA >= 2.0)\n");
      printf("2. Good (CPA >= 2.5)\n");
      printf("3. Excellent (CPA >= 3.2)\n");
      printf("Enter choice (1-3): ");
      scanf("%d", &choice);
      while (getchar() != '\n');
      if(choice < 1 || choice > 3){
          LOG_ERROR("Invalid choice. Please select a valid option.");
          continue;
      }else {
        break;
      }
    }while (1);
    choice--;
    int8_t visted[128][128] = {0}; // mask for [type_subject][number_of_subjects]

    LOG_INFO("Starting subject matching process...");
    matching(p, choice, visted);
    LOG_INFO("Subject matching process completed.");
}


#endif /* MATCHING_SUBJECT_H */