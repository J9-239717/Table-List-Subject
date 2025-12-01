#ifndef NODE_LOGIC_H
#define NODE_LOGIC_H

#include "Struct_Table.h"
#include <stdio.h>
// Function declarations
Subject_Node* createSubjectNode(const char* name, const char* ID, char score_letter, float score_number_mid, float score_number_final, int status_pass, int status_ever_been_study, int credit, int term_recomment_to_studie);
void addSubjectNode(Subject_Type* subjectType, Subject_Node* newNode);
void initializePlayer(Player* player, const char* name);
void setSubjectTypeName(Subject_Type* subjectType, const char* name);
void freeSubjectNodes(Subject_Node* head);
void freePlayer(Player* player);
void printSubjectNode(const Subject_Node* node);
void printSubjectType(const Subject_Type* subjectType);
void printPlayer(const Player* player);
void initialize_subject_node(Subject_Node *node);

#endif