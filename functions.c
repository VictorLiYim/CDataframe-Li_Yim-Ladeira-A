#include "functions.h"
#include <stdlib.h>
#include <stdio.h>


int nb_occurrences(COLUMN* col, int x){ //Retourner le nombre de d’occurrences d’une valeur x (x donné en paramètre).
    int i, count = 0;
    for(i=0; i<col->TL; i++){
        if(col->data[i]==x){
            count++;
        }
    }
    return count;
}
int search_val(COLUMN* col, int x){ //Retourner la valeur présente à la position x (x donné en paramètre).
    return col->data[x];
}

int research_sup(COLUMN* col, int x){ // Retourner le nombre de valeurs qui sont supérieures à x (x donné en paramètre).
    int i, count = 0;
    for(i=0; i<col->TL; i++){
        if(col->data[i]>x){
            count++;
        }
    }
    return count;
}
int research_inf(COLUMN* col, int x){ //Retourner le nombre de valeurs qui sont inférieures à x (x donné en paramètre).
    int i, count = 0;
    for(i=0; i<col->TL; i++){
        if(col->data[i]<x){
            count++;
        }
    }
    return count;
}
int research_equal(COLUMN* col, int x){ //Retourner le nombre de valeurs qui sont égales à x (x donné en paramètre).
    int i, count = 0;
    for(i=0; i<col->TL; i++){
        if(col->data[i]==x){
            count++;
        }
    }
    return count;
}




