//
// Created by Victor Li Yim on 28/03/2024.
//
#include<stdio.h>
#include "functions.h"


int main() {
    // Créer un CDataframe vide avec 3 colonnes
    CDataframe* dataframe = create_dataframe(3);

    // Ajouter des colonnes au dataframe
    add_column(dataframe, "Column 1");
    add_column(dataframe, "Column 2");
    add_column(dataframe, "Column 3");

    // Remplir le dataframe à partir de saisies utilisateur
    read_Dataframe(dataframe);

    // Afficher les données du dataframe
    for (int i = 0; i < dataframe->num_columns; i++) {
        printf("Column %d:\n", i);
        print_col(dataframe->columns[i]);
    }

    // Libérer la mémoire allouée pour le dataframe
    delete_dataframe(&dataframe);

    return 0;
}
