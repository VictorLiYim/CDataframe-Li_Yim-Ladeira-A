//
// Created by Victor Li Yim on 28/03/2024.
//
#include<stdio.h>
#include<stdlib.h>
#include "cdataframe.h"
#include<string.h>

int main() {
    int num_columns;
    printf("Entrez le nombre de colonnes que vous souhaitez afficher: ");
    scanf("%d", &num_columns);
    CDataframe* cdataframe = create_CDataframe(num_columns);
    // Demande à l'utilisateur
    read_CDataframe(cdataframe);
    // Afficher le CDataframe avec utilisation de quelques
    add_raw(cdataframe);
    add_column(cdataframe);
    delete_raw(cdataframe);
    delete_columncdf(cdataframe);
    print_CDataframe(cdataframe);
    rename_title(cdataframe);
    search(cdataframe);
    search(cdataframe);
    print_CDataframe(cdataframe);
    printf("%d\n", verify(cdataframe));
    print_name(cdataframe);
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


