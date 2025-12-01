#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Struct_Table.h"
#include "Node_LOGIC.h"
#include "LoadDT.h"

// Load data from text files
void Load_data_Txt(Player* p) {
    FILE* fp = fopen("file/importantFile/dataCTDT.txt", "r");
    FILE* fi = fopen("file/importantFile/dataCredit_and_Term.txt", "r");
    if (!fp || !fi) {
        printf("Failed to open file.\n");
        return;
    }

    char buffer[61];
    char buffer_i[25];
    int count_SubjectType = -1;
    char buffer_g[2][61];
    int term, tin;
    while (fgets(buffer, sizeof(buffer), fp)) {
        fgets(buffer_i, sizeof(buffer_i), fi);
        buffer[strcspn(buffer, "\r\n")] = '\0';
        buffer_i[strcspn(buffer_i, "\r\n")] = '\0';
        memset(buffer_g, 0, sizeof(buffer_g));

        int count_word = 0;
        int c_s = 0;
        int c_id = 0;
        int lengh = strlen(buffer);
        int skip = 0;

        for (int i = 0; i < lengh; i++) {
            if (buffer[0] == '/') {
                skip = 1;
                count_SubjectType++;
                break;
            } else if (buffer[i] == ' ') {
                count_word = 1;
                continue;
            } else if (buffer[i] != ' ' && count_word == 0) {
                buffer_g[count_word][c_id++] = buffer[i];
            } else {
                buffer_g[count_word][c_s++] = buffer[i];
            }
        }

        if (skip) continue;

        buffer_g[0][c_id] = '\0';
        buffer_g[1][c_s] = '\0';
        sscanf(buffer_i, "%d %d", &term, &tin);
        Subject_Node* subj = createSubjectNode(buffer_g[1], buffer_g[0], 'X', 0.0, 0.0, 0, 0, tin, term);
        addSubjectNode(&p->numofSubjectType[count_SubjectType], subj);
        if (subj->status_pass) {
            p->ToTal_credit_pass += subj->credit;  // Increment ToTal_credit_pass for the Player
        }
    }
    fclose(fp);
    fclose(fi);
}
