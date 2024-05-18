#ifndef CDATAFRAME_LI_YIM_LADEIRA_A_COLUMN_H
#define CDATAFRAME_LI_YIM_LADEIRA_A_COLUMN_H

#define REALOC_SIZE 256

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
}COLUMN;

COLUMN *create_column(ENUM_TYPE type, char* title);
int insert_value(COLUMN* col, void* value);
void delete_column(COLUMN **col);
void convert_value(COLUMN *col, unsigned long long int i, char *str, int size);
void print_col(COLUMN* col);

//fonctionnalités
int nb_occurrences(COLUMN* col, int x);
int search_val(COLUMN* col, int x);
int research_sup(COLUMN* col, int x);
int research_inf(COLUMN* col, int x);
int research_equal(COLUMN* col, int x);

#endif //CDATAFRAME_LI_YIM_LADEIRA_A_COLUMN_H
