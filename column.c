#include "column.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

COLUMN *create_column(ENUM_TYPE type, char* title)
{
    /*
    * Fonction qui crée une colonne de type donné en paramètre
    */
    COLUMN *col = (COLUMN*) malloc(sizeof(COLUMN)); // Allouer de la mémoire pour la colonne
    if (col == NULL) {
        printf("Erreur lors de l'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    col->TP = 0;
    col->TL = 0;
    col->type = type;
    col->name = strdup(title);
    col->data = NULL;
    col->index = NULL;
    col->valid_index = 0; // Colonne non triée
    col->sort_dir = 0;
    return col;
}



int insert_value(COLUMN* col, void* value) {
    /*
* Fonction qui permet d'ajouter une valeur donnée en paramètre à une colonne également donnée en paramètre
*/
    if (col->TP == 0) {
        col->TP = REALLOC_SIZE;
        col->data = (COL_TYPE **) malloc(col->TP * sizeof(COL_TYPE *));
        if (col->data == NULL) {
            return 0;
        }
        col->index = (unsigned long long int *) malloc(col->TP * sizeof(unsigned long long int));
        if (col->index == NULL) {
            free(col->data);
            return 0;
        }
    } else if (col->TL >= col->TP) {
        col->TP += REALLOC_SIZE;
        COL_TYPE **new_data = (COL_TYPE **) realloc(col->data, col->TP * sizeof(COL_TYPE *));
        if (new_data == NULL) {
            return 0;
        }
        col->data = new_data;

        unsigned long long int *new_index = (unsigned long long int *) realloc(col->index, col->TP * sizeof(unsigned long long int));
        if (new_index == NULL) {
            return 0;
        }
        col->index = new_index;
    }

    col->data[col->TL] = (COL_TYPE *) malloc(sizeof(COL_TYPE));
    if (col->data[col->TL] == NULL) {
        return 0;
    }

    switch (col->type) {
        case UINT:
            col->data[col->TL]->uint_value = *(unsigned int *) value;
            break;
        case INT:
            col->data[col->TL]->int_value = *(signed int *) value;
            break;
        case CHAR:
            col->data[col->TL]->char_value = *(char *) value;
            break;
        case FLOAT:
            col->data[col->TL]->float_value = *(float *) value;
            break;
        case DOUBLE:
            col->data[col->TL]->double_value = *(double *) value;
            break;
        case STRING:
            col->data[col->TL]->string_value = (char *) malloc((strlen((char *) value) + 1) * sizeof(char));
            if (col->data[col->TL]->string_value == NULL) {
                free(col->data[col->TL]);
                return 0;
            }
            strcpy(col->data[col->TL]->string_value, (char *) value);
            break;
        case STRUCTURE:
            col->data[col->TL]->struct_value = value;
            break;
        default:
            free(col->data[col->TL]);
            return 0;
    }

    col->index[col->TL] = col->TL;
    col->TL++;
    return 1;
}

void delete_column(COLUMN **col) {
    /*
     * Fonction qui supprime une colonne donnée en paramètre
     */
    if (col == NULL || *col == NULL) {
        printf("ERREUR\n");
        exit(EXIT_FAILURE);
    }
    for (unsigned int i = 0; i < (*col)->TL; i++) {
        if ((*col)->type == STRING) {
            free((*col)->data[i]->string_value);
        }
        free((*col)->data[i]);
    }
    free((*col)->data);    // Libérer le tableau de données
    free((*col)->index);
    free((*col)->name);
    free(*col);
    *col = NULL;
}

void convert_value(COLUMN* col, unsigned long long int i, char* str, int size) {
    /*
     * Fonction converti une valeur de n'importe quel type en string
     */
    switch (col->type) {
        case INT:
            snprintf(str, size, "%d", *(int*)col->data[i]);
            break;
        case FLOAT:
            snprintf(str, size, "%f", *(float*)col->data[i]);
            break;
        case UINT:
            snprintf(str, size, "%u", *(unsigned int*)col->data[i]);
            break;
        case CHAR:
            snprintf(str, size, "%c", *(char*)col->data[i]);
            break;
        case DOUBLE:
            snprintf(str, size, "%lf", *(double*)col->data[i]);
            break;
        case STRING:
            snprintf(str, size, "%s", col->data[i]->string_value);
            break;
        default:
            snprintf(str, size, "Format inconnu");
            break;
    }
}

void print_col(COLUMN* col) {
    /*
     * Fonction qui affiche tout le contenu d'une colonne donnée en paramètre
     */
    printf("[NAME] %s\n", col->name);
    for (unsigned int i = 0; i < col->TL; i++) {
        char str[256];
        convert_value(col, i, str, sizeof(str));
        printf("[%u] %s\n", i, str);
    }
}

int nb_occurrences(COLUMN *col, void *value) {
    if (col == NULL || value == NULL) {
        printf("ERREUR\n");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    for (unsigned int i = 0; i < col->TL; i++) {
        switch (col->type) {
            case UINT:
                if (*(unsigned int*)col->data[i] == *(unsigned int *)value) {
                    count++;
                }
                break;
            case INT:
                if (*(int*)col->data[i]== *(int *)value) {
                    count++;
                }
                break;
            case CHAR:
                if (*(char*)col->data[i] == *(char *)value) {
                    count++;
                }
                break;
            case FLOAT:
                if (*(float*)col->data[i] == *(float *)value) {
                    count++;
                }
                break;
            case DOUBLE:
                if (*(double*)col->data[i] == *(double *)value) {
                    count++;
                }
                break;
            case STRING:
                if (strcmp(col->data[i]->string_value, (char *)value) == 0) {
                    count++;
                }
                break;
            default:
                printf("Type de colonne invalide.\n");
                return 0;
        }
    }

    return count;
}

COL_TYPE* search_val(COLUMN* col, int x) {
    if (x < col->TL) {
        return col->data[x];
    } else {
        return 0;
    }
}

int research_sup(COLUMN *col, void *value) {
    if (col == NULL || value == NULL) {
        printf("ERREUR\n");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    for (unsigned int i = 0; i < col->TL; i++) {
        switch (col->type) {
            case UINT:
                if (*(unsigned int*)col->data[i] > *(unsigned int *)value) {
                    count++;
                }
                break;
            case INT:
                if (*(int*)col->data[i] > *(int *)value) {
                    count++;
                }
                break;
            case CHAR:
                if (*(char*)col->data[i] > *(char *)value) {
                    count++;
                }
                break;
            case FLOAT:
                if (*(float*)col->data[i] > *(float *)value) {
                    count++;
                }
                break;
            case DOUBLE:
                if (*(double*)col->data[i] > *(double *)value) {
                    count++;
                }
                break;
            case STRING:
                if (strcmp(col->data[i]->string_value, (char *)value) > 0) {
                    count++;
                }
                break;
            default:
                printf("Type invalide\n");
                return 0;
        }
    }
    return count;
}

int research_equal(COLUMN *col, void *value) {
    if (col == NULL || value == NULL) {
        printf("ERREUR\n");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    for (unsigned int i = 0; i < col->TL; i++) {
        switch (col->type) {
            case UINT:
                if (*(unsigned int*)col->data[i] == *(unsigned int *)value) {
                    count++;
                }
                break;
            case INT:
                if (*(int*)col->data[i] == *(int *)value) {
                    count++;
                }
                break;
            case CHAR:
                if (*(char*)col->data[i] == *(char *)value) {
                    count++;
                }
                break;
            case FLOAT:
                if (*(float*)col->data[i] == *(float *)value) {
                    count++;
                }
                break;
            case DOUBLE:
                if (*(double*)col->data[i] == *(double *)value) {
                    count++;
                }
                break;
            case STRING:
                if (strcmp(col->data[i]->string_value, (char *)value) == 0) {
                    count++;
                }
                break;
            default:
                printf("Type invalide\n");
                return 0;
        }
    }
    return count;
}
int research_inf(COLUMN *col, void *value) {
    if (col == NULL || value == NULL) {
        printf("ERREUR\n");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    for (unsigned int i = 0; i < col->TL; i++) {
        switch (col->type) {
            case UINT:
                if (*(unsigned int*)col->data[i] < *(unsigned int *)value) {
                    count++;
                }
                break;
            case INT:
                if (*(int*)col->data[i] < *(int *)value) {
                    count++;
                }
                break;
            case CHAR:
                if (*(char*)col->data[i] < *(char *)value) {
                    count++;
                }
                break;
            case FLOAT:
                if (*(float*)col->data[i] < *(float *)value) {
                    count++;
                }
                break;
            case DOUBLE:
                if (*(double*)col->data[i] < *(double *)value) {
                    count++;
                }
                break;
            case STRING:
                if (strcmp(col->data[i]->string_value, (char *)value) < 0) {
                    count++;
                }
                break;
            default:
                printf("Type invalide\n");
                return 0;
        }
    }
    return count;
}

void void_insertion_sort(COLUMN* col, int gauche, int droite) {
    for (int i = gauche + 1; i <= droite; i++) {
        void* k = col->data[i];
        int j = i - 1;

        int position = research_sup(col, &k);

        while (j >= gauche && j >= position) {
            col->data[j + 1] = col->data[j];
            j--;
        }
        col->data[j + 1] = k;
    }
}

int void_partition(COLUMN* col, int gauche, int droite) {
    void* pivot = col->data[droite];
    int i = gauche - 1;

    int pivot_position = research_inf(col, &pivot);

    for (int j = gauche; j <= droite - 1; j++) {
        if (research_inf(col, &col->data[j]) <= pivot_position) {
            i++;
            void* temp = col->data[i];
            col->data[i] = col->data[j];
            col->data[j] = temp;
        }
    }

    void* temp = col->data[i + 1];
    col->data[i + 1] = col->data[droite];
    col->data[droite] = temp;

    return (i + 1);
}

void void_quicksort(COLUMN* col, int gauche, int droite) {
    if (gauche < droite) {
        int pi = void_partition(col, gauche, droite);
        void_quicksort(col, gauche, pi - 1);
        void_quicksort(col, pi + 1, droite);
    }
}

void void_sort(COLUMN* col, int gauche, int droite) {
    if (col->valid_index == 0) {
        // La colonne n'est pas du tout triée, appliquer Quicksort
        void_quicksort(col, gauche, droite);
    } else if (col->valid_index == -1) {
        // La colonne est partiellement triée, appliquer le tri par insertion
        void_insertion_sort(col, gauche, droite);
    }
}