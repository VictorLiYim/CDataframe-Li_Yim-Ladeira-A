#include "functions.h"

COLUMN *create_column(char* title)
{
    COLUMN *column;
    column->name = title;
    return column;
}