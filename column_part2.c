#include "column.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

COLUMN *create_column(ENUM_TYPE type, char* title)
{
    COLUMN *col = (COLUMN*) malloc(sizeof(COLUMN)); // Allouer de la mémoire pour la colonne
    if (col == NULL) {
        printf("Erreur lors de l'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    col->TP = 0;
    col->TL = 0;
    col->type = type;
    col->name = strdup(title);
    col->data = NULL;
    col->index = NULL;
    return col;
}

// Fonction pour ajouter une valeur à la colonne
int insert_value(COLUMN* col, void* value) {
    if (col->TP == 0) {
        int new_size = REALOC_SIZE;
        COL_TYPE *new_data = (COL_TYPE *) malloc(new_size * sizeof(COL_TYPE));
        if (new_data == NULL) {
            return 0;
        }
        col->data = new_data;
        col->TP = new_size;
    } else if (col->TL >= col->TP) {
        int new_size = col->TP + 256;
        COL_TYPE *new_data = (COL_TYPE *) realloc(col->data, new_size * sizeof(COL_TYPE)); // Réallocation
        if (new_data == NULL) {
            return 0;
        }
        col->data = new_data;
        col->TP = new_size;
    }

    COL_TYPE *new_data = (COL_TYPE *) malloc(sizeof(COL_TYPE));
    if(value == NULL)
    {
        new_data->string_value = NULL;
    }
    else
    {
        switch (col->type)
        {
            case UINT:
                new_data->uint_value = *(unsigned int *) value;
                break;
            case INT:
                new_data->int_value = *(signed int *) value;
                break;
            case CHAR:
                new_data->char_value = *(char *) value;
                break;
            case FLOAT:
                new_data->float_value = *(float *) value;
                break;
            case DOUBLE:
                new_data->double_value = *(double *) value;
                break;
            case STRING:
                new_data->string_value = strdup((char *) value);
                break;
            case STRUCTURE:
                new_data->struct_value = value;
                break;
            default:
                return 0;
        }
    }
    col->data[col->TL] = value;
    col->TL++;
    return 1;
}

void delete_column(COLUMN **col) {
    if (col == NULL || *col == NULL) {
        printf("ERREUR\n");
        exit(EXIT_FAILURE);
    }
    // Libérer le tableau de données
    free((*col)->data);
    // Libérer la structure de colonne
    free(*col);
    *col = NULL;
}

void convert_value(COLUMN* col, unsigned long long int i, char* str, int size)
{

    switch(col->type){

        case INT:
            snprintf(str, size, "%d", *((int*)col->data[i]));
            col->data[i] = str;
            break;
        case FLOAT:
            snprintf(str, size, "%f", *((float*)col->data[i]));
            col->data[i] = str;
            break;
        case UINT:
            snprintf(str, size, "%d", *((int*)col->data[i]));
            col->data[i] = str;
            break;
        case CHAR:
            snprintf(str, size, "%c", *((char*)col->data[i]));
            col->data[i] = str;
            break;
        case DOUBLE:
            snprintf(str, size, "%lf", *((double*)col->data[i]));
            col->data[i] = str;
            break;
        case STRING:
            break;
        default:
            snprintf(str, size, "Format inconnu");
            col->data[i] = str;
            break;
    }
}

void print_col(COLUMN* col){
    int i, j;
    for(j = 0; j<col->TL; j++)
    {
        char *str = (char *) malloc(50 * sizeof(char));
        if(col->data[j] != NULL) {
            convert_value(col, j, str, 50);
        }
    }

    printf("[NAME] %s\n", col->name);
    for(i = 0; i<col->TL; i++){
        if(col->data[i] == NULL)
        {
            printf("[%d] NULL\n", i);
        }
        else
        {
            printf("[%d] %s\n", i, col->data[i]);
        }
    }
}
