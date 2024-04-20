//
// Created by Victor Li Yim on 19/04/2024.
//

#ifndef CDATAFRAME_LI_YIM_LADEIRA_A_CDATAFRAME_H
#define CDATAFRAME_LI_YIM_LADEIRA_A_CDATAFRAME_H

#include "column.h"

COLUMN** create_CDataframe(int num_columns);
void read_CDataframe(COLUMN** columns, int num_columns);
void read_CDataframe_hardway(COLUMN** cdataframe, int num_columns);
void print_CDataframe(COLUMN** columns, int num_columns);
void print_CDataframe_limited_raw(COLUMN** cdataframe, int num_columns);
void print_CDataframe_limited_columns(COLUMN** cdataframe, int num_columns);
#endif //CDATAFRAME_LI_YIM_LADEIRA_A_CDATAFRAME_H
