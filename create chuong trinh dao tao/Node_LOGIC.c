#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Struct_Table.h"
#include "Node_LOGIC.h"

// Create a new Subject_Node
Subject_Node* createSubjectNode(const char* name, const char* ID, char score_letter, float score_number_mid, float score_number_final, int status_pass, int status_ever_been_study, int credit, int term_recomment_to_studie) {
    Subject_Node* newNode = (Subject_Node*)malloc(sizeof(Subject_Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    strncpy(newNode->name, name, MAXSIZENAME);
    strncpy(newNode->ID, ID, MAXSIZEID);
    newNode->score_letter = score_letter;
    newNode->score_number_mid = score_number_mid;
    newNode->score_number_final = score_number_final;
    newNode->status_pass = status_pass;
    newNode->status_ever_been_study = status_ever_been_study;
    newNode->credit = credit;
    newNode->term_recomment_to_studie = term_recomment_to_studie;
    newNode->next = NULL;

    return newNode;
}

void initialize_subject_node(Subject_Node *node) {
    // Ensure the pointer is valid
    if (node == NULL) {
        return;
    }

    // Set all fields to zero or NULL
    memset(node->name, 0, MAXSIZENAME);               // Clear the name field
    memset(node->ID, 0, MAXSIZEID);                   // Clear the ID field
    node->score_letter = '\0';                        // Set the score_letter to null character
    node->score_number_mid = 0.0f;                    // Set the midterm score to 0.0
    node->score_number_final = 0.0f;                  // Set the final score to 0.0
    node->status_pass = 0;                            // Set status_pass to 0
    node->status_ever_been_study = 0;                 // Set status_ever_been_study to 0
    node->credit = 0;                                 // Set credit to 0
    node->term_recomment_to_studie = 0;               // Set term_recomment_to_studie to 0
    node->next = NULL;                                // Set the next pointer to NULL
}

// Add a node to the end of the linked list in Subject_Type
void addSubjectNode(Subject_Type* subjectType, Subject_Node* newNode) {
    if (subjectType->head == NULL) {
        subjectType->head = newNode;
        subjectType->tail = newNode;
    } else {
        subjectType->tail->next = newNode;
        subjectType->tail = newNode;
    }
    subjectType->Total_Subject++;
    subjectType->Total_Credit += newNode->credit;

    if (newNode->status_pass) {
        subjectType->count_passSubject++;
        subjectType->count_passCredit += newNode->credit;  // Increment count_passCredit
    }
}


// Initialize the Player
void initializePlayer(Player* player, const char* name) {
    strncpy(player->name_player, name, MAXSIZENAME);
    player->ToTal_credit_pass = 0;  // Initialize ToTal_credit_pass to 0
    for (int i = 0; i < sizeSubjectType; i++) {
        player->numofSubjectType[i].Total_Subject = 0;
        player->numofSubjectType[i].count_passSubject = 0;
        player->numofSubjectType[i].count_passCredit = 0;  // Initialize count_passCredit to 0
        player->numofSubjectType[i].Total_Credit = 0;
        player->numofSubjectType[i].head = NULL;
        player->numofSubjectType[i].tail = NULL;
        memset(player->numofSubjectType[i].nameoftype, 0, MAXSIZENAME);
    }
    player->status_can_grauate = 0;
    player->status_alert = 0;
    player->ToTal_credit_npass = 0;
}

void setSubjectTypeName(Subject_Type* subjectType, const char* name) {
    // Ensure the name is within the allowed size
    strncpy(subjectType->nameoftype, name, MAXSIZENAME - 1);
    // Manually add the null terminator to avoid overflow issues
    subjectType->nameoftype[MAXSIZENAME - 1] = '\0';
}

void freeSubjectNodes(Subject_Node* head) {
    Subject_Node* current = head;
    Subject_Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void freePlayer(Player* player) {
    for (int i = 0; i < sizeSubjectType; i++) {
        freeSubjectNodes(player->numofSubjectType[i].head);
    }
}


void printSubjectNode(const Subject_Node* node) {
    if (node != NULL) {
        printf("(+)%s==", node->ID);
        printf("%s==", node->name);
        printf("%c==", node->score_letter);
        printf("%.2f==", node->score_number_mid);
        printf("%.2f==", node->score_number_final);
        printf("%s==", node->status_pass ? "Yes" : "No");
        printf("%s==", node->status_ever_been_study ? "Yes" : "No");
        printf("%d==", node->credit);
        printf("%d(+)", node->term_recomment_to_studie);
        printf("\n");
    }
}

// Print Subject_Type
void printSubjectType(const Subject_Type* subjectType) {
    printf("Subject Type: %s, Pass: %d, Total: %d, Total Credits: %d, Passed Credits: %d\n",
           subjectType->nameoftype, subjectType->count_passSubject,
           subjectType->Total_Subject, subjectType->Total_Credit, subjectType->count_passCredit);
    Subject_Node* current = subjectType->head;
    while (current != NULL) {
        printSubjectNode(current);
        current = current->next;
    }
}

// Print Player
void printPlayer(const Player* player) {
    printf("Player Name: %s\n", player->name_player);
    for (int i = 0; i < sizeSubjectType; i++) {
        printSubjectType(&player->numofSubjectType[i]);
    }
    printf("Total Credits Passed: %d\n", player->ToTal_credit_pass);  // Print ToTal_credit_pass
    printf("Status Can Graduate: %d, Status Alert: %d\n", player->status_can_grauate, player->status_alert);
}

