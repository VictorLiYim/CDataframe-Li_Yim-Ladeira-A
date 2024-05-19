#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"
/*
void menu(){
    int continuer = 1, option, num_columns, choix;
    while(continuer){
        printf("Création d'un CDataframe : \n");
        printf("Entrez le nombre de colonnes que vous souhaitez afficher: ");
        scanf("%d", &num_columns);
        CDataframe* cdataframe = create_CDataframe(num_columns); //création de colonnes tout en les nommant
        printf("Remplissage des colonnes : \n");
        read_CDataframe(cdataframe);
        while(option != 6){
            printf("Saisissez l'opération que vous souhaitez faire : \n"
                   "1- Ajouter (colonnes / lignes)\n"
                   "2- Supprimer (colonnes / lignes)\n"
                   "3- Afficher\n"
                   "4- Modifier\n"
                   "5- Analyser (recherche de valeurs ou d'occurrences)\n"
                   "6- Quitter\n");
            scanf("%d", &option);
            switch(option){
                case 1:
                    do {
                        printf("Que souhaitez-vous ajouter : \n"
                               "-1 Colonne\n"
                               "-2 Ligne\n");
                        scanf("%d", &choix);
                    }while(choix < 1 && choix > 2);
                    if(choix ==  1){
                        add_column(cdataframe);
                    }
                    else if(choix == 2){
                        add_raw(cdataframe);
                    }
                    break;
                case 2:
                    do {
                        printf("Que souhaitez-vous supprimer : \n"
                               "-1 Colonne\n"
                               "-2 Ligne\n");
                        scanf("%d", &choix);
                    }while(choix < 1 && choix > 2);
                    if(choix ==  1){
                        delete_columncdf(cdataframe);
                    }
                    else if(choix == 2){
                        delete_raw(cdataframe);
                    }
                    break;
                case 3:
                    do {
                        printf("Que souhaitez-vous afficher : \n"
                               "-1 Colonnes\n"
                               "-2 Lignes\n"
                               "-3 CDataframe complet\n"
                               "-4 Noms des colonnes\n"
                               "-5 Le nombre de lignes\n"
                               "-6 Le nombre de colonnes\n");
                        scanf("%d", &choix);
                    }while(choix < 1 && choix > 6);
                    if(choix ==  1){
                        print_CDataframe_limited_columns(cdataframe);
                    }
                    else if(choix == 2){
                        print_CDataframe_limited_raw(cdataframe);
                    }
                    else if(choix == 3){
                        print_CDataframe(cdataframe);
                    }
                    else if(choix == 4){
                        print_name(cdataframe);
                    }
                    else if(choix == 5){
                        print_num_raw(cdataframe);
                    }
                    else if(choix == 6){
                        print_num_col(cdataframe);
                    }
                    break;
                case 4:
                    do {
                        printf("Que souhaitez-vous modifier : \n"
                               "-1 une valeur spécifique\n"
                               "-2 le titre d'une colonne\n");
                        scanf("%d", &choix);

                    }while(choix < 1 && choix > 2);
                    if(choix == 1){

                        search(cdataframe, value, type);
                    }
                    else if(choix == 2){
                        rename_title(cdataframe);
                    }
                    break;
                case 5:
                    do {
                        printf("\nQue Recherchez-vous : \n"
                               "-1 Nombre de valeurs égale\n"
                               "-2 Nombre de valeurs supérieures\n"
                               "-3 Nombre de valeurs inférieures\n"
                               "-4 Vérifier l'existence d'une valeur\n");
                        scanf("%d", &choix);
                    }while(choix < 1 && choix > 4);
                    int x;
                    printf("Entrez la valeur que vous cherchez : ");
                    scanf("%d", &x);
                    if(choix == 1){
                        research_cel_equal(cdataframe, x);
                    }
                    else if(choix == 2){
                        research_cel_sup(cdataframe, x);
                    }
                    else if(choix ==  3){
                        research_cel_inf(cdataframe, x);
                    }
                    else if(choix == 4){
                        int verif = verify(cdataframe, x);
                        if(verif){
                            printf("La valeur %d que vous recherchez existe", x);
                        }
                        else{
                            printf("%d n'existe pas", x);
                        }
                    }
                    break;
                case 6:
                    printf("fin");
                    break;
                default:
                    printf("Vous n'avez pas sélectionné la bonne option\n");
            }
        }
        continuer = 0;
        for (int i = 0; i < cdataframe->num_columns; i++) {
            free(cdataframe->columns[i]->data);
            free(cdataframe->columns[i]->name);
            free(cdataframe->columns[i]);
        }
        free(cdataframe->columns);
        free(cdataframe);
    }
}*/