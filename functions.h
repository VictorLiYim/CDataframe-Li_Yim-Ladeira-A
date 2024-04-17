#ifndef CDATAFRAME_LI_YIM_LADEIRA_A_FUNCTIONS_H
#define CDATAFRAME_LI_YIM_LADEIRA_A_FUNCTIONS_H

#define REALOC_SIZE 256

typedef struct
{
    char *name;
    int TP;
    int TL;
    int *data;
}COLUMN;

typedef struct {
    COLUMN** columns;  // Tableau de pointeurs vers les colonnes
    int num_columns;   // Nombre de colonnes
}CDataframe;

COLUMN *create_column(char* title);
int insert_value(COLUMN* col, int value);
void delete_column(COLUMN **col);
void print_col(COLUMN* col);

int nb_occurrences(COLUMN* col, int x);
int search_val(COLUMN* col, int x);
int research_sup(COLUMN* col, int x);
int research_inf(COLUMN* col, int x);
int research_equal(COLUMN* col, int x);

CDataframe* create_dataframe(int num_columns);
int add_column(CDataframe* dataframe, char* title);
void delete_dataframe(CDataframe** dataframe);
void read_Dataframe(CDataframe* dataframe);
void read_cdataframe_hardway(CDataframe* cdataframe);

void print_dataframe(CDataframe* dataframe);

#endif //CDATAFRAME_LI_YIM_LADEIRA_A_FUNCTIONS_H
