//
// Created by Victor Li Yim on 28/03/2024.
//
#include<stdio.h>
#include "functions.h"

int main(){
    COLUMN *mycol = create_column("My column");
    printf("%s, %d", mycol->name);
    return 0;
}

