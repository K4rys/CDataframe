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
COLUMN *create_column(ENUM_TYPE type, char* title){

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
    col->index = malloc(REALOC_SIZE*sizeof(int));

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
            col->index = realloc(col->index,col->max_size*sizeof(int));
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
                col->index[col->size] = col->size;
            }
            else{
                col->data[col->size] = NULL;
                col->index[col->size] = col->size;
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
                col->index[col->size] = col->size;
            }
            else{
                col->data[col->size] = NULL;
                col->index[col->size] = col->size;
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
                col->index[col->size] = col->size;
            }
            else{
                col->data[col->size] = NULL;
                col->index[col->size] = col->size;
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
                col->index[col->size] = col->size;
            }
            else{
                col->data[col->size] = NULL;
                col->index[col->size] = col->size;
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
                col->index[col->size] = col->size;
            }
            else{
                col->data[col->size] = NULL;
                col->index[col->size] = col->size;
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
                col->index[col->size] = col->size;
            }
            else{
                col->data[col->size] = NULL;
                col->index[col->size] = col->size;
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

    if (col == NULL) {
        printf("Colonne invalide.\n");
        return;
    }

    char str[255];
    for (int i = 0; i < col->size; i++) {

        convert_value(col, i, str, sizeof(str));
        printf("[%d] \t %s\n", i, str);
    }
}

/**
 * @brief Return the number of occurrences of a value in a column
 * @param Pointer to the column to search
 * @param Pointer to the value to compare
 * @return number of occurrences of a value in a column
 */
int nb_occurence(COLUMN* col, void *value){

    if (col == NULL) {
        printf("Colonne invalide.\n");
        return 0;
    }


    int compteur = 0;

    switch(col->column_type) {
        case INT: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(int *) col->data[i]) == (*(int *) value)) {
                            compteur++;

                        }
                    }
                }
            }

            break;
        }
        case UINT: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(unsigned int *) col->data[i]) == (*(unsigned int *) value)) {
                            compteur++;

                        }
                    }
                }
            }
            break;
        }
        case CHAR: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(char *) col->data[i]) == (*(char *) value)) {
                            compteur++;

                        }
                    }
                }
            }
            break;
        }

        case FLOAT: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(float *) col->data[i]) == (*(float *) value)) {
                            compteur++;

                        }
                    }
                }
            }
            break;
        }
        case DOUBLE: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(double *) col->data[i]) == (*(double *) value)) {
                            compteur++;

                        }
                    }
                }
            }
            break;
        }
        case STRING: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if (strcmp((char *) col->data[i], (char *) value) == 0) {
                            compteur++;
                        }
                    }
                }
            }

            break;

        }


        default: {
            printf("Le format de la colonne est invalide");
            break;
        }
    }

    return compteur;

}

/**
 * @brief Return the pointer of the value at the position i
 * @param Pointer to the column to search
 * @param Position of the value
 * @return The pointer of the value at the position i
 */
void* get_value(COLUMN* col, int i){

    if (col == NULL) {
        printf("Colonne invalide.\n");
        return 0;
    }
    if(i>col->size){
        printf("Position trop grande par rapport à la taille de la colonne\n");
        return 0;
    }
    return col->data[i];

}

/**
 * @brief Return the number of values in the column greater than a specified value
 * @param Pointer to the column to search
 * @param Pointer to the value to compare against
 * @return The number of values in the column greater than the specified value
 */
int nb_value_superior(COLUMN* col, void* value){

    if (col == NULL) {
        printf("Colonne invalide.\n");
        return 0;
    }


    int compteur = 0;

    switch(col->column_type) {
        case INT: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(int *) col->data[i]) > (*(int *) value)) {
                            compteur++;

                        }
                    }
                }
            }

            break;
        }
        case UINT: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(unsigned int *) col->data[i]) > (*(unsigned int *) value)) {
                            compteur++;

                        }
                    }
                }
            }
            break;
        }
        case CHAR: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(char *) col->data[i]) > (*(char *) value)) {
                            compteur++;

                        }
                    }
                }
            }
            break;
        }

        case FLOAT: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(float *) col->data[i]) > (*(float *) value)) {
                            compteur++;

                        }
                    }
                }
            }
            break;
        }
        case DOUBLE: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(double *) col->data[i]) > (*(double *) value)) {
                            compteur++;

                        }
                    }
                }
            }
            break;
        }
        case STRING: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if (strcmp((char *) col->data[i], (char *) value) > 0) {
                            compteur++;
                        }
                    }
                }
            }

            break;

        }


        default: {
            printf("Le format de la colonne est invalide");
            break;
        }
    }

    return compteur;

}

/**
 * @brief Return the number of values in the column less than a specified value
 * @param Pointer to the column to search
 * @param Pointer to the value to compare against
 * @return The number of values in the column less than the specified value
 */
int nb_value_inferior(COLUMN* col, void* value){

    if (col == NULL) {
        printf("Colonne invalide.\n");
        return 0;
    }


    int compteur = 0;

    switch(col->column_type) {
        case INT: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(int *) col->data[i]) < (*(int *) value)) {
                            compteur++;

                        }
                    }
                }
            }

            break;
        }
        case UINT: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(unsigned int *) col->data[i]) < (*(unsigned int *) value)) {
                            compteur++;

                        }
                    }
                }
            }
            break;
        }
        case CHAR: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(char *) col->data[i]) < (*(char *) value)) {
                            compteur++;

                        }
                    }
                }
            }
            break;
        }

        case FLOAT: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(float *) col->data[i]) < (*(float *) value)) {
                            compteur++;

                        }
                    }
                }
            }
            break;
        }
        case DOUBLE: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(double *) col->data[i]) < (*(double *) value)) {
                            compteur++;

                        }
                    }
                }
            }
            break;
        }
        case STRING: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if (strcmp((char *) col->data[i], (char *) value) < 0) {
                            compteur++;
                        }
                    }
                }
            }

            break;

        }


        default: {
            printf("Le format de la colonne est invalide");
            break;
        }
    }

    return compteur;

}

/**
 * @brief Return the number of a value equal to the value given
 * @param Pointer to the column to search
 * @param Pointer to the value to compare
 * @return the number of a value equal to the value given
 */
int nb_value_equal(COLUMN* col, void *value){

    if (col == NULL) {
        printf("Colonne invalide.\n");
        return 0;
    }


    int compteur = 0;

    switch(col->column_type) {
        case INT: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(int *) col->data[i]) == (*(int *) value)) {
                            compteur++;

                        }
                    }
                }
            }

            break;
        }
        case UINT: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(unsigned int *) col->data[i]) == (*(unsigned int *) value)) {
                            compteur++;

                        }
                    }
                }
            }
            break;
        }
        case CHAR: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(char *) col->data[i]) == (*(char *) value)) {
                            compteur++;

                        }
                    }
                }
            }
            break;
        }

        case FLOAT: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(float *) col->data[i]) == (*(float *) value)) {
                            compteur++;

                        }
                    }
                }
            }
            break;
        }
        case DOUBLE: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if ((*(double *) col->data[i]) == (*(double *) value)) {
                            compteur++;

                        }
                    }
                }
            }
            break;
        }
        case STRING: {
            for (int i = 0; i < col->size; i++) {
                if(value!=NULL) {
                    if (col->data[i] != NULL) {
                        if (strcmp((char *) col->data[i], (char *) value) == 0) {
                            compteur++;
                        }
                    }
                }
            }

            break;

        }


        default: {
            printf("Le format de la colonne est invalide");
            break;
        }
    }

    return compteur;

}

/**
* @brief: Sort a column according to a given order
* @param1: Pointer to the column to sort
* @param2: Sort type (ASC or DESC)
*/
void sort(COLUMN* col, int sort_dir){
    char je[250000];
    if (col->valid_index == -1 ){
        for(int i = 2; i<col->size; i++){
            char k[250000];
            convert_value(col, i, k, sizeof(k));
            int j = i - 1;
            while(j>0 && je>k){
                convert_value(col,j,je,sizeof(j));

                j--;
            }

        }

    }

}
