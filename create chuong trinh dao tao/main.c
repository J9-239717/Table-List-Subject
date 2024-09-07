#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Struct_Table.h"
#include "Node_LOGIC.h"
#include "LoadDT.h"
#include "PaintTable.h"
#include "Write_dataB.h"
#include "functionhleperstr.h"
#include "Score_LOGIC.h"
#include "Read_dataB.h"
#include "Load_input.h"
#include "Show_Table.h"

// Main function
int main() {
    // Constants for subject types
    const char* name_SJ_t[] = {
        "co_so_nganh", "dai_cuong", "the_thao", "ly_luat_chinh_tri", 
        "tu_chon", "thuc_tap", "modunI", "modunII", 
        "modunIII", "modunIV", "modunV", "do_an_tot_nghiep"
    };
    Player player;
    char nameDataB[MAXSIZENAME] = "file/dataB";
    char nameTable[MAXSIZENAME] = "file/table";
    char txt[5] = ".txt";
    char buffername[36];

    int command = 0;
    int end = 0;
    int createNew = 0;

    do {
        // Set basic data
        fprintf(stdout, "Please Enter your name: ");
        scanf("%35s", buffername);  // safer without `[^\n]`
        char c;
        while ((c = getchar()) != '\n' && c != EOF);  // clear input buffer

        // Create file names
        strncat(nameDataB, buffername, sizeof(nameDataB) - strlen(nameDataB) - 1);
        strncat(nameDataB, txt, sizeof(nameDataB) - strlen(nameDataB) - 1);
        strncat(nameTable, buffername, sizeof(nameTable) - strlen(nameTable) - 1);
        strncat(nameTable, txt, sizeof(nameTable) - strlen(nameTable) - 1);

        FILE* f_dataB = fopen(nameDataB, "r");
        if (!f_dataB) {
            do {
                fprintf(stdout, "You don't have a database file.\n"
                                "Do you want to create a new file or enter a new name?\n"
                                "Enter 1 to create a new file\n"
                                "Enter 2 to enter a new name\n"
                                "Please Enter: ");
                scanf("%d", &command);
                while ((c = getchar()) != '\n' && c != EOF);  // clear input buffer

                if (command == 1) {
                    end = 1;
                    createNew = 1;
                    break;
                } else if (command == 2) {
                    strcpy(nameDataB, "file/dataB");
                    strcpy(nameTable, "file/table");
                    break;
                } else {
                    fprintf(stdout, "Invalid input, please enter again.\n");
                }
            } while (command != 1 && command != 2);
        } else {
            fprintf(stdout, "Successfully opened file: %s\n\n", nameDataB);
            fclose(f_dataB);
            end = 1;
        }
    } while (!end);

    initializePlayer(&player, buffername);
    
    if (createNew) {
        // Set up new data
        char buffer[36];
        for (int i = 0; i < sizeSubjectType; i++) {
            change_underscore_v(name_SJ_t[i], buffer);
            setSubjectTypeName(&player.numofSubjectType[i], buffer);
        }
        Load_data_Txt(&player);
    } else {
        // Read data from existing database
        FILE* dataBase = fopen(nameDataB, "r");
        if (dataBase && read_dataB_player(&player, dataBase)) {
            fprintf(stdout, "Read Complete\n\n");
        } else {
            fprintf(stdout, "Can't read file\n");
            fclose(dataBase);
            exit(EXIT_FAILURE);
        }
        fclose(dataBase);
    }

    command = 0;
    end = 0;

    do {
        fprintf(stdout, "        Welcome        \n");
        printf("1. Set up Data\n"
               "2. Save Data\n"
               "3. Print Player\n"
               "4. Check What You should study in term\n"
               "5. Show Table\n"
               "6. Count CPA\n"
               "7. Show Subject Not pass per type of Subject\n"
               "8. Check Grauate\n"
               "0. End Program\n"
               "!!Please save data before ending the program!!\n"
               "Enter: ");
        scanf("%d", &command);
        char clean;
        while ((clean = getchar()) != '\n' && clean != EOF);  // clear input buffer
        if(command == 397)goto GOD;
        switch (command) {
            case 1:
                // Load input
                PayLoad_input(&player);
                printf("Load input Completed\n");
                break;
            case 2: {
                // Write and paint for update
                FILE* f_dataB = fopen(nameDataB, "w");
                FILE* f_table = fopen(nameTable, "w");
                if (f_dataB && f_table) {
                    write_dataB_player(&player, f_dataB);
                    paint_TKB_file(&player, f_table);
                    printf("Save File Completed\n");
                } else {
                    fprintf(stderr, "Error opening file for writing\n");
                }
                fclose(f_dataB);
                fclose(f_table);
                break;
            }
            case 3:
            printPlayer(&player);
            break;
            case 4:{
                int term;
                printf("Enter your current term: ");scanf("%d", &term);
                while ((clean = getchar()) != '\n' && clean != EOF);
                check_what_should_studie(player,term);
                break;
            }
            case 5:{
                FILE* file_table = fopen(nameTable,"r");
                if(file_table == NULL){
                    fprintf(stderr,"Cant find %s",nameTable);
                    fclose(file_table);
                    break;
                }
                show_table(file_table);
                fclose(file_table);
                break;
            }
            case 6:
                count_cpa_pass(&player);
                count_cpa_all(&player);
                count_cpa_type_pass(&player);
                count_cpa_type_all(&player);
                break;
            case 7:
                show_total_subject_npass_type(&player);
                break;
            case 8:
                check_can_grauate_statue(&player);
                break;
            case 0:
                end = 1;
                break;
            case -1:
                GOD:
                Set_all_god(&player);
                break;
            default:
                printf("Invalid input, please enter again\n");
                break;
        }
    } while (!end);

    printf("Thank you\n");
    // Free resources
    freePlayer(&player);

    return 0;
}
