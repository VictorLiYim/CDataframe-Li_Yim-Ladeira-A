//
// Created by Victor Li Yim on 19/04/2024.
//

#ifndef CDATAFRAME_LI_YIM_LADEIRA_A_COLUMN_H
#define CDATAFRAME_LI_YIM_LADEIRA_A_COLUMN_H

#define REALOC_SIZE 256

typedef struct
{
    char *name;
    int TP;
    int TL;
    int *data;
}COLUMN;

COLUMN *create_column(char* title);
int insert_value(COLUMN* col, int value);
void delete_column(COLUMN **col);
void print_col(COLUMN* col);

#endif //CDATAFRAME_LI_YIM_LADEIRA_A_COLUMN_H
