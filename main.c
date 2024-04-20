//
// Created by Victor Li Yim on 28/03/2024.
//
#include<stdio.h>
#include<stdlib.h>
#include "functions.h"
#include<string.h>

int main() {
    int num_columns;
    printf("Enter the number of columns: ");
    scanf("%d", &num_columns);
    CDataframe* cdataframe = create_CDataframe(num_columns);

    // Demander à l'utilisateur de saisir les données pour chaque colonne
    read_cdataframe_hardway(cdataframe);

    // Afficher le CDataframe
    add_column(cdataframe);
    print_CDataframe(cdataframe);
    print_CDataframe_limited_raw(cdataframe);
    print_CDataframe_limited_columns(cdataframe);
    // Libérer la mémoire allouée pour le CDataframe
    for (int i = 0; i < cdataframe->num_columns; i++) {
        free(cdataframe->columns[i]->data);
        free(cdataframe->columns[i]->name);
        free(cdataframe->columns[i]);
    }
    free(cdataframe->columns);
    free(cdataframe);

    return 0;
}


