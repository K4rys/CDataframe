//
// Created by natha on 08/05/2024.
//

#ifndef CDATAFRAME_CDATAFRAME_H
#define CDATAFRAME_CDATAFRAME_H
#include <list.h>
#include <column.h>

/**
* Création d'un dataframe
*/
CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size);
void delete_cdataframe(CDATAFRAME **cdf);
void delete_column_in_cdataframe(CDATAFRAME *cdf, char *col_name);
int get_cdataframe_cols_size(CDATAFRAME *cdf);
void fill_cdataframe_user(CDATAFRAME *cdf);
//void fill_cdataframe_hard(CDATAFRAME *cdf, void **tab, const int *taille);
void print_cdataframe(CDATAFRAME *cdf);
void printcol_cdataframe(CDATAFRAME *cdf, int debut, int fin);
void printlig_cdataframe(CDATAFRAME *cdf, int debut, int fin);
void add_lig(CDATAFRAME *cdf);
void del_lig(CDATAFRAME *cdf, int indice);
void add_col(CDATAFRAME *cdf, ENUM_TYPE coltype, int indice);
void del_col(CDATAFRAME *cdf, int indice);
void rename_col(CDATAFRAME *cdf, int indice);
void is_in_cdataframe(CDATAFRAME *cdf,void* x);
void print_column_name(CDATAFRAME *cdf);
int nb_col(CDATAFRAME *cdf);
void nb_lig(CDATAFRAME *cdf);
void nb_equal_to(CDATAFRAME *cdf, void* x);
void nb_superior_to(CDATAFRAME *cdf, void* x);
void nb_inferior_to(CDATAFRAME *cdf, void* x);
void replace_value_cdataframe(CDATAFRAME *cdf, void* value, int indice_col, int indice_lig);
CDATAFRAME *load_from_csv(char* name, ENUM_TYPE* cdftype , int size);



#endif //CDATAFRAME_CDATAFRAME_H
