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
        int type;
        do {
            printf("Saisissez le type que vous souhaitez utiliser pour la colonne %d:\n"
                   "-1 UINT\n"
                   "-2 INT\n"
                   "-3 CHAR\n"
                   "-4 FLOAT\n"
                   "-5 DOUBLE\n"
                   "-6 STRING\n", i+1);
            scanf("%d", &type);
        }while(type<1 || type>6);
        printf("Entrez le titre de la colonne %d: ", i + 1);
        scanf("%s", title);
        switch(type){
            case 1:
                cdataframe->columns[i] = create_column(UINT ,title);
                break;
            case 2:
                cdataframe->columns[i] = create_column(INT ,title);
                break;
            case 3:
                cdataframe->columns[i] = create_column(CHAR ,title);
                break;
            case 4:
                cdataframe->columns[i] = create_column(FLOAT ,title);
                break;
            case 5:
                cdataframe->columns[i] = create_column(DOUBLE ,title);
                break;
            case 6:
                cdataframe->columns[i] = create_column(STRING ,title);
                break;
            default:
                printf("Format inconnu");
                break;
        }
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
        printf("Colonne %d:\n", i + 1);
        int nb_value;
        printf("Entrez le nombre de valeurs de la colonnes %d: ", i + 1);
        scanf("%d", &nb_value);
        printf("Remplissage de la colonne %s\n", cdataframe->columns[i]->name);
        for(int j = 0; j<nb_value; j++) {
            switch(cdataframe->columns[i]->type){
                case UINT:{
                    unsigned int value;
                    printf("Entrez la valeur de la ligne %d\n", j+1);
                    scanf("%u", &value);
                    insert_value(cdataframe->columns[i], &value);
                    break;
                }
                case INT:{
                    int value;
                    printf("Entrez l'entier de la ligne %d\n", j+1);
                    scanf("%d", &value);
                    insert_value(cdataframe->columns[i], &value);
                    break;
                }
                case CHAR:{
                    char value;
                    printf("Entrez le caractère de la ligne %d\n", j+1);
                    scanf(" %c", &value);
                    insert_value(cdataframe->columns[i], &value);
                    break;
                }
                case FLOAT:{
                    float value;
                    printf("Entrez le flottant de la ligne %d\n", j+1);
                    scanf("%f", &value);
                    insert_value(cdataframe->columns[i], &value);
                    break;
                }
                case DOUBLE:{
                    double value;
                    printf("Entrez le flottant de la ligne %d\n", j+1);
                    scanf("%lf", &value);
                    insert_value(cdataframe->columns[i], &value);
                    break;
                }
                case STRING:{
                    char value[50];
                    printf("Entrez la chaine de caractère de la ligne %d\n", j+1);
                    scanf("%s", value);
                    insert_value(cdataframe->columns[i], value);
                    break;
                }
            }
        }
    }
}

void read_cdataframe_hardway(CDataframe* dataframe) {
    if (dataframe == NULL) {
        printf("ERREUR\n");
        exit(EXIT_FAILURE);
    }

    // Exemple de données prédéfinies pour chaque colonne
    int data[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    for (int i = 0; i < dataframe->num_columns; i++) {
        for (int j = 0; j < 3; j++) {
            insert_value(dataframe->columns[i], &data[i][j]);
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
        printf("Colonne %d (%s):\n", i + 1, cdataframe->columns[i]->name);
        printf("Valeur:\n");
        for(j = 0; j<limit; j++){
            if(cdataframe->columns[i]->data[j]!=NULL) {
                char str[256];
                convert_value(cdataframe->columns[i], j, str, sizeof(str));
                printf("[%d] %s\n", j, str);
            }
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
        printf("Colonne %d (%s):\n", i + 1, cdataframe->columns[i]->name);
        printf("Valeurs:\n");
        for(j = 0; j<cdataframe->columns[i]->TL; j++){
            char str[256];
            convert_value(cdataframe->columns[i], j, str, sizeof(str));
            printf("[%d] %s\n", j, str);
        }
    }
}

void add_raw(CDataframe* cdataframe) {
    for (int i = 0; i < cdataframe->num_columns; i++) {
        switch (cdataframe->columns[i]->type) {
            case UINT: {
                unsigned int value;
                printf("Entrez la valeur de la colonne : %s\n", cdataframe->columns[i]->name);
                scanf("%u", &value);
                insert_value(cdataframe->columns[i], &value);
                break;
            }
            case INT: {
                int value;
                printf("Entrez l'entier de la colonne : %s\n", cdataframe->columns[i]->name);
                scanf("%d", &value);
                insert_value(cdataframe->columns[i], &value);
                break;
            }
            case CHAR: {
                char value;
                printf("Entrez le caractère de la colonne : %s\n", cdataframe->columns[i]->name);
                scanf(" %c", &value);
                insert_value(cdataframe->columns[i], &value);
                break;
            }
            case FLOAT: {
                float value;
                printf("Entrez le flottant de la colonne : %s\n", cdataframe->columns[i]->name);
                scanf("%f", &value);
                insert_value(cdataframe->columns[i], &value);
                break;
            }
            case DOUBLE: {
                double value;
                printf("Entrez le flottant de la colonne : %s\n", cdataframe->columns[i]->name);
                scanf("%lf", &value);
                insert_value(cdataframe->columns[i], &value);
                break;
            }
            case STRING: {
                char value[50];
                printf("Entrez la chaine de caractère de la colonne : %s\n", cdataframe->columns[i]->name);
                scanf("%s", value);
                insert_value(cdataframe->columns[i], value);
                break;
            }
        }
    }
}

void delete_raw(CDataframe* cdataframe) {
    int index;
    do {
        printf("Entrez l'indice de la ligne à supprimer : ");
        scanf("%d", &index);
    } while (index < 0);

    // Supprimer la ligne de chaque colonne
    for (int i = 0; i < cdataframe->num_columns; i++) {
        if (index < cdataframe->columns[i]->TL) {
            for (int j = index; j < cdataframe->columns[i]->TL - 1; j++) {
                cdataframe->columns[i]->data[j] = cdataframe->columns[i]->data[j + 1];
            }
            cdataframe->columns[i]->TL--;
        }
    }
}


void add_column(CDataframe* cdataframe) {
    if (cdataframe == NULL) {
        printf("ERREUR: CDataframe NULL\n");
        exit(EXIT_FAILURE);
    }
    char title[50];
    int type;
    do {
        printf("Saisissez le type que vous souhaitez utiliser pour cette nouvelle colonne :\n"
               "-1 UINT\n"
               "-2 INT\n"
               "-3 CHAR\n"
               "-4 FLOAT\n"
               "-5 DOUBLE\n"
               "-6 STRING\n");
        scanf("%d", &type);
    }while(type<1 || type>6);
    printf("Entrez le titre de la colonne %d: ", cdataframe->num_columns + 1);
    scanf("%49s", title);
    COLUMN* column;
    switch(type){
        case 1:
            column = create_column(UINT,title);
            break;
        case 2:
            column = create_column(INT ,title);
            break;
        case 3:
            column = create_column(CHAR ,title);
            break;
        case 4:
            column = create_column(FLOAT ,title);
            break;
        case 5:
            column = create_column(DOUBLE ,title);
            break;
        case 6:
            column = create_column(STRING ,title);
            break;
        default:
            printf("Format inconnu");
            break;
    }
    if (column == NULL) {
        printf("ERREUR: Échec de création de colonne\n");
        exit(EXIT_FAILURE);
    }
    int nb_value;
    printf("Entrez le nombre de valeurs de la colonnes : ");
    scanf("%d", &nb_value);
    printf("Remplissage de la colonne : \n");
    for(int j = 0; j<nb_value; j++) {
        switch (column->type) {
            case UINT: {
                unsigned int value;
                printf("Entrez la valeur de la ligne %d\n", j + 1);
                scanf("%u", &value);
                insert_value(column, &value);
                break;
            }
            case INT: {
                int value;
                printf("Entrez l'entier de la ligne %d\n", j + 1);
                scanf("%d", &value);
                insert_value(column, &value);
                break;
            }
            case CHAR: {
                char value;
                printf("Entrez le caractère de la ligne %d\n", j + 1);
                scanf(" %c", &value);
                insert_value(column, &value);
                break;
            }
            case FLOAT: {
                float value;
                printf("Entrez le flottant de la ligne %d\n", j + 1);
                scanf("%f", &value);
                insert_value(column, &value);
                break;
            }
            case DOUBLE: {
                double value;
                printf("Entrez le flottant de la ligne %d\n", j + 1);
                scanf("%lf", &value);
                insert_value(column, &value);
                break;
            }
            case STRING: {
                char value[50];
                printf("Entrez la chaine de caractère de la ligne %d\n", j + 1);
                scanf("%s", value);
                insert_value(column, value);
                break;
            }
        }
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

void delete_columncdf(CDataframe* cdataframe) {
    int index;
    do {
        printf("Entrez l'indice de la colonne à supprimer : ");
        scanf("%d", &index);
    } while (index < 0);
    if (cdataframe == NULL || index < 0) {
        printf("ERREUR\n");
        exit(EXIT_FAILURE);
    }
    else if(index >= cdataframe->num_columns){
        printf("Il n'y a pas de colonne à cet indice fin de l'exécution");
        exit(EXIT_FAILURE);
    }

    // Libérer la mémoire allouée pour la colonne à l'index spécifié
    delete_column(&(cdataframe->columns[index]));
    // Décaler les colonnes restantes vers la gauche pour remplir l'espace laissé par la suppression
    for (int i = index; i < cdataframe->num_columns - 1; i++) {
        cdataframe->columns[i] = cdataframe->columns[i + 1];
    }
    // Réduire le nombre de colonnes dans le dataframe
    cdataframe->num_columns--;
}

void rename_title(CDataframe* cdataframe){
    int index;
    do {
        printf("Entrez l'indice de la colonne à modifier : ");
        scanf("%d", &index);
    } while (index < 0);
    if(index >= cdataframe->num_columns){
        printf("Il n'y a pas de colonne à cet indice fin de l'exécution");
        exit(EXIT_FAILURE);
    }
    free(cdataframe->columns[index]->name);
    char title[50];
    printf("Entrez le nouveau titre de la colonne %d: ", index);
    scanf("%49s", title);
    cdataframe->columns[index]->name = strdup(title);
    if (cdataframe->columns[index]->name == NULL) {
        printf("ERREUR\n");
        exit(EXIT_FAILURE);
    }
}

int search_value(CDataframe *dataframe, void *value, ENUM_TYPE type) {
    if (dataframe == NULL || value == NULL) {
        printf("ERREUR : Paramètre non valide.\n");
        return 0;
    }

    for (int i = 0; i < dataframe->num_columns; i++) {
        COLUMN *col = dataframe->columns[i];
        if (col->type != type) {
            continue; // On passe les colonnes qui ont un type différent de ce que l'on recherche
        }

        for (unsigned int j = 0; j < col->TL; j++) {
            switch (type) {
                case UINT:
                    if (col->data[j]->uint_value == *(unsigned int *)value) {
                        return 1;
                    }
                    break;
                case INT:
                    if (col->data[j]->int_value == *(int *)value) {
                        return 1;
                    }
                    break;
                case CHAR:
                    if (col->data[j]->char_value == *(char *)value) {
                        return 1;
                    }
                    break;
                case FLOAT:
                    if (col->data[j]->float_value == *(float *)value) {
                        return 1;
                    }
                    break;
                case DOUBLE:
                    if (col->data[j]->double_value == *(double *)value) {
                        return 1;
                    }
                    break;
                case STRING:
                    if (strcmp(col->data[j]->string_value, (char *)value) == 0) {
                        return 1;
                    }
                    break;
                case STRUCTURE:
                    // Comparaison des structures - dépend de la structure spécifique
                    if (col->data[j]->struct_value == value) {
                        return 1;
                    }
                    break;
                default:
                    printf("Type de colonne non pris en charge.\n");
                    return 0;
            }
        }
    }
    return 0;
}

void search(CDataframe* cdataframe) {
    if (cdataframe == NULL) {
        printf("ERREUR");
        exit(EXIT_FAILURE);
    }

    int option;
    do {
        printf("Que voulez-vous faire ? \n"
               "-0 accéder\n "
               "-1 modifier \n");
        scanf("%d", &option);
    } while (option < 0 || option > 1);

    int num_raw, num_col;
    printf("Entrez l'indice de la colonne et de la ligne sous la forme [colonne ligne]: ");
    scanf("[%d %d]", &num_col, &num_raw);
    printf("\n");

    if (num_col >= cdataframe->num_columns || num_raw >= cdataframe->columns[num_col]->TL) {
        printf("ERREUR : Indice de colonne ou de ligne non valide.\n");
        return;
    }

    COLUMN *col = cdataframe->columns[num_col];

    if (option == 0) { // Accéder à la valeur
        switch (col->type) {
            case UINT:
                printf("La valeur que vous cherchez à la colonne %d ligne %d est %u\n", num_col, num_raw,
                       *(unsigned int *) col->data[num_raw]);
                break;
            case INT:
                printf("La valeur que vous cherchez à la colonne %d ligne %d est %d\n", num_col, num_raw,
                       *(int *) col->data[num_raw]);
                break;
            case CHAR:
                printf("La valeur que vous cherchez à la colonne %d ligne %d est %c\n", num_col, num_raw,
                       *(char *) col->data[num_raw]);
                break;
            case FLOAT:
                printf("La valeur que vous cherchez à la colonne %d ligne %d est %f\n", num_col, num_raw,
                       *(float *) col->data[num_raw]);
                break;
            case DOUBLE:
                printf("La valeur que vous cherchez à la colonne %d ligne %d est %lf\n", num_col, num_raw,
                       *(double *) col->data[num_raw]);
                break;
            case STRING:
                printf("La valeur que vous cherchez à la colonne %d ligne %d est %s\n", num_col, num_raw,
                       col->data[num_raw]->string_value);
                break;
            default:
                printf("Type invalide\n");
                break;
        }
    } else { // Modifier la valeur
        void *new_val;
        switch (col->type) {
            case UINT: {
                unsigned int uint_val;
                printf("Saisissez la nouvelle valeur (unsigned int) : ");
                scanf("%u", &uint_val);
                *(unsigned int *) col->data[num_raw] = uint_val;
                break;
            }
            case INT: {
                int int_val;
                printf("Saisissez la nouvelle valeur (int) : ");
                scanf("%d", &int_val);
                *(int *) col->data[num_raw] = int_val;
                break;
            }
            case CHAR: {
                char char_val;
                printf("Saisissez la nouvelle valeur (char) : ");
                scanf(" %c", &char_val);
                *(char *) col->data[num_raw] = char_val;
                break;
            }
            case FLOAT: {
                float float_val;
                printf("Saisissez la nouvelle valeur (float) : ");
                scanf("%f", &float_val);
                *(float *) col->data[num_raw] = float_val;
                break;
            }
            case DOUBLE: {
                double double_val;
                printf("Saisissez la nouvelle valeur (double) : ");
                scanf("%lf", &double_val);
                *(double *) col->data[num_raw] = double_val;
                break;
            }
            case STRING: {
                char str_val[256];
                printf("Saisissez la nouvelle valeur (string) : ");
                scanf("%s", str_val);
                free(col->data[num_raw]->string_value); // On libère l'espace alloué par l'ancienne valeur
                col->data[num_raw]->string_value = strdup(str_val); // Changement
                break;
            }
            default:
                printf("Type invalide\n");
                return;
        }
        printf("Modification effectuée.\n");
    }
}

void print_name(CDataframe* cdataframe){
    for(int i = 0; i<cdataframe->num_columns; i++){
        printf("Titre de la colonne %d : %s\n", i+1,cdataframe->columns[i]->name);
    }
}

void print_num_raw(CDataframe* cdataframe){
    if(cdataframe == NULL){
        printf("ERREUR");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i<cdataframe->num_columns; i++){
        printf("Nombre de ligne de la colonne %s : %d\n", cdataframe->columns[i]->name, cdataframe->columns[i]->TL);
    }
}

void print_num_col(CDataframe* cdataframe){
    if(cdataframe == NULL){
        printf("ERREUR");
        exit(EXIT_FAILURE);
    }
    printf("Il y a %d colonnes.", cdataframe->num_columns);
}

int research_cel_equal(CDataframe* df, void* value, ENUM_TYPE type) {
    int count = 0;
    for (int col_idx = 0; col_idx < df->num_columns; col_idx++) {
        COLUMN* col = df->columns[col_idx];
        count += research_equal(col, value);
    }
    return count;
}

int research_cel_sup(CDataframe* df, void* value, ENUM_TYPE type) {
    int count = 0;
    for (int col_idx = 0; col_idx < df->num_columns; col_idx++) {
        COLUMN* col = df->columns[col_idx];
        count += research_sup(col, value);
    }
    return count;
}

int research_cel_inf(CDataframe* df, void* value, ENUM_TYPE type) {
    int count = 0;
    for (int col_idx = 0; col_idx < df->num_columns; col_idx++) {
        COLUMN* col = df->columns[col_idx];
        count += research_inf(col, value);
    }
    return count;
}