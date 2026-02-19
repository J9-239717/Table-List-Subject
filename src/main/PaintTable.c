#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "PaintTable.h"
#include "Struct_Table.h"

// Function to change score letter
void changescoreletter(char* src) {
    if(strcmp(src, "X") == 0 || strcmp(src, "F") == 0) return;
    if (!islower(*src)) {
        src[1] = '+';
        src[2] = '\0';
    } else {
        *src = toupper(*src);
        src[1] = '\0';
    }
}

// Function to print a formatted table
void paint_table(FILE *fp, const char* headers[], int num_columns, const char* rows[][MAX_COLUMNS], int num_rows) {
    if (fp == NULL) {
        fprintf(stderr, "Error: File pointer is NULL.\n");
        return;
    }

    if (headers == NULL || rows == NULL) {
        fprintf(stderr, "Error: Headers or rows array is NULL.\n");
        return;
    }

    int column_widths[MAX_COLUMNS] = {0};

    // Calculate column widths
    for (int i = 0; i < num_columns; i++) {
        if (headers[i] == NULL) {
            fprintf(stderr, "Error: Header at index %d is NULL.\n", i);
            return;
        }
        column_widths[i] = strlen(headers[i]);

        for (int j = 0; j < num_rows; j++) {
            if (rows[j][i] == NULL) {
                fprintf(stderr, "Error: %s\n", rows[j-1][i]);
                fprintf(stderr, "Error: Row at (%d, %d) is NULL.\n", j, i);
                return;
            }
            int cell_width = strlen(rows[j][i]);
            if (cell_width > column_widths[i]) {
                column_widths[i] = (cell_width > MAX_COLUMN_WIDTH) ? MAX_COLUMN_WIDTH : cell_width;
            }
        }
    }

    // Print header separator
    fprintf(fp, "+");
    for (int i = 0; i < num_columns; i++) {
        for (int j = 0; j < column_widths[i] + 2; j++) {
            fprintf(fp, "-");
        }
        fprintf(fp, "+");
    }
    fprintf(fp, "\n");

    // Print headers
    fprintf(fp, "|");
    for (int i = 0; i < num_columns; i++) {
        fprintf(fp, " %-*s |", column_widths[i], headers[i]);
    }
    fprintf(fp, "\n");

    // Print header separator again
    fprintf(fp, "+");
    for (int i = 0; i < num_columns; i++) {
        for (int j = 0; j < column_widths[i] + 2; j++) {
            fprintf(fp, "-");
        }
        fprintf(fp, "+");
    }
    fprintf(fp, "\n");

    // Print rows
    for (int i = 0; i < num_rows; i++) {
        fprintf(fp, "|");
        for (int j = 0; j < num_columns; j++) {
            fprintf(fp, " %-*.*s |", column_widths[j], column_widths[j], rows[i][j]);
        }
        fprintf(fp, "\n");
    }

    // Print bottom separator
    fprintf(fp, "+");
    for (int i = 0; i < num_columns; i++) {
        for (int j = 0; j < column_widths[i] + 2; j++) {
            fprintf(fp, "-");
        }
        fprintf(fp, "+");
    }
    fprintf(fp, "\n");
}

// Function to write player data to a file in a formatted way
void paint_TKB_file(Player* player, FILE* fp) {
    // Player Info
    fprintf(fp, "Player Name: %s\n", player->name_player);
    fprintf(fp, "Total Credits Passed: %d\n", player->ToTal_credit_pass);
    fprintf(fp, "Status Can Graduate: %d\n", player->status_can_grauate);
    fprintf(fp, "Status Alert: %d\n", player->status_alert);
    fprintf(fp, "Total Credit Not Pass: %d\n", player->ToTal_credit_npass);
    fprintf(fp, "\n");

    // Headers for the Subject_Type table
    const char* type_headers[] = { "Subject Type", "Total Subjects", "Passed Subjects", "Total Credits", "Passed Credits" };

    for (int i = 0; i < sizeSubjectType; i++) {
        if (player->numofSubjectType[i].Total_Subject > 0) {
            const char* type_rows[1][MAX_COLUMNS];
            char total_subjects[10], passed_subjects[10], total_credits[10], passed_credits[10];

            snprintf(total_subjects, sizeof(total_subjects), "%d", player->numofSubjectType[i].Total_Subject);
            snprintf(passed_subjects, sizeof(passed_subjects), "%d", player->numofSubjectType[i].count_passSubject);
            snprintf(total_credits, sizeof(total_credits), "%d", player->numofSubjectType[i].Total_Credit);
            snprintf(passed_credits, sizeof(passed_credits), "%d", player->numofSubjectType[i].count_passCredit);

            type_rows[0][0] = player->numofSubjectType[i].nameoftype;
            type_rows[0][1] = total_subjects;
            type_rows[0][2] = passed_subjects;
            type_rows[0][3] = total_credits;
            type_rows[0][4] = passed_credits;

            paint_table(fp, type_headers, 5, type_rows, 1);

            // Headers for the Subject_Node table
            const char* subject_headers[] = { "Subject Name", "ID", "Score", "Midterm", "Final", "Pass", "Credits", "Term" };

            // Collect rows data
            const Subject_Node* current = player->numofSubjectType[i].head;
            int row_count = player->numofSubjectType[i].Total_Subject;
            const char* subject_rows[row_count][MAX_COLUMNS];

            // Ensure all pointers are initialized to NULL
            memset(subject_rows, 0, sizeof(subject_rows));

            int row_index = 0;
            while (current != NULL) {
                char score_letter[3];
                char score_mid[10];
                char score_final[10];
                char pass[10];
                char credits[10];
                char term[10];

                snprintf(score_letter, sizeof(score_letter), "%c", current->score_letter);
                snprintf(score_mid, sizeof(score_mid), "%.2f", current->score_number_mid);
                snprintf(score_final, sizeof(score_final), "%.2f", current->score_number_final);
                snprintf(pass, sizeof(pass), "%s", (current->status_pass == 1) ? "YES" : "NO");
                snprintf(credits, sizeof(credits), "%d", current->credit);
                snprintf(term, sizeof(term), "%d", current->term_recomment_to_studie);

                changescoreletter(score_letter);

                subject_rows[row_index][0] = strdup(current->name);
                subject_rows[row_index][1] = strdup(current->ID);
                subject_rows[row_index][2] = strdup(score_letter);
                subject_rows[row_index][3] = strdup(score_mid);
                subject_rows[row_index][4] = strdup(score_final);
                subject_rows[row_index][5] = strdup(pass);
                subject_rows[row_index][6] = strdup(credits);
                subject_rows[row_index][7] = strdup(term);

                row_index++;
                current = current->next;
            }

            // Print the table for this subject type
            paint_table(fp, subject_headers, 8, subject_rows, row_count);

            // Free the allocated memory
            for (int r = 0; r < row_count; r++) {
                free((void*)subject_rows[r][0]);
                free((void*)subject_rows[r][1]);
                free((void*)subject_rows[r][2]);
                free((void*)subject_rows[r][3]);
                free((void*)subject_rows[r][4]);
                free((void*)subject_rows[r][5]);
                free((void*)subject_rows[r][6]);
                free((void*)subject_rows[r][7]);
            }
        }
    }
}
