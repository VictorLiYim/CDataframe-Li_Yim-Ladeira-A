#ifndef CDATAFRAME_LI_YIM_LADEIRA_A_FUNCTIONS_H
#define CDATAFRAME_LI_YIM_LADEIRA_A_FUNCTIONS_H

#include "cdataframe.h"



int nb_occurrences(COLUMN* col, int x);
int search_val(COLUMN* col, int x);
int research_sup(COLUMN* col, int x);
int research_inf(COLUMN* col, int x);
int research_equal(COLUMN* col, int x);


void print_raws(CDataframe* cdataframe);
#endif //CDATAFRAME_LI_YIM_LADEIRA_A_FUNCTIONS_H
