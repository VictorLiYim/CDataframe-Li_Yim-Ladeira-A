//
// Created by Victor Li Yim on 19/04/2024.
//

#ifndef CDATAFRAME_LI_YIM_LADEIRA_A_CDATAFRAME_H
#define CDATAFRAME_LI_YIM_LADEIRA_A_CDATAFRAME_H

#include "column.h"

typedef struct {
    COLUMN** columns;  // Tableau de pointeurs vers les colonnes
    int num_columns;   // Nombre de colonnes
} CDataframe;

CDataframe* create_CDataframe(int num_columns);
void read_CDataframe(CDataframe* cdataframe);
void print_CDataframe(CDataframe* cdataframe);
void read_cdataframe_hardway(CDataframe* cdataframe);
void print_CDataframe_limited_raw(CDataframe* cdataframe);
void print_CDataframe_limited_columns(CDataframe* cdatafram);
void add_column(CDataframe* cdataframe);

#endif //CDATAFRAME_LI_YIM_LADEIRA_A_CDATAFRAME_H
