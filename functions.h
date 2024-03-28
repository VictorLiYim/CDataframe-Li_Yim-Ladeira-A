
#ifndef CDATAFRAME_LI_YIM_LADEIRA_A_FUNCTIONS_H
#define CDATAFRAME_LI_YIM_LADEIRA_A_FUNCTIONS_H

#define REALOC_SIZE 256

typedef struct
{
    char *name;
    int data;
}COLUMN;


COLUMN *create_column(char* title);

#endif //CDATAFRAME_LI_YIM_LADEIRA_A_FUNCTIONS_H
