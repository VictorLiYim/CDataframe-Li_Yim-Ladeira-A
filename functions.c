#include "functions.h"
#include <stdlib.h>

COLUMN *create_column(char* title)
{
    COLUMN *column = NULL;
    column = malloc(sizeof(COLUMN));
    column->TP = malloc(REALOC_SIZE);
    column->TL = 0;
    column->name = title;
    return column;
}

int insert_value(COLUMN* col, int value){
    int verif = 0;
    int *temp = col->TP;
    if(col->TP == col->TL){
        temp = realloc(&temp,REALOC_SIZE);
        while(temp == NULL){
            temp = realloc(&temp,REALOC_SIZE);
        }
        col->TP = temp;
    }
    col->data[col->TL]

    return 0;
}