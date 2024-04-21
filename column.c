//
// Created by Victor Li Yim on 19/04/2024.
//
#include "column.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
COLUMN *create_column(char* title)
{
    COLUMN *col = (COLUMN*) malloc(sizeof(COLUMN)); // Allouer de la mémoire pour la colonne
    if (col == NULL) {
        printf("Erreur lors de l'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    col->TP = 0;
    col->TL = 0;
    col->name = strdup(title);
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

void delete_column(COLUMN **col) {
    if (col == NULL || *col == NULL) {
        printf("ERREUR\n");
        return;
    }
    // Libérer le tableau de données
    free((*col)->data);
    // Libérer la structure de colonne
    free(*col);
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
