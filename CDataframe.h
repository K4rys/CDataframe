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



#endif //CDATAFRAME_CDATAFRAME_H
