//
// Created by Victor Li Yim on 28/03/2024.
//
#include<stdio.h>
#include<stdlib.h>
#include "cdataframe.h"
#include<string.h>

int main() {
    int num_columns;
    printf("Enter the number of columns: ");
    scanf("%d", &num_columns);
    CDataframe* cdataframe = create_CDataframe(num_columns);

    // Demander à l'utilisateur de saisir les données pour chaque colonne
    read_cdataframe_hardway(cdataframe);

    // Afficher le CDataframe
    add_raw(cdataframe);
    add_column(cdataframe);
    delete_raw(cdataframe);
    delete_columncdf(cdataframe);
    print_CDataframe(cdataframe);
    rename_title(cdataframe);
    search(cdataframe);
    search(cdataframe);
    print_CDataframe(cdataframe);
    printf("%d", verify(cdataframe));
    print_name(cdataframe);

    // Libérer la mémoire allouée pour le CDataframe
    for (int i = 0; i < cdataframe->num_columns; i++) {
        delete_column(cdataframe->columns[i]);
    }
    free(cdataframe->columns);
    free(cdataframe);

    return 0;
}


