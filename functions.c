#include "functions.h"
#include <stdlib.h>
#include <stdio.h>


COLUMN *create_column(char* title)
{
    COLUMN *col = malloc(sizeof(COLUMN)); // Allouer de la mémoire pour la colonne
    if (col == NULL) {
        printf(stderr, "Erreur lors de l'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    COLUMN *column = NULL;
    column = malloc(sizeof(COLUMN));
    column->TP = 0;
    column->TL = 0;
    column->name = title;
    column->data = NULL;
    return column;
}

// Fonction pour ajouter un entier à la colonne
int insert_value(COLUMN* col, int value){
    if (col->TP == 0) {
        int new_size = REALOC_SIZE;
        int *new_data = (int *) malloc(new_size * sizeof(int));
        if (new_data == NULL) {
            return 0;
        }
    }
    else if (col->TL >= col->TP) {
        int new_size = col->TP + 256;
        int* new_data = (int *) realloc(col->data, new_size * sizeof(int)); // Réallocation
        if (new_data == NULL) {
            return 0;
        }
        col->data = new_data;
        col->TP = new_size;
    }
    col->data[col->TL] = value;
    col->TL++;
    return 1;
}

void delete_column(COLUMN **col){
    if (col == NULL || *col == NULL) {
        printf("Column NULL\n");
        return;
    }
    // Libérer le tableau de données
    free((*col)->data);
    // Libérer la structure de colonne
    free(*col);
    // Définir le pointeur de colonne sur NULL pour éviter les accès accidentels
    *col = NULL;
}

void print_col(COLUMN* col){
    int i;
    printf("%d", col->TL);
    for(i = 0; i<col->TL; i++){
        printf("[%d] %d", i, col->data[i]);
    }
}
/*
Cdataframe *create_Cdataframe(){
    Cdataframe *CDataframe = malloc(sizeof(Cdataframe));
    Cdataframe->column = NULL;
    Cdataframe->nbcolumn = 0;
    return Cdataframe;
}*/