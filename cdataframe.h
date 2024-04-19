//
// Created by Victor Li Yim on 19/04/2024.
//

#ifndef CDATAFRAME_LI_YIM_LADEIRA_A_CDATAFRAME_H
#define CDATAFRAME_LI_YIM_LADEIRA_A_CDATAFRAME_H

#include "column.h"

typedef struct {
    COLUMN** columns;  // Tableau de pointeurs vers les colonnes
    int num_columns;   // Nombre de colonnes
}CDataframe;

CDataframe* create_dataframe(int num_columns);
void add_column(CDataframe* cdataframe, COLUMN* column);
void delete_dataframe(CDataframe** cdataframe);
void read_CDataframe(CDataframe* cdataframe);
void read_cdataframe_hardway(CDataframe* cdataframe);
void print_dataframe(CDataframe* cdataframe);


#endif //CDATAFRAME_LI_YIM_LADEIRA_A_CDATAFRAME_H
