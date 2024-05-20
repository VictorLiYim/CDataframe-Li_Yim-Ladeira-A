#include "menu.h"
/*
 * Ce fichier menu va permettre d'utiliser toutes les fonctions créée le cdataframe ou dans colonne
 */

void menu(){
    int continuer = 1, option, num_columns, choix;
    while (continuer) {
        printf("Création d'un CDataframe : \n");
        printf("Entrez le nombre de colonnes que vous souhaitez créer: ");
        scanf("%d", &num_columns);
        CDataframe *cdataframe = create_CDataframe(num_columns); //création de colonnes tout en les nommant
        printf("Remplissage des colonnes : \n");
        read_CDataframe(cdataframe);
        while (option != 6) {
            printf("Saisissez l'opération que vous souhaitez faire : \n"
                   "1- Ajouter (colonnes / lignes)\n"
                   "2- Supprimer (colonnes / lignes)\n"
                   "3- Afficher\n"
                   "4- Modifier(ou trier)\n"
                   "5- Analyser (recherche de valeurs ou d'occurrences)\n"
                   "6- Quitter\n");
            scanf("%d", &option);
            switch (option) {
                case 1:
                    do {
                        printf("Que souhaitez-vous ajouter : \n"
                               "-1 Colonne\n"
                               "-2 Ligne\n");
                        scanf("%d", &choix);
                    } while (choix < 1 && choix > 2);
                    if (choix == 1) {
                        add_column(cdataframe);
                    } else if (choix == 2) {
                        add_raw(cdataframe);
                    }
                    break;
                case 2:
                    do {
                        printf("Que souhaitez-vous supprimer : \n"
                               "-1 Colonne\n"
                               "-2 Ligne\n");
                        scanf("%d", &choix);
                    } while (choix < 1 && choix > 2);
                    if (choix == 1) {
                        delete_columncdf(cdataframe);
                    } else if (choix == 2) {
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
                               "-6 Le nombre de colonnes\n"
                               "-7 Le CDataframe trié\n");
                        scanf("%d", &choix);
                    } while (choix < 1 && choix > 7);
                    if (choix == 1) {
                        print_CDataframe_limited_columns(cdataframe);
                    } else if (choix == 2) {
                        print_CDataframe_limited_raw(cdataframe);
                    } else if (choix == 3) {
                        print_CDataframe(cdataframe);
                    } else if (choix == 4) {
                        print_name(cdataframe);
                    } else if (choix == 5) {
                        print_num_raw(cdataframe);
                    } else if (choix == 6) {
                        print_num_col(cdataframe);
                    } else if(choix == 7){
                        for(int i = 0; i <cdataframe->num_columns; i++) {
                            print_col_by_index(cdataframe->columns[i]);
                        }
                    }
                    break;
                case 4:
                    do {
                        printf("Que souhaitez-vous modifier : \n"
                               "-1 une valeur spécifique\n"
                               "-2 le titre d'une colonne\n"
                               "-3 Trier une colonne\n");
                        scanf("%d", &choix);

                    } while (choix < 1 && choix > 3);
                    if (choix == 1) {
                        search(cdataframe);
                    } else if (choix == 2) {
                        rename_title(cdataframe);
                    }
                    else if(choix == 3){
                        printf("Dans quel ordre voulez vous le trier\n"
                               "-1 ascendant\n"
                               "-2 descendant\n");
                        int tri;
                        scanf("%d", &tri);
                        if(tri == 1){
                            for(int j = 0; j<cdataframe->num_columns; j++){
                                sort(cdataframe->columns[j], ASC);
                            }
                        }
                        if(tri == 2){
                            for(int j = 0; j<cdataframe->num_columns; j++){
                                sort(cdataframe->columns[j], DESC);
                            }
                        }
                    }
                    break;
                case 5:
                    do {
                        printf("\nQue Recherchez-vous : \n"
                               "-1 Nombre de valeurs égale\n"
                               "-2 Nombre de valeurs supérieures\n"
                               "-3 Nombre de valeurs inférieures\n"
                               "-4 Vérifier l'existence d'une valeur\n"
                               "-5 Une valeur dans une colonne triée non fonctionnelle pour le moment\n");
                        scanf("%d", &choix);
                    } while (choix < 1 && choix > 4);
                    int type;
                    do {
                        printf("Quel type de donnée recherchez vous :\n"
                               "-1 UINT\n"
                               "-2 INT\n"
                               "-3 CHAR\n"
                               "-4 FLOAT\n"
                               "-5 DOUBLE\n"
                               "-6 STRING\n");
                        scanf("%d", &type);
                    }while(type<1 || type >6);
                    if (choix == 1) {
                        switch(type){
                            case 1: {
                                unsigned int x;
                                printf("Entrez l'entier non signé que vous cherchez :\n");
                                scanf("%u", &x);
                                printf("Il y a %d valeurs égales\n",research_cel_equal(cdataframe, &x, type + 1));
                                break;
                            }
                            case 2:{
                                int x;
                                printf("Entrez l'entier que vous cherchez :\n");
                                scanf("%d", &x);
                                printf("Il y a %d valeurs égales\n", research_cel_equal(cdataframe, &x, type + 1));
                                break;
                            }
                            case 3:{
                                char x;
                                printf("Entrez le caractère que vous cherchez :\n");
                                scanf("%c", &x);
                                printf("Il y a %d valeurs égales\n",research_cel_equal(cdataframe, &x, type + 1));
                            }
                            case 4:{
                                float x;
                                printf("Entrez le flottant que vous cherchez :\n");
                                scanf("%f", &x);
                                printf("Il y a %d valeurs égales\n",research_cel_equal(cdataframe, &x, type + 1));
                            }
                            case 5:{
                                double x;
                                printf("Entrez le double que vous cherchez :\n");
                                scanf("%lf", &x);
                                printf("Il y a %d valeurs égales\n",research_cel_equal(cdataframe, &x, type + 1));
                            }
                            case 6:{
                                char str[50];
                                printf("Entrez la chaine de caractère que vous cherchez :\n");
                                scanf("%s", str);
                                printf("Il y a %d valeurs égales\n",research_cel_equal(cdataframe, &str, type + 1));
                            }
                        }
                    } else if (choix == 2) {
                        switch(type){
                            case 1: {
                                unsigned int x;
                                printf("Entrez l'entier non signé que vous cherchez :\n");
                                scanf("%u", &x);
                                printf("Il y a %d valeurs supérieures\n",research_cel_sup(cdataframe, &x, type + 1));
                            }
                            case 2:{
                                int x;
                                printf("Entrez l'entier que vous cherchez :\n");
                                scanf("%d", &x);
                                printf("Il y a %d valeurs supérieures\n",research_cel_sup(cdataframe, &x, type + 1));
                            }
                            case 3:{
                                char x;
                                printf("Entrez le caractère que vous cherchez :\n");
                                scanf(" %c", &x);
                                printf("Il y a %d valeurs supérieures\n",research_cel_sup(cdataframe, &x, type + 1));
                            }
                            case 4:{
                                float x;
                                printf("Entrez le flottant que vous cherchez :\n");
                                scanf("%f", &x);
                                printf("Il y a %d valeurs supérieures\n",research_cel_sup(cdataframe, &x, type + 1));
                            }
                            case 5:{
                                double x;
                                printf("Entrez le double que vous cherchez :\n");
                                scanf("%lf", &x);
                                printf("Il y a %d valeurs supérieures\n",research_cel_sup(cdataframe, &x, type + 1));
                            }
                            case 6:{
                                char str[50];
                                printf("Entrez la chaine de caractère que vous cherchez :\n");
                                scanf("%s", str);
                                printf("Il y a %d valeurs supérieures\n",research_cel_sup(cdataframe, &str, type + 1));
                            }
                        }
                    } else if (choix == 3) {
                        switch(type){
                            case 1: {
                                unsigned int x;
                                printf("Entrez l'entier non signé que vous cherchez :\n");
                                scanf("%u", &x);
                                printf("Il y a %d valeurs supérieures\n",research_cel_inf(cdataframe, &x, type + 1));
                            }
                            case 2:{
                                int x;
                                printf("Entrez l'entier que vous cherchez :\n");
                                scanf("%d", &x);
                                printf("Il y a %d valeurs supérieures\n",research_cel_inf(cdataframe, &x, type + 1));
                            }
                            case 3:{
                                char x;
                                printf("Entrez le caractère que vous cherchez :\n");
                                scanf(" %c", &x);
                                printf("Il y a %d valeurs supérieures\n",research_cel_inf(cdataframe, &x, type + 1));
                            }
                            case 4:{
                                float x;
                                printf("Entrez le flottant que vous cherchez :\n");
                                scanf("%f", &x);
                                printf("Il y a %d valeurs supérieures\n",research_cel_inf(cdataframe, &x, type + 1));
                            }
                            case 5:{
                                double x;
                                printf("Entrez le double que vous cherchez :\n");
                                scanf("%lf", &x);
                                printf("Il y a %d valeurs supérieures\n",research_cel_inf(cdataframe, &x, type + 1));
                            }
                            case 6:{
                                char str[50];
                                printf("Entrez la chaine de caractère que vous cherchez :\n");
                                scanf("%s", str);
                                printf("Il y a %d valeurs supérieures\n",research_cel_inf(cdataframe, &str, type + 1));
                            }
                        }
                    } else if (choix == 4) {
                        switch(type){
                            case 1: {
                                unsigned int x;
                                printf("Entrez l'entier non signé que vous cherchez :\n");
                                scanf("%u", &x);
                                int verif = search_value(cdataframe, &x, type+1);
                                if (verif) {
                                    printf("La valeur %u que vous recherchez existe\n", x);
                                } else {
                                    printf("La valeur que vous recherchez n'existe pas.\n");
                                }
                            }
                            case 2:{
                                int x;
                                printf("Entrez l'entier que vous cherchez :\n");
                                scanf("%d", &x);
                                int verif = search_value(cdataframe, &x, type+1);
                                if (verif) {
                                    printf("La valeur %d que vous recherchez existe\n", x);
                                } else {
                                    printf("La valeur que vous recherchez n'existe pas.\n");
                                }
                            }
                            case 3:{
                                char x;
                                printf("Entrez le caractère que vous cherchez :\n");
                                scanf(" %c", &x);
                                int verif = search_value(cdataframe, &x, type+1);
                                if (verif) {
                                    printf("Le caractère %c que vous recherchez existe\n", x);
                                } else {
                                    printf("Le caractère que vous recherchez n'existe pas.\n");
                                }
                            }
                            case 4:{
                                float x;
                                printf("Entrez le flottant que vous cherchez :\n");
                                scanf("%f", &x);
                                int verif = search_value(cdataframe, &x, type+1);
                                if (verif) {
                                    printf("La valeur %.2f que vous recherchez existe\n", x);
                                } else {
                                    printf("La valeur que vous recherchez n'existe pas.\n");
                                }
                            }
                            case 5:{
                                double x;
                                printf("Entrez le double que vous cherchez :\n");
                                scanf("%lf", &x);
                                int verif = search_value(cdataframe, &x, type+1);
                                if (verif) {
                                    printf("La valeur %.2lf que vous recherchez existe\n", x);
                                } else {
                                    printf("La valeur que vous recherchez n'existe pas.\n");
                                }
                            }
                            case 6:{
                                char str[50];
                                printf("Entrez la chaine de caractère que vous cherchez :\n");
                                scanf("%s", str);
                                int verif = search_value(cdataframe, &str, type+1);
                                if (verif) {
                                    printf("La chaine de caractère [%s] que vous recherchez existe\n", str);
                                } else {
                                    printf("La chaine de cacratère que vous recherchez n'existe pas\n");
                                }
                            }
                        }
                    } else if(choix == 5){
                        switch (type) {
                            case 1: {
                                for (int i = 0; i < cdataframe->num_columns; i++) {
                                    COLUMN *col = cdataframe->columns[i];
                                    if (col->type != type) {
                                        continue; // On passe les colonnes qui ont un type différent de ce que l'on recherche
                                    }
                                    unsigned int x;
                                    printf("Entrez l'entier non signé que vous cherchez :\n");
                                    scanf("%u", &x);
                                    int verif = search_value_in_column(col, &x);
                                    if (verif) {
                                        printf("La valeur %u que vous recherchez existe\n", x);
                                    } else {
                                        printf("La valeur que vous recherchez n'existe pas.\n");
                                    }
                                }
                            }
                            case 2: {
                                for (int i = 0; i < cdataframe->num_columns; i++) {
                                    COLUMN *col = cdataframe->columns[i];
                                    if (col->type != type) {
                                        continue; // On passe les colonnes qui ont un type différent de ce que l'on recherche
                                    }
                                    int x;
                                    printf("Entrez l'entier que vous cherchez :\n");
                                    scanf("%d", &x);
                                    int verif = search_value_in_column(col, &x);
                                    if (verif) {
                                        printf("La valeur %d que vous recherchez existe\n", x);
                                    } else {
                                        printf("La valeur que vous recherchez n'existe pas.\n");
                                    }
                                }
                            }
                            case 3: {
                                for (int i = 0; i < cdataframe->num_columns; i++) {
                                    COLUMN *col = cdataframe->columns[i];
                                    if (col->type != type) {
                                        continue; // On passe les colonnes qui ont un type différent de ce que l'on recherche
                                    }
                                    char x;
                                    printf("Entrez le caractère que vous cherchez :\n");
                                    scanf("%c", &x);
                                    int verif = search_value_in_column(col, &x);
                                    if (verif) {
                                        printf("Le caractère %c que vous recherchez existe\n", x);
                                    } else {
                                        printf("Le caractère que vous recherchez n'existe pas.\n");
                                    }
                                }
                            }
                            case 4: {
                                for (int i = 0; i < cdataframe->num_columns; i++) {
                                    COLUMN *col = cdataframe->columns[i];
                                    if (col->type != type) {
                                        continue; // On passe les colonnes qui ont un type différent de ce que l'on recherche
                                    }
                                    float x;
                                    printf("Entrez le flottant que vous cherchez :\n");
                                    scanf("%f", &x);
                                    int verif = search_value_in_column(col, &x);
                                    if (verif) {
                                        printf("La valeur %.2f que vous recherchez existe\n", x);
                                    } else {
                                        printf("La valeur que vous recherchez n'existe pas.\n");
                                    }
                                }
                            }
                            case 5: {
                                for (int i = 0; i < cdataframe->num_columns; i++) {
                                    COLUMN *col = cdataframe->columns[i];
                                    if (col->type != type) {
                                        continue; // On passe les colonnes qui ont un type différent de ce que l'on recherche
                                    }
                                    double x;
                                    printf("Entrez le double que vous cherchez :\n");
                                    scanf("%ld", &x);
                                    int verif = search_value_in_column(col, &x);
                                    if (verif) {
                                        printf("La valeur %.2ld que vous recherchez existe\n", x);
                                    } else {
                                        printf("La valeur que vous recherchez n'existe pas.\n");
                                    }
                                }
                            }
                            case 6: {
                                for (int i = 0; i < cdataframe->num_columns; i++) {
                                    COLUMN *col = cdataframe->columns[i];
                                    if (col->type != type) {
                                        continue; // On passe les colonnes qui ont un type différent de ce que l'on recherche
                                    }
                                    char str[50];
                                    printf("Entrez l'entier non signé que vous cherchez :\n");
                                    scanf("%u", str);
                                    int verif = search_value_in_column(col, str);
                                    if (verif) {
                                        printf("La valeur %s que vous recherchez existe\n", str);
                                    } else {
                                        printf("La valeur que vous recherchez n'existe pas.\n");
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 6:
                    printf("Vous avez quittez le menu");
                    break;
                default:
                    printf("Vous n'avez pas sélectionné la bonne option\n");
            }
        }
        continuer = 0;
        for (int i = 0; i < cdataframe->num_columns; i++) {
            delete_column(&cdataframe->columns[i]);
        }
        free(cdataframe->columns);
    }
}