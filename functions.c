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
    col->TP += REALOC_SIZE;
    int *temp;
    if(col->TP >= col->TL){
        // Réallouer de la mémoire pour le tableau
        col->TP += REALOC_SIZE;
        if(temp == NULL){
            return 0;
        }
        else{
            // Ajouter la valeur au tableau
            col->data[col->TL++] = value;
        }
    }
    return 1;
}






