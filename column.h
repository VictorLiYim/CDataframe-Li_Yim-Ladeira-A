#ifndef CDATAFRAME_LI_YIM_LADEIRA_A_COLUMN_H
#define CDATAFRAME_LI_YIM_LADEIRA_A_COLUMN_H

#define REALLOC_SIZE 256
#define ASC  0
#define DESC 1

typedef enum
{
    NULLVAL = 1 , UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
}ENUM_TYPE;

typedef union
{
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
}COL_TYPE;

typedef struct
{
    char *name;
    unsigned int TP;
    unsigned int TL;
    ENUM_TYPE type;
    COL_TYPE **data;
    unsigned long long int *index;
    int valid_index;
    int sort_dir;
}COLUMN;

COLUMN *create_column(ENUM_TYPE type, char* title);
int insert_value(COLUMN* col, void* value);
void delete_column(COLUMN **col);
void convert_value(COLUMN *col, unsigned long long int i, char *str, int size);
void print_col(COLUMN* col);

//fonctionnalités
int nb_occurrences(COLUMN* col, void* x);
COL_TYPE* search_val(COLUMN* col, int x);
int research_sup(COLUMN* col, void* x);
int research_inf(COLUMN* col, void* x);
int research_equal(COLUMN* col, void* x);

// Tri

void sort(COLUMN* col, int sort_dir);
int partition(COLUMN* col, int gauche, int droite, int sort_dir);
void insertion_sort(COLUMN* col, int gauche, int droite, int sort_dir);
void quicksort(COLUMN* col, int gauche, int droite, int sort_dir);
void print_col_by_index(COLUMN *col);
void erase_index(COLUMN* col);
int check_index(COLUMN* col);
void update_index(COLUMN* col);
int search_value_in_column(COLUMN *col, void *val);
#endif //CDATAFRAME_LI_YIM_LADEIRA_A_COLUMN_H
