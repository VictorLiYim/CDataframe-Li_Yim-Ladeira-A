//
// Created by Victor Li Yim on 19/04/2024.
//
#include "cdataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


CDataframe* create_CDataframe(int num_columns) {
    CDataframe* cdataframe = malloc(sizeof(CDataframe));
    if (cdataframe == NULL) {
        printf("ERREUR\n");
        exit(EXIT_FAILURE);
    }

    cdataframe->columns = malloc(num_columns * sizeof(COLUMN*));
    if (cdataframe->columns == NULL) {
        printf("ERREUR\n");
        exit(EXIT_FAILURE);
    }
    // Saisir le nom de chaque colonne
    char title[50];
    for (int i = 0; i < num_columns; i++) {
        printf("Entrez le titre de la colonne %d: ", i + 1);
        scanf("%s", title);
        // Créer une nouvelle colonne avec le titre donné
        cdataframe->columns[i] = create_column(title);
    }

    cdataframe->num_columns = num_columns;
    return cdataframe;
}


void read_CDataframe(CDataframe* cdataframe) {
    if (cdataframe == NULL) {
        printf("ERREUR\n");
        return;
    }

    for (int i = 0; i < cdataframe->num_columns; i++) {
        printf("Column %d:\n", i + 1);
        int nb_value;
        printf("Enter the number of values for column %d: ", i + 1);
        scanf("%d", &nb_value);
        printf("Enter values for column %d:\n", i + 1);
        for (int j = 0; j < nb_value; j++) {
            int value;
            printf("Enter value for row %d: ", j + 1);
            scanf("%d", &value);
            insert_value(cdataframe->columns[i], value);
        }
    }
}

void read_cdataframe_hardway(CDataframe* dataframe) {
    if (dataframe == NULL) {
        printf("Dataframe is NULL\n");
        return;
    }

    // Exemple de données prédéfinies pour chaque colonne
    int data[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    for (int i = 0; i < dataframe->num_columns; i++) {
        for (int j = 0; j < 3; j++) {
            insert_value(dataframe->columns[i], data[i][j]);
        }
    }
}

void print_CDataframe(CDataframe* cdataframe) {
    if (cdataframe == NULL) {
        printf("ERREUR\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < cdataframe->num_columns; i++) {
        printf("%s:\n", cdataframe->columns[i]->name);
        print_col(cdataframe->columns[i]);
    }
}

void print_CDataframe_limited_raw(CDataframe* cdataframe){
    int i,j, limit;
    printf("Combien de lignes voulez vous afficher : ");
    scanf("%d", &limit);
    for(i = 0; i<cdataframe->num_columns; i++){
        printf("Column %d (%s):\n", i + 1, cdataframe->columns[i]->name);
        printf("Values:\n");
        for(j = 0; j<limit; j++){
            printf("[%d] %d\n", j, cdataframe->columns[i]->data[j]);
        }
    }
}

void print_CDataframe_limited_columns(CDataframe* cdataframe){
    int i,j, limit;
    do {
        printf("Combien de colonnes souhaitez-vous afficher : ");
        scanf("%d", &limit);
    }while(limit>cdataframe->num_columns);
    for(i = 0; i<limit; i++){
        printf("Column %d (%s):\n", i + 1, cdataframe->columns[i]->name);
        printf("Values:\n");
        for(j = 0; j<cdataframe->columns[i]->TL; j++){
            printf("[%d] %d\n", j, cdataframe->columns[i]->data[j]);
        }
    }

    }

void add_column(CDataframe* cdataframe) {
    if (cdataframe == NULL) {
        printf("ERREUR: CDataframe NULL\n");
        exit(EXIT_FAILURE);
    }
    char title[50];
    int nb_val;
    printf("Entrez le titre de la colonne %d: ", cdataframe->num_columns + 1);
    scanf("%49s", title);
    // Créer une nouvelle colonne avec le titre donné
    COLUMN* column = create_column(title);
    if (column == NULL) {
        printf("ERREUR: Échec de création de colonne\n");
        exit(EXIT_FAILURE);
    }
    printf("Entrez le nombre de valeurs à insérer dans la colonne : ");
    scanf("%d", &nb_val);
    for (int j = 0; j < nb_val; j++) {
        int val;
        printf("Entrez la valeur pour la ligne %d: ", j + 1);
        scanf("%d", &val);
        insert_value(column, val);
    }
    // Réallouer de la mémoire pour le tableau de pointeurs de colonnes
    cdataframe->columns = realloc(cdataframe->columns, (cdataframe->num_columns + 1) * sizeof(COLUMN*));
    if (cdataframe->columns == NULL) {
        printf("ERREUR: Échec de réallocation de mémoire pour les colonnes\n");
        exit(EXIT_FAILURE);
    }
    // Ajouter la nouvelle colonne à la fin du tableau
    cdataframe->columns[cdataframe->num_columns] = column;
    cdataframe->num_columns++;
}
