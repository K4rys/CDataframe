//
// Created by natha on 21/04/2024.
//

#include "column.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* Create a new column
* @param1 : Column type
* @param2 : Column title
* @return : Pointer to the created column
*/
COLUMN *create_column(ENUM_TYPE type, char *title){

    COLUMN *col = malloc(sizeof(COLUMN));

    if (col == NULL) {
        printf("Colonne invalide.\n");
        return NULL;
    }

    col->title = title;
    col->size = 0;
    col->max_size = 0;
    col->column_type = type;
    col->data = NULL;
    col->index = NULL;

    return col;
}

/**
* @brief: Insert a new value into a column
* @param1: Pointer to the column
* @param2: Pointer to the value to insert
* @return: 1 if the value is correctly inserted 0 otherwise
*/
int insert_value(COLUMN *col, void *value) {

    if (col == NULL) {
        printf("Colonne invalide.\n");
        return 0;
    }


    if (col->size >= col->max_size) {

        if (col->max_size == 0) {
            col->data = malloc(REALOC_SIZE * sizeof(int));
            col->max_size = 256;
        } else {
            col->max_size += REALOC_SIZE;
            col->data = realloc(col->data, col->max_size * sizeof(int));
        }


        if (col->data == NULL) {
            printf("Échec de l'allocation mémoire.\n");
            return 0;
        }
    }


    switch(col->column_type) {
        case INT: {
            if (value!=NULL){
                col->data[col->size] = malloc(sizeof(int));
                if (col->data[col->size] == NULL) {
                    printf("Échec de l'allocation mémoire.\n");
                    return 0;
                }
                *((int*)col->data[col->size]) = *((int*)value);
            }
            else{
                col->data[col->size] = NULL;
            }

            break;
        }
        case UINT: {
            if (value!=NULL){
                col->data[col->size] = malloc(sizeof(unsigned int));
                if (col->data[col->size] == NULL) {
                    printf("Échec de l'allocation mémoire.\n");
                    return 0;
                }
                *((unsigned int*)col->data[col->size]) = *((unsigned int*)value);
            }
            else{
                col->data[col->size] = NULL;
            }

            break;
        }
        case CHAR: {

            if (value!=NULL){
                col->data[col->size] = malloc(sizeof(char));
                if (col->data[col->size] == NULL) {
                    printf("Échec de l'allocation mémoire.\n");
                    return 0;
                }
                *((char*)col->data[col->size]) = *((char*)value);
            }
            else{
                col->data[col->size] = NULL;
            }

            break;
        }
        case FLOAT: {
            if (value!=NULL){
                col->data[col->size] = malloc(sizeof(float));
                if (col->data[col->size] == NULL) {
                    printf("Échec de l'allocation mémoire.\n");
                    return 0;
                }
                *((float*)col->data[col->size]) = *((float*)value);
            }
            else{
                col->data[col->size] = NULL;
            }

            break;
        }
        case DOUBLE: {
            if (value!=NULL){
                col->data[col->size] = malloc(sizeof(double));
                if (col->data[col->size] == NULL) {
                    printf("Échec de l'allocation mémoire.\n");
                    return 0;
                }
                *((double*)col->data[col->size]) = *((double*)value);
            }
            else{
                col->data[col->size] = NULL;
            }

            break;
        }
        case STRING: {
            if (value!=NULL) {
                col->data[col->size] = malloc(strlen((char *) value) + 1);
                if (col->data[col->size] == NULL) {
                    printf("Échec de l'allocation mémoire.\n");
                    return 0;
                }
                strcpy((char *) col->data[col->size], (char *) value);
            }
            else{
                col->data[col->size] = NULL;
            }
            break;

        }


        default:
            printf("Le format de la colonne est invalide");
            break;
    }

    col->size++;
    return 1;
}

/**
* @brief: Free the space allocated by a column
* @param1: Pointer to the column
*/
void delete_column(COLUMN **col){

    if (*col == NULL) {
        printf("Colonne invalide.\n");
        return;
    }

    free((*col)->title);
    (*col)->title = NULL;

    for(int i = 0; i < (*col)->max_size; i++) {
        free((*col)->data[i]);
        (*col)->data[i] = NULL;
    }

    free((*col)->index);
    (*col)->index = NULL;
    free((*col));
    *col = NULL;

}

/**
* @brief: Convert a value into a string
* @param1: Pointer to the column
* @param2: Position of the value in the data array
* @param3: The string in which the value will be written
* @param4: Maximum size of the string
*/
void convert_value(COLUMN *col, unsigned long long int i, char *str, int size) {
    if (col == NULL || i >= col->size) {
        printf("Colonne invalide ou indice hors limites.\n");
        return;
    }

    if (col->data[i] == NULL) {
        snprintf(str, size, "NULL");
        return;
    }

    switch(col->column_type) {
        case INT:
            snprintf(str, size, "%d", *((int*)col->data[i]));
            break;
        case UINT:
            snprintf(str, size, "%u", *((unsigned int*)col->data[i]));
            break;
        case CHAR:
            snprintf(str, size, "%c", *((char*)col->data[i]));
            break;
        case FLOAT:
            snprintf(str, size, "%f", *((float*)col->data[i]));
            break;
        case DOUBLE:
            snprintf(str, size, "%lf", *((double*)col->data[i]));
            break;
        case STRING:
            strncpy(str, (char*)col->data[i], size - 1);
            str[size - 1] = '\0';
            break;

        default:
            printf("Type de colonne non pris en charge.\n");
            break;
    }
}

/**
* @brief: Display the content of a column
* @param: Pointer to the column to display
*/
void print_col(COLUMN* col){
    char str[255];
    for (int i = 0; i < col->size; i++) {

        convert_value(col, i, str, sizeof(str));
        printf("[%d] \t %s\n", i, str);
    }
}

int nb_occurence(COLUMN* col, void *x){
    int res=0;

    for(int i = 0; i < col->size; i++){
        if(*(col->data[i]) == x){

        }


    }
    return res;

}