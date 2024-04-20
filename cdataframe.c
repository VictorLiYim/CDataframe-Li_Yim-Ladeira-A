//
// Created by Victor Li Yim on 19/04/2024.
//
// Fonction pour créer un CDataframe vide
#include "cdataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

COLUMN** create_CDataframe(int num_columns) {
    // Allouer de la mémoire pour le tableau de pointeurs de colonnes
    COLUMN** cdataframe = malloc(num_columns * sizeof(COLUMN*));
    if (cdataframe == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Saisir le nom de chaque colonne
    char title[50];
    for (int i = 0; i < num_columns; i++) {
        printf("Entrez le titre de la colonne %d: ", i + 1);
        scanf("%s", title);
        // Créer une nouvelle colonne avec le titre donné
        cdataframe[i] = create_column(strdup(title));
    }

    return cdataframe;
}

// Fonction pour lire les valeurs des colonnes
void read_CDataframe(COLUMN** columns, int num_columns) {
    if (columns == NULL) {
        printf("Invalid dataframe\n");
        return;
    }
    for (int i = 0; i < num_columns; i++) {
        printf("Column %d:\n", i + 1);
        int nb_value;
        printf("Enter the number of values for column %d: ", i + 1);
        scanf("%d", &nb_value);
        printf("Enter values for column %d:\n", i + 1);
        for (int j = 0; j < nb_value; j++) {
            int value;
            printf("Enter value for row %d: ", j + 1);
            scanf("%d", &value);
            insert_value(columns[i], value);
        }
    }
}

void read_CDataframe_hardway(COLUMN** cdataframe, int num_columns) {
    // Exemple de données prédéfinies pour chaque colonne
    int data[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    for (int i = 0; i < num_columns; i++) {
        for (int j = 0; j < 3; j++) {
            insert_value(cdataframe[i], data[i][j]);
        }
    }
}

void print_CDataframe(COLUMN** columns, int num_columns) {
    if (columns == NULL) {
        printf("Invalid dataframe\n");
        return;
    }

    // Parcours de chaque colonne
    for (int i = 0; i < num_columns; i++) {
        printf("Column %d (%s):\n", i + 1, columns[i]->name);
        printf("Values:\n");

        // Affichage des valeurs de la colonne
        print_col(columns[i]);
        printf("\n");
    }
}

void print_CDataframe_limited_raw(COLUMN** cdataframe, int num_columns){
    int i,j, limit;
    printf("Combien de lignes voulez vous afficher : ");
    scanf("%d", &limit);
    for(i = 0; i<num_columns; i++){
        printf("Column %d (%s):\n", i + 1, cdataframe[i]->name);
        printf("Values:\n");
        for(j = 0; j<limit; j++){
            printf("[%d] %d\n", j, cdataframe[i]->data[j]);
        }
    }
}

void print_CDataframe_limited_columns(COLUMN** cdataframe, int num_columns){
    int i,j, limit;
    do {
        printf("Combien de colonnes souhaitez-vous afficher : ");
        scanf("%d", &limit);
    }while(limit>num_columns);
    for(i = 0; i<limit; i++){
        printf("Column %d (%s):\n", i + 1, cdataframe[i]->name);
        printf("Values:\n");
        for(j = 0; j<cdataframe[i]->TL; j++){
            printf("[%d] %d\n", j, cdataframe[i]->data[j]);
        }
    }
}