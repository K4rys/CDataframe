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
        printf("Combien de valeurs souhaitez vous ajouter a la colonne %s:\n",col->title);
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

void add_lig(CDATAFRAME *cdf){
    lnode *current_node = get_first_node(cdf);
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        printf("Quel valeur souhaitez vous ajouter a colonne %s ligne %d : \n",col->title,col->size+1);
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
        current_node = get_next_node(cdf, current_node);
    }

}



void del_lig(CDATAFRAME *cdf, int indice){
    lnode *current_node = get_first_node(cdf);
    while (current_node != NULL) {
        COLUMN *col = current_node->data;

        col->data[indice-1]=NULL;
        free(col->data[indice-1]);



        current_node = get_next_node(cdf, current_node);

    }
}

void add_col(CDATAFRAME *cdf, ENUM_TYPE coltype, int indice){
    char titre[1220000];
    printf("Quel sera le nom de la nouvelle colonne : \n");
    scanf("%s",titre);
    COLUMN* col = create_column(coltype, strdup(titre));

    int nombre;
    printf("Combien de valeurs souhaitez vous ajouter a la colonne %s:\n",col->title);
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
    lnode *current_node = get_first_node(cdf);
    lnode *noeud = lst_create_lnode(col);
    if (indice<=1){
        lst_insert_head(cdf,noeud);
    }
    else {
        for (int i = 0; i < indice - 2; i++) {
            current_node = get_next_node(cdf, current_node);
        }

        lst_insert_after(cdf, noeud, current_node);
    }
}


void del_col(CDATAFRAME *cdf, int indice){
    lnode *current_node = get_first_node(cdf);
    for (int i = 0; i<indice-2; i++) {
        current_node = get_next_node(cdf,current_node);
    }
    lst_delete_lnode(cdf, current_node);

}



void rename_col(CDATAFRAME *cdf, int indice){
    lnode *current_node = get_first_node(cdf);
    for (int i = 0; i<indice-1; i++) {
        current_node = get_next_node(cdf,current_node);
    }
    COLUMN *col = current_node->data;
    char titre[1220000];

    printf("Quel sera le nouveau nom de la colonne %d ? :\n",indice);
    scanf("%s",titre);
    col->title = strdup(titre);


}

void is_in_cdataframe(CDATAFRAME *cdf,void* x){
    lnode *current_node = get_first_node(cdf);
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        if (nb_occurence(col,x)>=1){
            printf("La valeur se trouve dans le cdataframe a la colonne %s\n",col->title);
        }

        current_node = get_next_node(cdf, current_node);

    }
}


void print_column_name(CDATAFRAME *cdf){
    lnode *current_node = get_first_node(cdf);
    printf("Le nom des colonnes :\n");
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        printf("\t%s\n",col->title);

        current_node = get_next_node(cdf, current_node);

    }

}


int nb_col(CDATAFRAME *cdf){
    lnode *current_node = get_first_node(cdf);
    int compteur = 0;
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        compteur++;
        current_node = get_next_node(cdf, current_node);
    }
    //printf("Il y a %d colonnes",compteur);
    return compteur;

}

int nb_lig(CDATAFRAME *cdf){
    lnode *current_node = get_first_node(cdf);
    int max = 0;
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        if(col->size>max){
            max = col->size;
        }
        current_node = get_next_node(cdf, current_node);
    }
    return max;

}

void nb_equal_to(CDATAFRAME *cdf, void* x){
    lnode *current_node = get_first_node(cdf);
    int nb = 0;
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        nb+= nb_occurence(col,x);
        current_node = get_next_node(cdf, current_node);
    }
    printf("Il y a %d celulles egale(s) a x",nb);

}

void nb_superior_to(CDATAFRAME *cdf, void* x){
    lnode *current_node = get_first_node(cdf);
    int nb = 0;
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        nb+= nb_value_superior(col,x);
        current_node = get_next_node(cdf, current_node);
    }
    printf("Il y a %d celulles superieure(s) a x",nb);

}

void nb_inferior_to(CDATAFRAME *cdf, void* x){
    lnode *current_node = get_first_node(cdf);
    int nb = 0;
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        nb+= nb_value_inferior(col,x);
        current_node = get_next_node(cdf, current_node);
    }
    printf("Il y a %d celulles inferieure(s) a x",nb);
}

void replace_value_cdataframe(CDATAFRAME *cdf, void* value, int indice_col, int indice_lig){
    lnode *current_node = get_first_node(cdf);
    if (indice_col>nb_col(cdf)){
        printf("Indice colonne : %d nb col : %d\n",indice_col, nb_col(cdf));
        return;
    }
    for (int i = 1; i<indice_col; i++) {
        current_node = get_next_node(cdf,current_node);

    }
    COLUMN *col = current_node->data;

    if (col == NULL) {
        printf("Colonne invalide.\n");
        return;
    }


    if (indice_lig >= col->max_size) {

        if (col->max_size == 0) {
            col->data = malloc(REALOC_SIZE * sizeof(int));
            col->max_size = 256;
        } else {
            col->max_size += REALOC_SIZE;
            col->data = realloc(col->data, col->max_size * sizeof(int));
        }


        if (col->data == NULL) {
            printf("Échec de l'allocation mémoire.\n");
            return;
        }
    }
    switch(col->column_type) {
        case INT: {
            if (value != NULL) {
                col->data[indice_lig-1] = malloc(sizeof(int));
                if (col->data[indice_lig-1] == NULL) {
                    printf("Échec de l'allocation mémoire.\n");
                }
                *((int *) col->data[indice_lig-1]) = *((int *) value);
            } else {
                col->data[indice_lig-1] = NULL;
            }

            break;
        }
        case UINT: {
            if (value != NULL) {
                col->data[indice_lig-1] = malloc(sizeof(unsigned int));
                if (col->data[indice_lig-1] == NULL) {
                    printf("Échec de l'allocation mémoire.\n");
                }
                *((unsigned int *) col->data[indice_lig-1]) = *((unsigned int *) value);
            } else {
                col->data[indice_lig-1] = NULL;
            }

            break;
        }
        case CHAR: {

            if (value != NULL) {
                col->data[indice_lig-1] = malloc(sizeof(char));
                if (col->data[indice_lig-1] == NULL) {
                    printf("Échec de l'allocation mémoire.\n");
                }
                *((char *) col->data[indice_lig-1]) = *((char *) value);
            } else {
                col->data[indice_lig-1] = NULL;
            }

            break;
        }
        case FLOAT: {
            if (value != NULL) {
                col->data[indice_lig-1] = malloc(sizeof(float));
                if (col->data[indice_lig-1] == NULL) {
                    printf("Échec de l'allocation mémoire.\n");
                }
                *((float *) col->data[indice_lig-1]) = *((float *) value);
            } else {
                col->data[indice_lig-1] = NULL;
            }

            break;
        }
        case DOUBLE: {
            if (value != NULL) {
                col->data[indice_lig-1] = malloc(sizeof(double));
                if (col->data[indice_lig-1] == NULL) {
                    printf("Échec de l'allocation mémoire.\n");
                }
                *((double *) col->data[indice_lig-1]) = *((double *) value);
            } else {
                col->data[indice_lig-1] = NULL;
            }

            break;
        }
        case STRING: {
            if (value != NULL) {
                col->data[indice_lig-1] = malloc(strlen((char *) value) + 1);
                if (col->data[indice_lig-1] == NULL) {
                    printf("Échec de l'allocation mémoire.\n");
                }
                strcpy((char *) col->data[indice_lig-1], (char *) value);
            } else {
                col->data[indice_lig-1] = NULL;
            }
            break;

        }


        default:
            printf("Le format de la colonne est invalide");
            break;
    }
    if (col->size<indice_lig){
        col->size = indice_lig;
    }

}

CDATAFRAME* load_from_csv(char* name, ENUM_TYPE *cdftype, int size) {
    FILE* file;
    CDATAFRAME *cdf = create_cdataframe(cdftype, size);
    char line[1000];

    file = fopen(name, "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return cdf;
    }
    int colonne = 1;
    int ligne = 1;
    char str[255];

    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, ";");
        colonne = 0;
        for (int i =0; i<size;i++){
            colonne++;
            COLUMN *col = get_first_node(cdf)->data;

            switch(cdftype[colonne-1]) {
                case INT: {
                    int current = atoi(token);
                    void *ptr = &current;
                    replace_value_cdataframe(cdf, ptr, colonne, ligne);
                    break;
                }
                case UINT: {
                    unsigned int current = (unsigned int)strtoul(token, NULL, 10);
                    void *ptr = &current;
                    replace_value_cdataframe(cdf, ptr, colonne, ligne);
                    break;
                }
                case CHAR: {
                    char current = token[0]; // Supposant que vous voulez stocker le premier caractère de la chaîne
                    void *ptr = &current;
                    replace_value_cdataframe(cdf, ptr, colonne, ligne);
                    break;
                }
                case FLOAT: {
                    float current = strtof(token, NULL);
                    void *ptr = &current;
                    replace_value_cdataframe(cdf, ptr, colonne, ligne);
                    break;
                }
                case DOUBLE: {
                    double current = atof(token);
                    void *ptr = &current;
                    replace_value_cdataframe(cdf, ptr, colonne, ligne);
                    break;
                }
                case STRING: {
                    replace_value_cdataframe(cdf, token, colonne, ligne);
                    break;
                }
            }



            token = strtok(NULL, ";");
        }
        ligne++;

    }

    fclose(file);

    return cdf;
}

void export_cdataframe(char* name, CDATAFRAME* cdf){
    FILE* file = NULL;

    file = fopen(name, "w");

    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }


    char str[255];
    lnode* current_node = get_first_node(cdf);
    while (current_node != NULL){
        COLUMN *col = current_node->data;

        fputs(col->title, file);
        if(current_node!= get_last_node(cdf)){
            fputs(";", file);
        }

        current_node = get_next_node(cdf,current_node);
    }
    fputs("\n", file);



    for(int i = 0; i< nb_lig(cdf); i++){

        lnode* current_node = get_first_node(cdf);

        while (current_node != NULL){
            COLUMN *col = current_node->data;
            convert_value(col,i,str,sizeof(str));

            fputs(str, file);
            if(current_node!= get_last_node(cdf)){
                fputs(";", file);
            }

            current_node = get_next_node(cdf,current_node);
        }

        fputs("\n", file);
    }



    fclose(file);

}