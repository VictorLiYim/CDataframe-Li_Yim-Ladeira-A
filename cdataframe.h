#ifndef CDATAFRAME_LI_YIM_LADEIRA_A_CDATAFRAME_H
#define CDATAFRAME_LI_YIM_LADEIRA_A_CDATAFRAME_H
#include "column.h"

typedef struct {
    COLUMN** columns;  // Tableau de pointeurs vers les colonnes
    int num_columns;   // Nombre de colonnes
} CDataframe;

//Alimentation
CDataframe* create_CDataframe(int num_columns);
void read_CDataframe(CDataframe* cdataframe);
void read_cdataframe_hardway(CDataframe* cdataframe);

//Affichage
void print_CDataframe(CDataframe* cdataframe);
void print_CDataframe_limited_raw(CDataframe* cdataframe);
void print_CDataframe_limited_columns(CDataframe* cdataframe);

//Opérations usuelles
void add_raw(CDataframe* cdataframe);
void delete_raw(CDataframe* cdataframe);
void add_column(CDataframe* cdataframe);
void delete_columncdf(CDataframe* cdataframe);
void rename_title(CDataframe* cdataframe);
int search_value(CDataframe *dataframe, void *value, ENUM_TYPE type);
void search(CDataframe* cdataframe);
void print_name(CDataframe* cdataframe);

//Analyse et statistiques

void print_num_raw(CDataframe* cdataframe);
void print_num_col(CDataframe* cdataframe);
int research_cel_equal(CDataframe* df, void* value, ENUM_TYPE type);
int research_cel_inf(CDataframe* df, void* value, ENUM_TYPE type);
int research_cel_sup(CDataframe* df, void* value, ENUM_TYPE type);

#endif //CDATAFRAME_LI_YIM_LADEIRA_A_CDATAFRAME_H
