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
        printf("Entrez le titre de la colonne %d: ", i + 1);
        scanf("%s", title);
        // Créer une nouvelle colonne avec le titre donné
        cdataframe->columns[i] = create_column(title);
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
        printf("Entrez les valeurs de la colonne %d:\n", i + 1);
        for (int j = 0; j < nb_value; j++) {
            int value;
            printf("Entrez la valeur de la ligne %d: ", j + 1);
            scanf("%d", &value);
            insert_value(cdataframe->columns[i], value);
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
            insert_value(dataframe->columns[i], data[i][j]);
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
                printf("[%d] %d\n", j, cdataframe->columns[i]->data[j]);
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
            printf("[%d] %d\n", j, cdataframe->columns[i]->data[j]);
        }
    }
}

void add_raw(CDataframe* cdataframe){
    for(int i = 0; i<cdataframe->num_columns; i++){
        int val;
        printf("Entrez la valeur à ajouter pour la colonne %s : ", cdataframe->columns[i]->name);
        scanf("%d", &val);
        insert_value(cdataframe->columns[i], val);
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
            // Supprimer la valeur à l'index spécifié
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
    int nb_val;
    printf("Entrez le titre de la colonne %d: ", cdataframe->num_columns + 1);
    scanf("%49s", title);
    // Créer une nouvelle colonne avec le titre donné
    COLUMN* column = create_column(title);
    if (column == NULL) {
        printf("ERREUR: Échec de création de colonne\n");
        exit(EXIT_FAILURE);
    }
    printf("Entrez le nombre de valeurs à insérer dans la colonne : ");
    scanf("%d", &nb_val);
    for (int j = 0; j < nb_val; j++) {
        int val;
        printf("Entrez la valeur pour la ligne %d: ", j + 1);
        scanf("%d", &val);
        insert_value(column, val);
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

int verify(CDataframe* cdataframe, int val){
    for(int i = 0; i<cdataframe->num_columns; i++){
        for(int j = 0; j<cdataframe->columns[i]->TL; j++){
            if(cdataframe->columns[i]->data[j] == val){
                return 1;
            }
        }
    }
    return 0;
}
void search(CDataframe* cdataframe){
    int option;
    do {
        printf("Que voulez-vous faire entre : \n -0 acceder\n -1 modifier \n");
        scanf("%d", &option);
    }while(option < 0 || option > 1);
    int num_raw, num_col;
    printf("Entrez l'indice de la colonne et de la ligne : ");
    scanf("%d %d", &num_col, &num_raw);
    printf("\n");
    if(option == 0){
        printf("La valeur que vous cherchez à la colonne %d ligne %d est %d\n", num_col, num_raw, cdataframe->columns[num_col]->data[num_raw]);
    }
    else{
        int new_val;
        printf("Saisissez la nouvelle valeur : ");
        scanf("%d", &new_val);
        cdataframe->columns[num_col]->data[num_raw]= new_val;
        printf("Modification effectuée");
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
        printf("Nombre de ligne de la colonne %s : %d", cdataframe->columns[i]->name, cdataframe->columns[i]->TL);
    }
}

void print_num_col(CDataframe* cdataframe){
    if(cdataframe == NULL){
        printf("ERREUR");
        exit(EXIT_FAILURE);
    }
    printf("Il y a %d colonnes.", cdataframe->num_columns);
}

int research_cel_equal(CDataframe* cdataframe, int x){
    int count = 0;
    if(cdataframe == NULL){
        printf("ERREUR");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i<cdataframe->num_columns; i++){
        count += research_equal(cdataframe->columns[i], x);
    }
    return count;
}

int research_cel_sup(CDataframe* cdataframe, int x){
    int count = 0;
    if(cdataframe == NULL){
        printf("ERREUR");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i<cdataframe->num_columns; i++){
        count += research_sup(cdataframe->columns[i], x);

    }
    return count;
}

int research_cel_inf(CDataframe* cdataframe, int x){
    int count = 0;
    if(cdataframe == NULL){
        printf("ERREUR");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i<cdataframe->num_columns; i++){
        count += research_inf(cdataframe->columns[i], x);
    }
    return count;
}