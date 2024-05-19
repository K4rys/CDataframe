//
// Created by natha on 08/05/2024.
//c

#ifndef CDATAFRAME_CDATAFRAME_H
#define CDATAFRAME_CDATAFRAME_H
#include <list.h>
#include <column.h>


CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size); //check
void delete_cdataframe(CDATAFRAME **cdf); //check
void delete_column_in_cdataframe_name(CDATAFRAME *cdf, char *col_name); //check
int get_cdataframe_cols_size(CDATAFRAME *cdf); //check
void fill_cdataframe_user(CDATAFRAME *cdf); //check
void fill_cdataframe_hard(CDATAFRAME *cdf, void **tab, const int *taille_tab, int nb_col); //check
void print_cdataframe(CDATAFRAME *cdf); //check
void printcol_cdataframe(CDATAFRAME *cdf, int debut, int fin); //check
void printlig_cdataframe(CDATAFRAME *cdf, int debut, int fin); //check
void add_lig(CDATAFRAME *cdf); //check
void del_lig(CDATAFRAME *cdf, int indice); //check
void add_col(CDATAFRAME *cdf, ENUM_TYPE coltype, int indice); //check
void del_col_indice(CDATAFRAME *cdf, int indice); //check
void rename_col(CDATAFRAME *cdf, int indice); //check
void is_in_cdataframe(CDATAFRAME *cdf,void* x); //check
void print_column_name(CDATAFRAME *cdf); //check
int nb_col(CDATAFRAME *cdf); //check
int nb_lig(CDATAFRAME *cdf); //check
void nb_equal_to(CDATAFRAME *cdf, void* x); //check
void nb_superior_to(CDATAFRAME *cdf, void* x); //check
void nb_inferior_to(CDATAFRAME *cdf, void* x); //check
void replace_value_cdataframe(CDATAFRAME *cdf, void* value, int indice_col, int indice_lig); //check
CDATAFRAME *load_from_csv(char* name, ENUM_TYPE* cdftype , int size); //check
void export_cdataframe(char* name, CDATAFRAME* cdf); //check


#endif //CDATAFRAME_CDATAFRAME_H
