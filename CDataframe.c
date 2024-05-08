//
// Created by natha on 08/05/2024.
//

#include "CDataframe.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
* Création d'un dataframe
*/
CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size) {
    list *lst = lst_create_list();
    char titre[1220000];
    //char *ptr_titre = strdup(titre);
    for (int i = 0; i < size; i++) {
        printf("Quel sera le nom de la colonne %d ? :\n",i);
        scanf("%s",titre);
        COLUMN* column = create_column(cdftype[i], strdup(titre));
        lnode* noeud = lst_create_lnode(column);
        lst_insert_tail(lst, noeud);
    }
    return lst;
}

/**
* @brief: Column deletion
* param1: Pointer to the CDataframe to delete
*/
void delete_cdataframe(CDATAFRAME **cdf){
    lnode* first_node = get_first_node((*cdf));
    lnode* current_node = first_node;
    while (current_node != get_last_node((*cdf))){
        delete_column(current_node->data);
        current_node = get_next_node((*cdf),current_node);
    }
    lst_erase((*cdf));
}

/**
* @breif: Delete column by name
* @param1: Pointer to the CDataframe
* @param2: Column name
*/
void delete_column_in_cdataframe(CDATAFRAME *cdf, char *col_name){
    lnode* first_node = get_first_node(cdf);
    lnode* current_node = first_node;
    while (current_node != get_last_node(cdf)){
        COLUMN* column = current_node->data;
        if(strcmp(column->title,col_name)==0){
            delete_column(&column);
            current_node->data = NULL;

        }
        current_node = get_next_node(cdf,current_node);
    }
}

/**
* @brief: Number of columns
* @param1: Point to the CDataframe
* @return: Number of columns in the CDataframe
*/
int get_cdataframe_cols_size(CDATAFRAME *cdf){
    int compteur = 0;
    lnode* first_node = get_first_node(cdf);
    lnode* current_node = first_node;
    while (current_node != NULL){
        if(current_node->data!=NULL){
            compteur++;
        }
        current_node = get_next_node(cdf,current_node);
    }
    return compteur;
}


void fill_cdataframe_user(CDATAFRAME *cdf) {
    lnode *current_node = get_first_node(cdf);

    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        int nombre;
        printf("Combien de valeurs souhaitez vous ajouter à la colonne %s:\n",col->title);
        scanf("%d",&nombre);
        for(int i = 0; i<nombre; i++) {
            printf("Enter values for column %s:\n", col->title);

            switch (col->column_type) {
                case INT: {
                    int value;
                    scanf("%d", &value);
                    int *ptr_value = &value;
                    insert_value(col, (void *) ptr_value);
                    break;
                }
                case UINT: {
                    unsigned int value;
                    scanf("%u", &value);
                    unsigned int *ptr_value = &value;
                    insert_value(col, (void *) ptr_value);
                    break;
                }
                case CHAR: {
                    char value;
                    scanf("%c", &value);
                    char *ptr_value = &value;
                    insert_value(col, (void *) ptr_value);
                    break;
                }

                case FLOAT: {
                    float value;
                    scanf("%f", &value);
                    float *ptr_value = &value;
                    insert_value(col, (void *) ptr_value);
                    break;
                }
                case DOUBLE: {
                    double value;
                    scanf("%lf", &value);
                    double *ptr_value = &value;
                    insert_value(col, (void *) ptr_value);
                    break;
                }
                case STRING: {
                    char value[120000];
                    scanf("%s", value);
                    char *ptr_value = value;
                    insert_value(col, (void *) ptr_value);
                    break;
                }


                default: {
                    printf("Le format de la colonne est invalide");
                    break;
                }
            }
        }
        current_node = get_next_node(cdf, current_node);
    }
}

/*void fill_cdataframe_hard(CDATAFRAME *cdf, void **tab, const int *taille){
    lnode* first_node = get_first_node(cdf);
    lnode* current_node = first_node;
    int indice = 0;
    while (current_node != NULL){
        COLUMN *col = current_node->data;
        for(int i = 0; i < taille[indice]; i++){
            switch(col->column_type) {
                case INT: {
                    int *row = (int *)tab[indice];
                    for (int i = 0; i < taille[indice]; i++) {
                        int value = row[i];
                        int *ptr_value = &value;
                        insert_value(col, (void *)ptr_value);
                    }
                    break;
                }
                case UINT: {
                    unsigned int *row = (unsigned int *)tab[indice];
                    for (int i = 0; i < taille[indice]; i++) {
                        unsigned int value = row[i];
                        unsigned int *ptr_value = &value;
                        insert_value(col, (void *)ptr_value);
                    }
                    break;
                }
                case CHAR: {
                    char *row = (char *)tab[indice];
                    for (int i = 0; i < taille[indice]; i++) {
                        char value = row[i];
                        char *ptr_value = &value;
                        insert_value(col, (void *)ptr_value);
                    }
                    break;
                }

                case FLOAT: {
                    float *row = (float *)tab[indice];
                    for (int i = 0; i < taille[indice]; i++) {
                        float value = row[i];
                        float *ptr_value = &value;
                        insert_value(col, (void *)ptr_value);
                    }
                    break;
                }
                case DOUBLE: {
                    double *row = (double *)tab[indice];
                    for (int i = 0; i < taille[indice]; i++) {
                        double value = row[i];
                        double *ptr_value = &value;
                        insert_value(col, (void *)ptr_value);
                    }
                    break;
                }
                case STRING: {
                    char **row = (char **)tab[indice];
                    for (int i = 0; i < taille[indice]; i++) {
                        char *value = row[i];
                        char *ptr_value = strdup(value);
                        insert_value(col, (void *)ptr_value);
                    }
                    break;
                }


                default: {
                    printf("Le format de la colonne est invalide");
                    break;
                }
            }

        }
        current_node = get_next_node(cdf,current_node);
    }
}*/

void print_cdataframe(CDATAFRAME *cdf) {
    lnode *current_node = get_first_node(cdf);
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        printf("Column %s:\n", col->title);
        print_col(col);
        printf("\n");
        current_node = get_next_node(cdf, current_node);
    }
}

void printcol_cdataframe(CDATAFRAME *cdf, int debut, int fin){
    lnode *current_node = get_first_node(cdf);
    int compteur = 1;
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        if(compteur >= debut && compteur <=fin) {
            print_col(col);
        }
        compteur++;
        current_node = get_next_node(cdf, current_node);
    }
}

void printlig_cdataframe(CDATAFRAME *cdf, int debut, int fin) {
    lnode *current_node = get_first_node(cdf);

    for(int i = debut; i<fin+1; i++){
        printf("ligne %d:\n",i);
        current_node = get_first_node(cdf);
        while (current_node != NULL) {
            COLUMN *col = current_node->data;

            char str[255];

            convert_value(col, i-1, str, sizeof(str));
            printf("%s\n", str);
            current_node = get_next_node(cdf, current_node);
        }

    }


}