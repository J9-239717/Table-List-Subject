#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Struct_Table.h"
#include "Node_LOGIC.h"
#include "functionhleperstr.h"
#include "Read_dataB.h"

// Function to read subject type data from the file
int read_dataB_type(Subject_Type* node, FILE* fp) {
    char copy[MAXSIZENAME];
    char buffer[MAXSIZENAME];

    // Reading subject type data
    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        printf("Error reading subject type data\n");
        return 0;
    }
    sscanf(buffer,"<%s ", copy);

    // Convert underscores to spaces
    change_underscore_v(copy, node->nameoftype);


    unsigned int b_s_p, b_e_b, b_c, b_t;

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strcmp(buffer, "</>\n") == 0) break;

        Subject_Node* temp = (Subject_Node*)malloc(sizeof(Subject_Node));
        if (!temp) {
            fprintf(stderr, "Memory allocation failed\n");
            return 0;
        }

        initialize_subject_node(temp);

        if (sscanf(buffer, "$%s %s %c %f %f %d %d %d %d$\n",
                   temp->name, temp->ID, &temp->score_letter,
                   &temp->score_number_mid, &temp->score_number_final,
                   &b_s_p, &b_e_b, &b_c, &b_t) != 9) {

            free(temp);
            printf("Error parsing subject node\n");
            return 0;
        }

        temp->status_pass = b_s_p;
        temp->status_ever_been_study = b_e_b;
        temp->credit = b_c;
        temp->term_recomment_to_studie = b_t;

        addSubjectNode(node, temp);
    }

    return 1;
}

// Function to read player data from the file
int read_dataB_player(Player* p, FILE* fp) {
    int temp_st_g, temp_st_a;

    if (fscanf(fp, "[%s %d %d %d %d]\n", p->name_player, &p->ToTal_credit_pass, 
               &p->ToTal_credit_npass, &temp_st_g, &temp_st_a) != 5) {
        printf("Error parsing player data\n");
        return 0;
    }

    p->status_can_grauate = temp_st_g;
    p->status_alert = temp_st_a;


    for (int i = 0; i < sizeSubjectType; i++) {
        int a,b,c,d;
        if (!read_dataB_type(&p->numofSubjectType[i], fp)) {
            printf("Error reading subject type\n");
            return 0;
        }     
    }

    return 1;
}
