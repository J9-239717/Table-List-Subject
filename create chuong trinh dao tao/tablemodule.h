#ifdef TABLE_MODULE

////////////////////////////////////// DEFINE //////////////////////////////////////

#define MAXSIZENAME 256
#define MAXSIZEID 26
#define MAX_COLUMNS 10
#define MAX_COLUMN_WIDTH 56

const char* name_SJ_t[] = {
        "co_so_nganh", "dai_cuong", "the_thao", "ly_luat_chinh_tri", 
        "tu_chon", "thuc_tap", "modunI", "modunII", 
        "modunIII", "modunIV", "modunV", "do_an_tot_nghiep"
};

typedef struct Subject_Node {
    char name[MAXSIZENAME];
    char ID[MAXSIZEID];
    char score_letter;
    float score_number_mid;
    float  score_number_final;
    unsigned int status_pass : 1;
    unsigned int status_ever_been_study: 2;
    unsigned int credit : 4;
    unsigned int term_recomment_to_studie: 4;
    struct Subject_Node *next;
} Subject_Node;

typedef struct _Subject_Type {
    int Total_Subject;
    unsigned int count_passSubject;
    unsigned int count_passCredit; // ADD NEW
    int Total_Credit;
    char nameoftype[MAXSIZENAME];
    Subject_Node* head;
    Subject_Node* tail;
} Subject_Type;

typedef enum {
    co_so_nganh,
    dai_cuong,
    the_thao,
    ly_luat_chinh_tri,
    tu_chon,
    thuc_tap,
    modunI,
    modunII,
    modunIII,
    modunIV,
    modunV,
    do_an_tot_nghiep,
    sizeSubjectType
} index_subject_type;

typedef struct Player {
    char name_player[MAXSIZENAME];
    int ToTal_credit_pass; // ADD NEW
    int ToTal_credit_npass;
    Subject_Type numofSubjectType[sizeSubjectType];
    unsigned int status_can_grauate : 1;
    unsigned int status_alert : 2;
} Player;

//////////////////////////////// API FUNCTION ////////////////////////////////

///// API NODE LOGIC ///
/// Sub Function ///
Subject_Node* createSubjectNode(const char* name, const char* ID, char score_letter, float score_number_mid, float score_number_final, int status_pass, int status_ever_been_study, int credit, int term_recomment_to_studie);
void addSubjectNode(Subject_Type* subjectType, Subject_Node* newNode);
void setSubjectTypeName(Subject_Type* subjectType, const char* name);
void freeSubjectNodes(Subject_Node* head);
void freePlayer(Player* player);
void printSubjectNode(const Subject_Node* node);
void printSubjectType(const Subject_Type* subjectType);
void printPlayer(const Player* player);
void initialize_subject_node(Subject_Node *node);
/// Main API ///
void initializePlayer(Player* player, const char* name);

///// LOAD DATA ///
/// Main API ///
void Load_data_Txt(Player* p);

///// Paint Table ///
/// Sub Function ///
void paint_table(FILE *fp, const char* headers[], int num_columns, const char* rows[][MAX_COLUMNS], int num_rows);
/// Main API ///
void paint_TKB_file(Player* player,FILE* fp);

///// Write Data Base Player ////
/// Main API ///
int write_dataB_player(const Player* p,FILE* fp);

///// String function ////
/// Main API ///
char* change_underscore(char* src);
void change_underscore_v(const char* src,char* return_s);
void change_space_v(const char* src,char* return_s);
char* change_space(char* src);

///// Score Logic /////
/// Sub Function ///
void check_what_should_studie(Player p,int term);
void count_cpa_pass(Player* p);
void count_cpa_all(Player* p);
void count_cpa_type_all(Player *p);
void count_cpa_type_pass(Player *p);
void show_total_subject_npass_type(Player* p);
void check_can_grauate_statue(Player* p);
void Set_all_god(Player* p);
/// Main API ///
int limit_subject(float limit_mid,float limit_final,float score_mid,float score_final,char* score_l);
int set_score_mid_and_final(Player* p, float mid, float final, float limit_m, float limit_f, int i, char ID[MAXSIZEID]);
int check_status_alert(int credit_np);
char check_score_letter(float score);

///// Read Data Base ////
/// Sub Function ///
int read_dataB_type(Subject_Type* node, FILE* fp); // Read Subject Type
/// Main API ///
int read_dataB_player(Player* p,FILE* fp); // Read Data Base and Save in Player

///// Load Input /////
/// Sub Function ///
void PayLoad_input(Player* p); // this function to set data into Player but uisng stdio

///// Show Table /////
/// Sub Function ///
void show_table(FILE* f); // this function only print file

#endif