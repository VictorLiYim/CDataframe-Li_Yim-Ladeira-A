#include "functions.h"
#include <stdlib.h>
COLUMN *create_column(char* title)
{
    COLUMN *column = NULL;
    column = malloc(sizeof(COLUMN));
    column->TP = REALOC_SIZE;
    column->TL = 0;
    column->name = title;
    return column;
}
