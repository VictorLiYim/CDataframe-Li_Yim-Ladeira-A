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
    printf("%s : \n", col->name);
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

// Fonction de tri par insertion
void insertion_sort(COLUMN* col, int left, int right, int sort_dir) {
    for (int i = left + 1; i <= right; i++) {
        unsigned long long int index = col->index[i];
        void* key = col->data[index];
        int j = i - 1;

        // Comparaison et déplacement des éléments
        while (j >= left) {
            void* currentValue = col->data[col->index[j]];
            if ((sort_dir == ASC && col->type == UINT && *((unsigned int*)currentValue) > *((unsigned int*)key)) ||
                (sort_dir == DESC && col->type == UINT && *((unsigned int*)currentValue) < *((unsigned int*)key))) {
                col->index[j + 1] = col->index[j];
                j--;
            } else if ((sort_dir == ASC && col->type == INT && *((int*)currentValue) > *((int*)key)) ||
                       (sort_dir == DESC && col->type == INT && *((int*)currentValue) < *((int*)key))) {
                col->index[j + 1] = col->index[j];
                j--;
            } else if ((sort_dir == ASC && col->type == CHAR && *((char*)currentValue) > *((char*)key)) ||
                       (sort_dir == DESC && col->type == CHAR && *((char*)currentValue) < *((char*)key))) {
                col->index[j + 1] = col->index[j];
                j--;
            } else if ((sort_dir == ASC && col->type == FLOAT && *((float*)currentValue) > *((float*)key)) ||
                       (sort_dir == DESC && col->type == FLOAT && *((float*)currentValue) < *((float*)key))) {
                col->index[j + 1] = col->index[j];
                j--;
            } else if ((sort_dir == ASC && col->type == DOUBLE && *((double*)currentValue) > *((double*)key)) ||
                       (sort_dir == DESC && col->type == DOUBLE && *((double*)currentValue) < *((double*)key))) {
                col->index[j + 1] = col->index[j];
                j--;
            } else {
                break;
            }
        }
        col->index[j + 1] = index;
    }
}

// Fonction de tri rapide
void quicksort(COLUMN* col, int left, int right, int sort_dir) {
    if (left < right) {
        unsigned long long int pivotIndex = partition(col, left, right, sort_dir);
        quicksort(col, left, pivotIndex - 1, sort_dir);
        quicksort(col, pivotIndex + 1, right, sort_dir);
    }
}

// Fonction de partitionnement pour le tri rapide
int partition(COLUMN* col, int left, int right, int sort_dir) {
    unsigned long long int pivotIndex = col->index[right];
    void* pivotValue = col->data[pivotIndex];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        void* currentValue = col->data[col->index[j]];
        int comparisonResult;

        // Comparaison des chaînes de caractères
        if (col->type == STRING) {
            char* currentString = (char*)currentValue;
            char* pivotString = (char*)pivotValue;

            if (sort_dir == ASC) {
                comparisonResult = strcmp(currentString, pivotString);
            } else {
                comparisonResult = strcmp(pivotString, currentString);
            }
        } else {
            // Comparaison des autres types de données
            if (col->type == UINT) {
                comparisonResult = (*((unsigned int*)currentValue) <= *((unsigned int*)pivotValue)) ? -1 : 1;
            } else if (col->type == INT) {
                comparisonResult = (*((int*)currentValue) <= *((int*)pivotValue)) ? -1 : 1;
            } else if (col->type == CHAR) {
                comparisonResult = (*((char*)currentValue) <= *((char*)pivotValue)) ? -1 : 1;
            } else if (col->type == FLOAT) {
                comparisonResult = (*((float*)currentValue) <= *((float*)pivotValue)) ? -1 : 1;
            } else if (col->type == DOUBLE) {
                comparisonResult = (*((double*)currentValue) <= *((double*)pivotValue)) ? -1 : 1;
            }
        }

        // Vérification du sens de tri
        if ((sort_dir == ASC && comparisonResult <= 0) || (sort_dir == DESC && comparisonResult >= 0)) {
            i++;
            unsigned long long int temp = col->index[i];
            col->index[i] = col->index[j];
            col->index[j] = temp;
        }
    }

    // Échange du pivot avec l'élément à la position i+1
    unsigned long long int temp = col->index[i + 1];
    col->index[i + 1] = col->index[right];
    col->index[right] = temp;

    return i + 1;
}



void sort(COLUMN* col, int sort_dir) {
    if (col == NULL || col->index == NULL) {
        printf("La colonne ou l'index est vide.\n");
        return;
    }
    // Vérifier si la colonne est partiellement triée
    if (col->valid_index == -1) {
        insertion_sort(col, 0, col->TL - 1, sort_dir);
    } else {
        quicksort(col, 0, col->TL - 1, sort_dir);
    }

    // Mettre à jour la direction de tri
    col->sort_dir = sort_dir;
}

void print_col_by_index(COLUMN *col) {
    if (col == NULL) {
        printf("Column is NULL\n");
        return;
    }

    printf("[NAME] %s\n", col->name);

    // Parcourir l'index et afficher les valeurs dans l'ordre spécifié
    for (unsigned long long int i = 0; i < col->TL; i++) {
        unsigned long long int index = col->index[i];
        void *value = col->data[index];

        // Convertir la valeur en chaîne de caractères et l'afficher
        char str[50];
        convert_value(col, index, str, sizeof(str));
        printf("[%llu] %s\n", index, str);
    }
}

void erase_index(COLUMN *col) {
    if (col == NULL || col->index == NULL) {
        return; // Rien à faire si l'index est déjà NULL ou la colonne est NULL
    }

    // Libérer la mémoire allouée pour le tableau des index
    free(col->index);

    // Mise à jour des attributs
    col->index = NULL;
    col->valid_index = 0;
}


int check_index(COLUMN *col) {
    if (col == NULL || col->index == NULL) {
        return 0; // Aucun index trouvé si la colonne ou son index sont NULL
    }

    if (col->valid_index == -1) {
        return -1; // Index invalide
    }

    return 1; // Index valide trouvé
}
void update_index(COLUMN *col) {
    if (col == NULL || col->data == NULL || col->TL == 0) {
        printf("ERREUR");
        exit(EXIT_FAILURE);
    }
    // Vérifier si l'index existe
    if (!check_index(col)) {
        sort(col, ASC); // Si l'index n'existe pas, trier la colonne en ordre ascendant
    } else {
        // Si l'index existe, le mettre à jour en triant la colonne en ordre ascendant
        erase_index(col); // Supprimer l'index actuel
        sort(col, ASC); // Trier la colonne pour créer un nouvel index
    }
}

int search_value_in_column(COLUMN *col, void *val) {
    if (col == NULL || col->data == NULL || col->TL == 0 || !check_index(col)) {
        return -1; // Colonnes non triées ou index inexistant, impossible de faire une recherche dichotomique
    }
    // Recherche dichotomique
    unsigned long long int left = 0;
    unsigned long long int right = col->TL - 1;
    while (left <= right) {
        unsigned long long int mid = (left + right) / 2;
        int cmp;
        switch (col->type) {
            case UINT:
                cmp = (*((unsigned int *)col->data[col->index[mid]]) > *((unsigned int *)val)) - (*((unsigned int *)col->data[col->index[mid]]) < *((unsigned int *)val));
                break;
            case INT:
                cmp = (*((int *)col->data[col->index[mid]]) > *((int *)val)) - (*((int *)col->data[col->index[mid]]) < *((int *)val));
                break;
            case CHAR:
                cmp = (*((char *)col->data[col->index[mid]]) > *((char *)val)) - (*((char *)col->data[col->index[mid]]) < *((char *)val));
                break;
            case FLOAT:
                cmp = (*((float *)col->data[col->index[mid]]) > *((float *)val)) - (*((float *)col->data[col->index[mid]]) < *((float *)val));
                break;
            case DOUBLE:
                cmp = (*((double *)col->data[col->index[mid]]) > *((double *)val)) - (*((double *)col->data[col->index[mid]]) < *((double *)val));
                break;
            case STRING:
                cmp = strcmp(col->data[col->index[mid]], (char *)val);
                break;
            case STRUCTURE:
                // Comparaison de structures non implémentée ici
                return -1;
            default:
                return -1;
        }

        if (cmp == 0) {
            return 1; // La valeur a été trouvée
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return 0; // La valeur n'a pas été trouvée
}