//
// Created by Victor Li Yim on 28/03/2024.
//
#include<stdio.h>
#include "functions.h"


int main() {
    // Créer un CDataframe vide avec 3 colonnes
    CDataframe* dataframe = create_dataframe(3);
    // Remplir le dataframe avec des données prédéfinies
    read_CDataframe(dataframe);
    insert_value(dataframe->columns[0], 3);
    // Afficher le dataframe
    print_dataframe(dataframe);

    // Libérer la mémoire allouée pour le dataframe
    delete_dataframe(&dataframe);


    return 0;
}
