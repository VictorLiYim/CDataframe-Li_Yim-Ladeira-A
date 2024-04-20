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

    // Créer un CDataframe avec les titres de colonne spécifiés par l'utilisateur
    COLUMN** cdataframe = create_CDataframe(num_columns);
    if (cdataframe == NULL) {
        printf("Failed to create dataframe\n");
        return EXIT_FAILURE;
    }

    // Lire les valeurs pour chaque colonne
    read_CDataframe_hardway(cdataframe, num_columns);

    // Afficher le CDataframe
    print_CDataframe(cdataframe, num_columns);
    print_CDataframe_limited_raw(cdataframe, num_columns);
    print_CDataframe_limited_columns(cdataframe, num_columns);
    // Libérer la mémoire allouée pour chaque colonne
    for (int i = 0; i < num_columns; i++) {
        free(cdataframe[i]->data);
        free(cdataframe[i]);
    }
    // Libérer le tableau de pointeurs de colonnes
    free(cdataframe);

    return 0;
}

