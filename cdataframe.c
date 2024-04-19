//
// Created by Victor Li Yim on 19/04/2024.
//
// Fonction pour créer un CDataframe vide
#include "cdataframe.h"
#include <stdio.h>
#include <stdlib.h>

CDataframe* create_dataframe(int num_columns) {
    CDataframe* cdataframe = (CDataframe*) malloc(sizeof(CDataframe));
    if (cdataframe == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Allouer de la mémoire pour le tableau de pointeurs de colonnes
    cdataframe->columns = (COLUMN**) malloc(num_columns * sizeof(COLUMN*));
    if (cdataframe->columns == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialiser les pointeurs de colonnes à NULL
    for (int i = 0; i < num_columns; i++) {
        cdataframe->columns[i] = NULL;
    }

    cdataframe->num_columns = num_columns;
    return cdataframe;
}


// Fonction pour ajouter une colonne à un CDataframe
void add_column(CDataframe* cdataframe, COLUMN* column) {
    if (cdataframe == NULL || column == NULL) {
        printf("Invalid dataframe or column\n");
        return;
    }

    // Réallouer de la mémoire pour le tableau de pointeurs de colonnes
    cdataframe->columns = realloc(cdataframe->columns, (cdataframe->num_columns + 1) * sizeof(COLUMN*));
    if (cdataframe->columns == NULL) {
        printf("Failed to reallocate memory for columns\n");
        return;
    }

    // Ajouter la nouvelle colonne à la fin du tableau
    cdataframe->columns[cdataframe->num_columns] = column;
    cdataframe->num_columns++;
}




// Fonction pour remplir un CDataframe à partir de saisies utilisateur
void read_CDataframe(CDataframe* cdataframe) {
    if (cdataframe == NULL) {
        printf("Dataframe is NULL\n");
        return;
    }
    // Boucle pour créer les colonnes
    printf("%d", cdataframe->num_columns);
    for(int i = 0; i < cdataframe->num_columns; i++) {
        char title[50];
        printf("Enter the title for column %d: ", i + 1);
        scanf("%49s", title);
        // Ajouter la colonne au CDataframe
        COLUMN* mycol = create_column(title);
        add_column(cdataframe, mycol);
        printf("%d %d\n", i, cdataframe->num_columns);
    }

    // Boucle pour remplir les colonnes avec les valeurs
    for (int i = 0; i < cdataframe->num_columns; i++) {
        int nb_value;
        printf("Enter the number of values for column %d: ", i + 1);
        scanf("%d", &nb_value);
        printf("Enter values for column %d:\n", i + 1);
        for (int j = 0; j < nb_value; j++) {
            int value;
            printf("Enter value %d: ", j + 1);
            scanf("%d", &value);
            insert_value(cdataframe->columns[i], value);
        }
    }
}



// Fonction pour libérer un CDataframe
void delete_dataframe(CDataframe** cdataframe) {
    if (cdataframe == NULL || *cdataframe == NULL) {
        printf("Dataframe is NULL\n");
        return;
    }
    for (int i = 0; i < (*cdataframe)->num_columns; i++) {
        delete_column(&((*cdataframe)->columns[i]));
    }
    free((*cdataframe)->columns);
    free(*cdataframe);
    *cdataframe = NULL;
}

// Fonction pour remplir un CDataframe avec des données prédéfinies
void read_cdataframe_hardway(CDataframe* cdataframe) {
    int i, j;
    if (cdataframe == NULL) {
        printf("Erreur\n");
        return;
    }

    // Exemple de données prédéfinies pour chaque colonne
    int data[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    for (i = 0; i < cdataframe->num_columns; i++) {
        // Créer une nouvelle colonne
        COLUMN* column = create_column("Column");
        // Remplir la colonne avec les données prédéfinies
        for (j = 0; j < 3; j++) {
            if (!insert_value(column, data[i][j])) {
                printf("Failed to insert value into column\n");
                delete_column(&column); // Libérer la mémoire de la colonne en cas d'échec
                return; // Sortir de la fonction sans ajouter de colonnes si l'insertion échoue
            }
        }
        // Assigner la colonne au dataframe
        cdataframe->columns[i] = column;
    }
}

// Fonction pour afficher tout le CDataframe
void print_dataframe(CDataframe* cdataframe) {
    if (cdataframe == NULL) {
        printf("Dataframe is NULL\n");
        return;
    }
    printf("Printing CDataframe:\n");
    for (int i = 0; i < cdataframe->num_columns; i++) {
        printf("%s\n", cdataframe->columns[i]->name);
        print_col(cdataframe->columns[i]);
        printf("\n");
    }
}

#include "cdataframe.h"
