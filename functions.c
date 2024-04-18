#include "functions.h"
#include <stdlib.h>
#include <stdio.h>


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
int nb_occurrences(COLUMN* col, int x){ //Retourner le nombre de d’occurrences d’une valeur x (x donné en paramètre).
    int i, count = 0;
    for(i=0; i<col->TL; i++){
        if(col->data[i]==x){
            count++;
        }
    }
    return count;
}
int search_val(COLUMN* col, int x){ //Retourner la valeur présente à la position x (x donné en paramètre).
    return col->data[x];
}

int research_sup(COLUMN* col, int x){ // Retourner le nombre de valeurs qui sont supérieures à x (x donné en paramètre).
    int i, count = 0;
    for(i=0; i<col->TL; i++){
        if(col->data[i]>x){
            count++;
        }
    }
    return count;
}
int research_inf(COLUMN* col, int x){ //Retourner le nombre de valeurs qui sont inférieures à x (x donné en paramètre).
    int i, count = 0;
    for(i=0; i<col->TL; i++){
        if(col->data[i]<x){
            count++;
        }
    }
    return count;
}
int research_equal(COLUMN* col, int x){ //Retourner le nombre de valeurs qui sont égales à x (x donné en paramètre).
    int i, count = 0;
    for(i=0; i<col->TL; i++){
        if(col->data[i]==x){
            count++;
        }
    }
    return count;
}

// Fonction pour créer un CDataframe vide
CDataframe* create_dataframe(int num_columns) {
    CDataframe* cdataframe = (CDataframe*) malloc(sizeof(CDataframe));
    if (cdataframe == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    cdataframe->columns = (COLUMN**)malloc(num_columns * sizeof(COLUMN*));
    if (cdataframe->columns == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    cdataframe->num_columns = num_columns;
    for (int i = 0; i < num_columns; i++) {
        cdataframe->columns[i] = NULL;
    }
    return cdataframe;
}

// Fonction pour ajouter une colonne à un CDataframe
int add_column(CDataframe* cdataframe, char* title) {
    if (cdataframe == NULL) {
        return 0;
    }
    COLUMN* new_column = create_column(title);
    int num_columns = cdataframe->num_columns;
    COLUMN** temp = (COLUMN**)realloc(cdataframe->columns, (num_columns + 1) * sizeof(COLUMN*));
    if (temp == NULL) {
        printf("Memory reallocation failed\n");
        delete_column(&new_column);
        return 0;
    }
    cdataframe->columns = temp;
    cdataframe->columns[num_columns] = new_column;
    cdataframe->num_columns++;
    return 1;
}

// Fonction pour remplir un CDataframe à partir de saisies utilisateur
void read_CDataframe(CDataframe* cdataframe) {
    if (cdataframe == NULL) {
        printf("Dataframe is NULL\n");
        return;
    }
    for (int i = 0; i < cdataframe->num_columns; i++) {
        printf("Colonne %d\n", i);
        int value;
        do {
            printf("Enter value (or -1 to stop): ");
            scanf("%d", &value);
            if (value != -1) {
                insert_value(cdataframe->columns[i], value);
            }
        } while (value != -1);
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

