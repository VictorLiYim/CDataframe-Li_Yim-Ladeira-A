//
// Created by Victor Li Yim on 28/03/2024.
//
#include<stdio.h>
#include "functions.h"

int main(){
    COLUMN *mycol = create_column("My column");
    insert_value(mycol, 52);
    insert_value(mycol, 44);
    insert_value(mycol, 15);
    print_col(mycol);
}

