//
// Created by Victor Li Yim on 19/04/2024.
//
#include "column.h"
#include <stdio.h>
#include <stdlib.h>
COLUMN *create_column(char* title)
{
    COLUMN *col = (COLUMN*) malloc(sizeof(COLUMN)); // Allouer de la mémoire pour la colonne
    if (col == NULL) {
        printf("Erreur lors de l'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    col->TP = 0;
    col->TL = 0;
    col->name = title;
    col->data = NULL;
    return col;
}

// Fonction pour ajouter un entier à la colonne
int insert_value(COLUMN* col, int value){
    if (col->TP == 0) {
        int new_size = REALOC_SIZE;
        int *new_data = (int *) malloc(new_size * sizeof(int));
        if (new_data == NULL) {
            return 0;
        }
        col->data = new_data;
        col->TP = new_size;
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
    for(i = 0; i<col->TL; i++){
        printf("[%d] %d\n", i, col->data[i]);
    }
}

#include "column.h"
