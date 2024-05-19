//
// Created by natha on 08/05/2024.
//

#include "CDataframe.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
* @brief: Création d'un dataframe
* @param1: Array of columns type
* @param2: Size of the array
* @return: Number of columns in the CDataframe
*/
CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size) {
    // Création d'une liste pour stocker les colonnes du dataframe
    list *lst = lst_create_list();
    char titre[1220000];
    // Parcours des types de colonnes pour créer et ajouter chaque colonne au dataframe
    for (int i = 0; i < size; i++) {
        printf("Quel sera le nom de la colonne %d ? :\n",i);
        scanf("%s",titre);
        // Création d'une nouvelle colonne avec le nom spécifié
        COLUMN* column = create_column(cdftype[i], strdup(titre));
        // Création d'un nœud pour la colonne et insertion dans la liste
        lnode* noeud = lst_create_lnode(column);
        lst_insert_tail(lst, noeud);
    }
    return lst;
}

/**
* @brief: Column deletion
* param1: Pointer of pointer to the CDataframe to delete
*/
void delete_cdataframe(CDATAFRAME **cdf){
    // Parcours et suppression de chaque colonne du dataframe


    lnode* current_node = get_first_node((*cdf));

    while (current_node != NULL){
        COLUMN* col = current_node->data;

        delete_column(&col);

        current_node = get_next_node((*cdf),current_node);
    }

    lst_erase((*cdf)); // Suppression de la liste
}

/**
* @breif: Delete column by name
* @param1: Pointer to the CDataframe
* @param2: Column name
*/
void delete_column_in_cdataframe_name(CDATAFRAME *cdf, char *col_name){
    // Parcours du dataframe pour trouver la colonne avec le nom spécifié
    lnode* current_node = get_first_node(cdf);
    while (current_node != NULL){
        COLUMN* column = current_node->data;
        //Test correspondance avec le titre de la colonne à supprimer
        if(strcmp(column->title,col_name)==0){
            delete_column(&column); // Suppression de la colonne
            lst_delete_lnode(cdf,current_node); //Puis suppression du noeud

        }
        current_node = get_next_node(cdf,current_node);
    }
}

/**
* @brief: Number of columns
* @param1: Pointer to the CDataframe
* @return: Number of columns in the CDataframe
*/
int get_cdataframe_cols_size(CDATAFRAME *cdf){
    int compteur = 0;
    lnode* current_node = get_first_node(cdf);
    //Parcours de toute les noeuds
    while (current_node != NULL){
        //Si le noeud contient une colonne non vide
        if(current_node->data!=NULL){
            compteur++;
        }
        current_node = get_next_node(cdf,current_node);
    }
    return compteur;
}

/**
* @brief: Remplit le dataframe en demandant à l'utilisateur d'entrer les valeurs pour chaque colonne.
* @param1: Point to the CDataframe
*/
void fill_cdataframe_user(CDATAFRAME *cdf) {
    lnode *current_node = get_first_node(cdf);
    //Parcours de tous les noeuds du CDF
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        int nombre;
        printf("Combien de valeurs souhaitez vous ajouter a la colonne %s:\n",col->title);
        scanf("%d",&nombre);
        //Ajout du nombre de valeurs indiquées dans la colonne
        for(int i = 0; i<nombre; i++) {
            printf("Enter values for column %s:\n", col->title);

            switch (col->column_type) {
                case INT: {
                    int value;
                    //Si la valeur saisie est de type int
                    if (scanf("%d", &value) == 1) {
                        //Cast en pointeur void
                        int *ptr_value = &value;
                        insert_value(col, (void *) ptr_value);
                    }
                    else
                        printf("La valeur que vous avez saisi ne correspond pas au meme type de valeur que la colonne\n");
                    //Vider le cache pour eviter tout bug
                    fflush(stdin);
                    break;
                }
                case UINT: {
                    unsigned int value;
                    fflush(stdin);
                    //Si la valeur saisie est de type unsigned int
                    if (scanf("%u", &value)==1) {
                        //Cast en pointeur void
                        unsigned int *ptr_value = &value;
                        insert_value(col, (void *) ptr_value);

                    }
                    else
                        printf("La valeur que vous avez saisi ne correspond pas au meme type de valeur que la colonne\n");
                    //Vider le cache pour eviter tout bug
                    fflush(stdin);
                    break;
                }
                case CHAR: {
                    char value;
                    fflush(stdin);
                    //Si la valeur saisie est de type char
                    if (scanf("%c", &value) == 1)
                    {
                        //Cast en pointeur void
                        char *ptr_value = &value;
                        insert_value(col, (void *) ptr_value);

                    }
                    else
                        printf("La valeur que vous avez saisi ne correspond pas au meme type de valeur que la colonne\n");
                    //Vider le cache pour eviter tout bug
                    fflush(stdin);
                    break;
                }

                case FLOAT: {
                    float value;
                    fflush(stdin);
                    //Si la valeur saisie est de type float
                    if (scanf("%f", &value) == 1) {
                        //Cast en pointeur void
                        float *ptr_value = &value;
                        insert_value(col, (void *) ptr_value);

                    }
                    else
                        printf("La valeur que vous avez saisi ne correspond pas au meme type de valeur que la colonne\n");
                    //Vider le cache pour eviter tout bug
                    fflush(stdin);
                    break;
                }
                case DOUBLE: {
                    double value;
                    fflush(stdin);
                    //Si la valeur saisie est de type double
                    if (scanf("%lf", &value) == 1) {
                        //Cast en pointeur void
                        double *ptr_value = &value;
                        insert_value(col, (void *) ptr_value);

                    }
                    else
                        printf("La valeur que vous avez saisi ne correspond pas au meme type de valeur que la colonne\n");
                    //Vider le cache pour eviter tout bug
                    fflush(stdin);
                    break;
                }
                case STRING: {
                    char value[120000];
                    fflush(stdin);
                    //Pas besoins de verifier le type saisie car c'est un string
                    fgets(value,sizeof(value),stdin);
                    //Cast en pointeur void
                    char *ptr_value = value;
                    insert_value(col, (void *) ptr_value);
                    //Vider le cache pour eviter tout bug
                    fflush(stdin);
                    break;
                }


                default: {
                    printf("Le format de la colonne est invalide");
                    break;
                }
            }
        }
        //On passe au prochain noeud
        current_node = get_next_node(cdf, current_node);
    }
}

/**
* @brief: Remplit le dataframe avec une liste de valeurs préremplie
* @param1: Point to the CDataframe
* @param2 : Tableau à double entrée
* @param3 : Tableau de la taille des différentes colonnes
* @param4 : Le nombre de colonnes
*/
void fill_cdataframe_hard(CDATAFRAME *cdf, void **tab, const int *taille_tab, int nb_col) {
    lnode *current_node = get_first_node(cdf);
    //La première boucle itère un nombre de fois égal à "nb_col"
    for (int i = 0; i < nb_col; i++) {
        COLUMN *col = current_node->data;
        //La deuxième boucle itère un nombre égale au nombre de valeurs de la colonne i
        for (int j = 0; j < taille_tab[i]; j++) {
            void *value;
            switch (col->column_type) {
                case INT: {
                    //Cast en pointeur void
                    int *ptr = (int *)tab[i] + j;
                    value = (void *)ptr;
                    break;
                }
                case UINT: {
                    //Cast en pointeur void
                    unsigned int *ptr = (unsigned int *)tab[i] + j;
                    value = (void *)ptr;
                    break;
                }
                case CHAR: {
                    //Cast en pointeur void
                    char *ptr = (char *)tab[i] + j;
                    value = (void *)ptr;
                    break;
                }
                case FLOAT: {
                    //Cast en pointeur void
                    float *ptr = (float *)tab[i] + j;
                    value = (void *)ptr;
                    break;
                }
                case DOUBLE: {
                    //Cast en pointeur void
                    double *ptr = (double *)tab[i] + j;
                    value = (void *)ptr;
                    break;
                }
                case STRING: {
                    //Cast en pointeur void
                    char **ptr = (char **)tab[i] + j;
                    value = *ptr;
                    break;
                }
                default: {
                    printf("Le format de la colonne est invalide\n");
                    break;
                }
            }
            insert_value(col, value); // Appel de la fonction avec le pointeur void *
        }
        current_node = get_next_node(cdf, current_node);
    }
}

/**
* @brief: afficher le dataframe.
* @param1: Point to the CDataframe
*/
void print_cdataframe(CDATAFRAME *cdf) {
    // Parcours du dataframe et affichage de chaque colonne
    lnode *current_node = get_first_node(cdf);
    //Parcours de tous les noeuds
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        printf("Column %s:\n", col->title);
        print_col(col);  // Appel à une fonction pour imprimer les valeurs de la colonne
        printf("\n");
        //On passe au noeud suivant
        current_node = get_next_node(cdf, current_node);
    }
}

/**
* @brief: afficher une partie du dataframe en fonction des indices de colonnes.
* @param1 : Point to the CDataframe
* @param2 : Indice de la première colonne à afficher
* @param3 : Indice de la dernière colonne à afficher
*/
void printcol_cdataframe(CDATAFRAME *cdf, int debut, int fin){
    if (debut<=0 || fin> nb_col(cdf) || debut>fin){
        printf("L'indice de debut ou l'indice de fin n'est pas correct\n");
        return;
    }
    // Parcours du dataframe et impression des colonnes dans la plage spécifiée
    lnode *current_node = get_first_node(cdf);
    int compteur = 1; //Compteur qui permet de savoir à quel colonne on est
    //Parcours de tous les noeuds
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        if(compteur >= debut && compteur <=fin) {
            printf("Column %s: \n",col->title);
            print_col(col); // Impression des valeurs de la colonne
            printf("\n");
        }
        compteur++;
        current_node = get_next_node(cdf, current_node);
    }
}

/**
 * @brief: Fonction pour imprimer une partie du dataframe en fonction des indices de lignes.
 * @param1: Pointeur vers le dataframe
 * @param2: Indice de la première ligne à imprime
 * @param3: Indice de la dernière ligne à imprimer
 */
void printlig_cdataframe(CDATAFRAME *cdf, int debut, int fin) {
    if(debut > fin || debut > nb_lig(cdf) || fin > nb_lig(cdf)){
        printf("L'indice de debut ou l'indice de fin n'est pas correct\n");
        return;
    }
    // Parcours du dataframe et impression des valeurs des lignes dans la plage spécifiée
    lnode *current_node = get_first_node(cdf);
    //Pour chaque ligne entre début et fin on parcourt tout les noeuds
    for(int i = debut; i<fin+1; i++){
        printf("ligne %d:\n",i);
        current_node = get_first_node(cdf);

        while (current_node != NULL) {
            COLUMN *col = current_node->data;

            char str[255];
            //On verifie que la fonction s'est éxécutée correctement
            if (convert_value(col, i-1, str, sizeof(str))!=-1) {
                printf("%s\n", str);
            }
            current_node = get_next_node(cdf, current_node);
        }

    }


}

/**
 * @brief: Ajoute une ligne au cdataframe.
 * @param1: Pointeur vers le dataframe
 */
void add_lig(CDATAFRAME *cdf){
    // Parcours du dataframe et ajout de valeurs à chaque colonne pour la nouvelle ligne
    lnode *current_node = get_first_node(cdf); // Obtient le premier nœud du dataframe
    while (current_node != NULL) {
        COLUMN *col = current_node->data; // Obtient les données de la colonne du nœud actuel
        printf("Quelle valeur souhaitez-vous ajouter z la colonne %s ligne %d : \n", col->title, col->size + 1);

        // Vérifie le type de colonne et insère la valeur correspondante
        switch (col->column_type) {
            case INT: {
                int value;
                // Vérifie si la valeur saisie est un entier
                if (scanf("%d", &value) == 1) {
                    int *ptr_value = &value; // Pointeur vers la valeur
                    insert_value(col, (void *) ptr_value); // Insère la valeur dans la colonne
                } else {
                    printf("La valeur que vous avez saisie ne correspond pas au meme type de valeur que la colonne\n");
                }
                fflush(stdin); // Vide le tampon d'entrée
                break;
            }
            case UINT: {
                unsigned int value;
                // Vérifie si la valeur saisie est un entier non signé
                if (scanf("%u", &value) == 1) {
                    unsigned int *ptr_value = &value; // Pointeur vers la valeur
                    insert_value(col, (void *) ptr_value); // Insère la valeur dans la colonne
                } else {
                    printf("La valeur que vous avez saisie ne correspond pas au meme type de valeur que la colonne\n");
                }
                fflush(stdin); // Vide le tampon d'entrée
                break;
            }
            case CHAR: {
                char value;
                // Vérifie si la valeur saisie est un caractère
                if (scanf("%c", &value) == 1) {
                    char *ptr_value = &value; // Pointeur vers la valeur
                    insert_value(col, (void *) ptr_value); // Insère la valeur dans la colonne
                } else {
                    printf("La valeur que vous avez saisie ne correspond pas au meme type de valeur que la colonne\n");
                }
                fflush(stdin); // Vide le tampon d'entrée
                break;
            }
            case FLOAT: {
                float value;
                // Vérifie si la valeur saisie est un flottant
                if (scanf("%f", &value) == 1) {
                    float *ptr_value = &value; // Pointeur vers la valeur
                    insert_value(col, (void *) ptr_value); // Insère la valeur dans la colonne
                } else {
                    printf("La valeur que vous avez saisie ne correspond pas au meme type de valeur que la colonne\n");
                }
                fflush(stdin); // Vide le tampon d'entrée
                break;
            }
            case DOUBLE: {
                double value;
                // Vérifie si la valeur saisie est un double
                if (scanf("%lf", &value) == 1) {
                    double *ptr_value = &value; // Pointeur vers la valeur
                    insert_value(col, (void *) ptr_value); // Insère la valeur dans la colonne
                } else {
                    printf("La valeur que vous avez saisie ne correspond pas au meme type de valeur que la colonne\n");
                }
                fflush(stdin); // Vide le tampon d'entrée
                break;
            }
            case STRING: {
                char value[120000];
                // Lit une chaîne de caractères
                scanf("%s", value);
                char *ptr_value = value; // Pointeur vers la valeur
                insert_value(col, (void *) ptr_value); // Insère la valeur dans la colonne
                fflush(stdin); // Vide le tampon d'entrée
                break;
            }
            default: {
                printf("Le format de la colonne est invalide");
                break;
            }
        }
        current_node = get_next_node(cdf, current_node); // Passe au nœud suivant du dataframe
    }
}


/**
 * @brief: Supprime une ligne du dataframe en utilisant son indice.
 * @param1: Pointeur vers le dataframe
 * @param2: Indice de la ligne à supprimer
 */
void del_lig(CDATAFRAME *cdf, int indice){
    if (indice<=0){
        printf("L'indice doit etre necessairemment strictement superieur a zero\n");
        return;
    }
    // Parcours du dataframe et suppression de la valeur à l'indice spécifié pour chaque colonne
    lnode *current_node = get_first_node(cdf);
    while (current_node != NULL) {
        COLUMN *col = current_node->data;

        col->data[indice-1]=NULL; //Suppression de la cellule
        free(col->data[indice-1]);



        current_node = get_next_node(cdf, current_node);

    }
}


/**
 * @brief: Ajoute une colonne au dataframe en demandant à l'utilisateur d'entrer les valeurs pour la nouvelle colonne.
 * @param1: Pointeur vers le dataframe
 * @param2: Type de la nouvelle colonne
 * @param3: Indice de la colonne à ajouter
 */
void add_col(CDATAFRAME *cdf, ENUM_TYPE coltype, int indice){
    if (indice<=0){
        printf("L'indice doit etre necessairemment strictement superieur a zero\n");
        return;
    }
    // Demande le nom de la nouvelle colonne
    char titre[1220000];
    printf("Quel sera le nom de la nouvelle colonne : \n");
    scanf("%s", titre); // Lit le nom de la colonne entré par l'utilisateur

    // Crée une nouvelle colonne avec le type et le nom spécifiés
    COLUMN *col = create_column(coltype, strdup(titre));

    // Demande à l'utilisateur d'entrer les valeurs pour la nouvelle colonne
    int nombre;
    printf("Combien de valeurs souhaitez-vous ajouter a la colonne %s:\n", col->title);
    scanf("%d", &nombre); // Lit le nombre de valeurs que l'utilisateur souhaite ajouter

    for (int i = 0; i < nombre; i++) {
        printf("Entrez une valeur pour la colonne %s:\n", col->title);

        // Vérifie le type de colonne et insère la valeur correspondante
        switch (col->column_type) {
            case INT: {
                int value;
                // Vérifie si la valeur saisie est un entier
                if (scanf("%d", &value) == 1) {
                    int *ptr_value = &value; // Pointeur vers la valeur
                    insert_value(col, (void *)ptr_value); // Insère la valeur dans la colonne
                } else {
                    printf("La valeur que vous avez saisie ne correspond pas au même type de valeur que la colonne\n");
                }
                fflush(stdin); // Vide le tampon d'entrée
                break;
            }
            case UINT: {
                unsigned int value;
                // Vérifie si la valeur saisie est un entier non signé
                if (scanf("%u", &value) == 1) {
                    unsigned int *ptr_value = &value; // Pointeur vers la valeur
                    insert_value(col, (void *)ptr_value); // Insère la valeur dans la colonne
                } else {
                    printf("La valeur que vous avez saisie ne correspond pas au même type de valeur que la colonne\n");
                }
                fflush(stdin); // Vide le tampon d'entrée
                break;
            }
            case CHAR: {
                char value;
                // Vérifie si la valeur saisie est un caractère
                if (scanf("%c", &value) == 1) {
                    char *ptr_value = &value; // Pointeur vers la valeur
                    insert_value(col, (void *)ptr_value); // Insère la valeur dans la colonne
                } else {
                    printf("La valeur que vous avez saisie ne correspond pas au même type de valeur que la colonne\n");
                }
                fflush(stdin); // Vide le tampon d'entrée
                break;
            }
            case FLOAT: {
                float value;
                // Vérifie si la valeur saisie est un flottant
                if (scanf("%f", &value) == 1) {
                    float *ptr_value = &value; // Pointeur vers la valeur
                    insert_value(col, (void *)ptr_value); // Insère la valeur dans la colonne
                }
                break;
            }
            case DOUBLE: {
                double value;
                // Vérifie si la valeur saisie est un double
                if (scanf("%lf", &value) == 1) {
                    double *ptr_value = &value; // Pointeur vers la valeur
                    insert_value(col, (void *)ptr_value); // Insère la valeur dans la colonne
                } else {
                    printf("La valeur que vous avez saisie ne correspond pas au même type de valeur que la colonne\n");
                }
                fflush(stdin); // Vide le tampon d'entrée
                break;
            }
            case STRING: {
                char value[120000];
                // Lit une chaîne de caractères
                if (scanf("%s", value) == 1) {
                    char *ptr_value = value; // Pointeur vers la valeur
                    insert_value(col, (void *)ptr_value); // Insère la valeur dans la colonne
                } else {
                    printf("La valeur que vous avez saisie ne correspond pas au même type de valeur que la colonne\n");
                }
                fflush(stdin); // Vide le tampon d'entrée
                break;
            }
            default: {
                printf("Le format de la colonne est invalide\n");
                break;
            }
        }
    }

    // Insère la nouvelle colonne à l'indice spécifié dans le dataframe
    lnode *current_node = get_first_node(cdf); // Obtient le premier nœud du dataframe
    lnode *noeud = lst_create_lnode(col); // Crée un nouveau nœud pour la colonne
    if (indice <= 1) {
        // Insère le nœud au début de la liste si l'indice est 1 ou inférieur
        lst_insert_head(cdf, noeud);
    } else {
        if (indice > col->size) {
            // Insère le nœud à la fin de la liste si l'indice est supérieur à la taille de la colonne
            lst_insert_tail(cdf, noeud);
        } else {
            // Parcourt la liste jusqu'à l'indice spécifié et insère le nœud après le nœud actuel
            for (int i = 0; i < indice - 2; i++) {
                current_node = get_next_node(cdf, current_node);
            }
            lst_insert_after(cdf, noeud, current_node);
        }
    }
}




/**
 * @brief: Supprime une colonne du dataframe en utilisant son indice.
 * @param1: Pointeur vers le dataframe
 * @param2: Indice de la colonne à supprimer
 */
void del_col_indice(CDATAFRAME *cdf, int indice){
    if (indice<=0 || indice > nb_col(cdf)){
        printf("L'indice doit etre necessairemment strictement superieur a zero et inferieur au nombre de colonne\n");
        return;
    }
    lnode *current_node = get_first_node(cdf);
    // Parcours du dataframe jusqu'à l'indice de la colonne à supprimer
    for (int i = 0; i<indice-1; i++) {
        current_node = get_next_node(cdf,current_node);
    }
    // Suppression de la colonne à l'indice spécifié
    lst_delete_lnode(cdf, current_node);

}


/**
 * @brief: Renomme une colonne du dataframe en utilisant son indice.
 * @param1: Pointeur vers le dataframe
 * @param2: Indice de la colonne à renommer
 */
void rename_col(CDATAFRAME *cdf, int indice){
    if (indice<=0 || indice > nb_col(cdf)){
        printf("L'indice doit etre necessairemment strictement superieur a zero et inferieur au nombre de colonne\n");
        return;
    }

    lnode *current_node = get_first_node(cdf);

    // Parcours du dataframe jusqu'à l'indice de la colonne à renommer

    for (int i = 0; i < indice - 1; i++) {
        current_node = get_next_node(cdf, current_node);
    }
    // Obtention de la colonne à renommer
    COLUMN *col = current_node->data;


    char titre[1220000];
    // Demande du nouveau nom pour la colonne
    printf("Quel sera le nouveau nom de la colonne %d ? :\n", indice);
    scanf("%s", titre);
    // Attribution du nouveau nom à la colonne
    col->title = strdup(titre);



}


/**
 * @brief: Vérifie si une valeur est présente dans le dataframe et affiche la colonne correspondante.
 * @param1: Pointeur vers le dataframe
 * @param2: Valeur à rechercher
 */
void is_in_cdataframe(CDATAFRAME *cdf,void* x){
    lnode *current_node = get_first_node(cdf);
    // Parcours du dataframe
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        // Vérification du nombre d'occurrences de la valeur dans la colonne
        if (nb_occurence(col,x)>=1){
            printf("La valeur se trouve dans le cdataframe a la colonne %s\n",col->title);
        }
        //On passe au noeud suivant
        current_node = get_next_node(cdf, current_node);

    }
}


/**
 * @brief: Affiche les noms des colonnes du dataframe.
 * @param1: Pointeur vers le dataframe
 */
void print_column_name(CDATAFRAME *cdf){
    lnode *current_node = get_first_node(cdf);
    printf("Le nom des colonnes :\n");
    // Parcours du dataframe et affichage des noms de colonnes
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        printf("\t%s\n",col->title);
        //On passe au noeud suivant
        current_node = get_next_node(cdf, current_node);

    }

}


/**
 * @brief: Compte le nombre de colonnes dans le dataframe.
 * @param1: Pointeur vers le dataframe
 * @return: Nombre de colonnes dans le dataframe
 */
int nb_col(CDATAFRAME *cdf){
    lnode *current_node = get_first_node(cdf);
    int compteur = 0;
    // Parcours du dataframe et comptage des colonnes
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        compteur++; //Pour chaque noeud on incrémente de 1 le compteur
        //On passe au noeud suivant
        current_node = get_next_node(cdf, current_node);
    }
    return compteur;

}


/**
 * @brief: Compte le nombre de lignes dans le dataframe.
 * @param1: Pointeur vers le dataframe
 * @return: Nombre maximal de lignes dans le dataframe
 */
int nb_lig(CDATAFRAME *cdf){
    lnode *current_node = get_first_node(cdf);
    int max = 0;
    // Parcours du dataframe et recherche du nombre maximal de lignes
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        if(col->size>max){
            max = col->size; //Si jamais on trouve une colonne plus grande on change la valeur de max
        }
        //On pass au noeud suivant
        current_node = get_next_node(cdf, current_node);
    }
    return max;

}


/**
 * @brief: Compte le nombre de cellules égales à une valeur donnée dans le dataframe.
 * @param1: Pointeur vers le dataframe
 * @param2: Valeur à comparer
 */
void nb_equal_to(CDATAFRAME *cdf, void* x){
    lnode *current_node = get_first_node(cdf);
    int nb = 0;
    // Parcours du dataframe et comptage des occurrences de la valeur dans les colonnes
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        nb+= nb_occurence(col,x); //On appel nb_occurence pour compter le bombre d'occurences de x dans la colonne
        //On passe au noeud suivant
        current_node = get_next_node(cdf, current_node);
    }
    printf("Il y a %d celulles egale(s) a x\n",nb);

}


/**
 * @brief: Compte le nombre de cellules supérieures à une valeur donnée dans le dataframe.
 * @param1: Pointeur vers le dataframe
 * @param2: Valeur à comparer
 */
void nb_superior_to(CDATAFRAME *cdf, void* x){
    lnode *current_node = get_first_node(cdf);
    int nb = 0;
    // Parcours de tous les noeuds
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        nb+= nb_value_superior(col,x); //on réutilise la fonction déjà codé et on incrémente nb
        //On passe au noeud suivant
        current_node = get_next_node(cdf, current_node);
    }
    printf("Il y a %d celulles superieure(s) a x\n",nb);

}

/**
 * @brief: Compte le nombre de cellules inférieures à une valeur donnée dans le dataframe.
 * @param1: Pointeur vers le dataframe
 * @param2: Valeur à comparer
 */
void nb_inferior_to(CDATAFRAME *cdf, void* x){
    lnode *current_node = get_first_node(cdf);
    int nb = 0;
    // Parcours de tous les noeuds
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        nb+= nb_value_inferior(col,x); //on réutilise la fonction déjà codé et on incrémente nb
        //On passe au noeud suivant
        current_node = get_next_node(cdf, current_node);
    }
    printf("Il y a %d celulles inferieure(s) a x\n",nb);
}



/**
 * @brief: Remplace la valeur d'une cellule dans le dataframe.
 * @param1: Pointeur vers le dataframe
 * @param2: Nouvelle valeur
 * @param3: Indice de la colonne
 * @param4: Indice de la ligne
 */
void replace_value_cdataframe(CDATAFRAME *cdf, void* value, int indice_col, int indice_lig){
    lnode *current_node = get_first_node(cdf);
    // Vérification de l'indice de la colonne par rapport au nombre de colonnes dans le dataframe
    if (indice_lig <= 0 || indice_col <= 0){
        printf("Les indices des lignes colonnes rentres sont invalides\n");
        return;
    }
    //Si l'indice est supérieur au nombre de colonne on ajoute une colonne
    if (indice_col>nb_col(cdf)){
        int type;

        printf("Veuillez indiquez le type de la valeur en indiquant son numero : (1 = INT, 2 = UINT, 3 = CHAR, 4 = FLOAT, 5 = DOUBLE, 6 = STRING \n");
        scanf("%d",&type);
        switch (type) {
            case 1: {
                char titre[1220000];
                printf("Quel sera le nom de la nouvelle colonne : \n");
                scanf("%s",titre);
                COLUMN* col = create_column(INT, strdup(titre));

                //On affecte à NULL les cellules jusqu'à l'indice de ligne
                for(int i = 0; i<indice_lig-1;i++){
                    insert_value(col,NULL);
                }
                //Puis on insert notre value
                insert_value(col,value);

                lnode* noeud = lst_create_lnode(col);
                lst_insert_tail(cdf,noeud);

                //On réactualise si nécessaire la taille de notre colonne
                if (col->size<indice_lig){
                    col->size = indice_lig;
                }
                break;

            }
            case 2: {
                char titre[1220000];
                printf("Quel sera le nom de la nouvelle colonne : \n");
                scanf("%s",titre);
                COLUMN* col = create_column(UINT, strdup(titre));

                //On affecte à NULL les cellules jusqu'à l'indice de ligne
                for(int i = 0; i<indice_lig-1;i++){
                    insert_value(col,NULL);
                }
                //Puis on insert notre value
                insert_value(col,value);

                lnode* noeud = lst_create_lnode(col);
                lst_insert_tail(cdf,noeud);
                //On réactualise si nécessaire la taille de notre colonne
                if (col->size<indice_lig){
                    col->size = indice_lig;
                }
                break;

            }
            case 3: {
                char titre[1220000];
                printf("Quel sera le nom de la nouvelle colonne : \n");
                scanf("%s",titre);
                COLUMN* col = create_column(CHAR, strdup(titre));

                //On affecte à NULL les cellules jusqu'à l'indice de ligne
                for(int i = 0; i<indice_lig-1;i++){
                    insert_value(col,NULL);
                }
                //Puis on insert notre value
                insert_value(col,value);

                lnode* noeud = lst_create_lnode(col);
                lst_insert_tail(cdf,noeud);
                //On réactualise si nécessaire la taille de notre colonne
                if (col->size<indice_lig){
                    col->size = indice_lig;
                }
                break;

            }
            case 4: {
                char titre[1220000];
                printf("Quel sera le nom de la nouvelle colonne : \n");
                scanf("%s",titre);
                COLUMN* col = create_column(FLOAT, strdup(titre));

                //On affecte à NULL les cellules jusqu'à l'indice de ligne
                for(int i = 0; i<indice_lig-1;i++){
                    insert_value(col,NULL);
                }
                //Puis on insert notre value
                insert_value(col,value);

                lnode* noeud = lst_create_lnode(col);
                lst_insert_tail(cdf,noeud);
                //On réactualise si nécessaire la taille de notre colonne
                if (col->size<indice_lig){
                    col->size = indice_lig;
                }
                break;

            }
            case 5: {
                char titre[1220000];
                printf("Quel sera le nom de la nouvelle colonne : \n");
                scanf("%s",titre);
                COLUMN* col = create_column(DOUBLE, strdup(titre));

                //On affecte à NULL les cellules jusqu'à l'indice de ligne
                for(int i = 0; i<indice_lig-1;i++){
                    insert_value(col,NULL);
                }
                //Puis on insert notre value
                insert_value(col,value);

                lnode* noeud = lst_create_lnode(col);
                lst_insert_tail(cdf,noeud);
                //On réactualise si nécessaire la taille de notre colonne
                if (col->size<indice_lig){
                    col->size = indice_lig;
                }
                break;

            }
            case 6: {
                char titre[1220000];
                printf("Quel sera le nom de la nouvelle colonne : \n");
                scanf("%s",titre);
                COLUMN* col = create_column(STRING, strdup(titre));

                //On affecte à NULL les cellules jusqu'à l'indice de ligne
                for(int i = 0; i<indice_lig-1;i++){
                    insert_value(col,NULL);
                }
                //Puis on insert notre value
                insert_value(col,value);

                lnode* noeud = lst_create_lnode(col);
                lst_insert_tail(cdf,noeud);
                //On réactualise si nécessaire la taille de notre colonne
                if (col->size<indice_lig){
                    col->size = indice_lig;
                }
                break;

            }

        }
    }

    else {
        // Parcours du dataframe jusqu'à la colonne spécifiée
        for (int i = 1; i < indice_col; i++) {
            current_node = get_next_node(cdf, current_node);

        }
        COLUMN *col = current_node->data;
        // Vérification de l'indice de ligne par rapport à la taille maximale de la colonne

        if (col == NULL) {
            printf("Colonne invalide.\n");
            return;
        }


        //On affecte à NULL les cellules entre celle déjà affectées et l'indice de ligne
        for(int i = col->size; i<indice_lig-1;i++){

            insert_value(col,NULL);
        }

        // Si la cellule est déjà occupée par une autre valeur
        if (indice_lig<=col->size){
            switch(col->column_type) {
                case INT: {
                    //On verifie que la valeur soit différente de NULL
                    if (value!=NULL){



                        *((int*)col->data[indice_lig]) = *((int*)value);

                    }
                    else{

                        col->data[indice_lig] = NULL;

                    }

                    break;
                }
                case UINT: {
                    //On verifie que la valeur soit différente de NULL
                    if (value!=NULL){


                        *((unsigned int*)col->data[indice_lig]) = *((unsigned int*)value);

                    }
                    else{
                        col->data[indice_lig] = NULL;

                    }

                    break;
                }
                case CHAR: {
                    //On verifie que la valeur soit différente de NULL
                    if (value!=NULL){


                        *((char*)col->data[indice_lig]) = *((char*)value);

                    }
                    else{
                        col->data[indice_lig] = NULL;

                    }

                    break;
                }
                case FLOAT: {
                    //On verifie que la valeur soit différente de NULL
                    if (value!=NULL){


                        *((float*)col->data[indice_lig]) = *((float*)value);

                    }
                    else{
                        col->data[indice_lig] = NULL;

                    }

                    break;
                }
                case DOUBLE: {
                    //On verifie que la valeur soit différente de NULL
                    if (value!=NULL){


                        *((double*)col->data[indice_lig]) = *((double*)value);

                    }
                    else{
                        col->data[indice_lig] = NULL;

                    }

                    break;
                }
                case STRING: {
                    //On verifie que la valeur soit différente de NULL
                    if (value!=NULL) {


                        strcpy((char *) col->data[indice_lig], (char *) value);

                    }
                    else{
                        col->data[indice_lig] = NULL;

                    }
                    break;

                }


                default:
                    printf("Le format de la colonne est invalide");
                    break;
            }
        }
        else
            //Si la cellule n'est pas déjà occupé par une autre valeur
            insert_value(col,value);
        // Mise à jour de la taille de la colonne si nécessaire
        if (col->size<indice_lig){
            col->size = indice_lig;
        }
    }




}


/* Les deux fonctions suivantes se situe dans la partie 3 experte mais comme nous les avons faîtes nous les avons quand même misent*/


/**
 * @brief: Charge les données d'un fichier CSV dans le dataframe.
 * @param1: Nom du fichier CSV
 * @param2: Tableau des types de données des colonnes
 * @param3: Nombre de colonnes
 * @return: Pointeur vers le dataframe contenant les données chargées
 */
CDATAFRAME* load_from_csv(char* name, ENUM_TYPE *cdftype, int size) {
    FILE* file;
    // Création du dataframe
    CDATAFRAME *cdf = create_cdataframe(cdftype, size);
    char line[1000];

    // Ouvre le fichier CSV en mode lecture
    file = fopen(name, "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return cdf;
    }

    // Initialisation des indices de colonne et de ligne
    int colonne = 1;
    int ligne = 1;
    char str[255];

    // Lecture du fichier ligne par ligne
    while (fgets(line, sizeof(line), file) != NULL) {
        // Découpage de la ligne en tokens séparés par des points-virgules
        char *token = strtok(line, ";");
        colonne = 0;

        // Parcours des tokens pour chaque colonne
        for (int i = 0; i < size; i++) {
            colonne++;
            COLUMN *col = get_first_node(cdf)->data;
            printf("%s\n",token);
            // Conversion du token en fonction du type de données de la colonne
            if(token != NULL && strcmp(token, "\n") != 0) {
                switch (cdftype[colonne - 1]) {

                    case INT: {
                        int current = atoi(token);  // Conversion en entier
                        void *ptr = &current;
                        replace_value_cdataframe(cdf, ptr, colonne, ligne);  // Remplace la valeur dans le dataframe
                        break;
                    }
                    case UINT: {
                        unsigned int current = (unsigned int) strtoul(token, NULL,
                                                                      10);  // Conversion en entier non signé
                        void *ptr = &current;
                        replace_value_cdataframe(cdf, ptr, colonne, ligne);  // Remplace la valeur dans le dataframe
                        break;
                    }
                    case CHAR: {
                        char current = token[0];  // Conversion en caractère
                        void *ptr = &current;
                        replace_value_cdataframe(cdf, ptr, colonne, ligne);  // Remplace la valeur dans le dataframe
                        break;
                    }
                    case FLOAT: {
                        float current = strtof(token, NULL);  // Conversion en flottant
                        void *ptr = &current;
                        replace_value_cdataframe(cdf, ptr, colonne, ligne);  // Remplace la valeur dans le dataframe
                        break;
                    }
                    case DOUBLE: {

                        double current = atof(token);  // Conversion en double
                        void *ptr = &current;
                        replace_value_cdataframe(cdf, ptr, colonne, ligne);  // Remplace la valeur dans le dataframe
                        break;
                    }
                    case STRING: {
                        replace_value_cdataframe(cdf, token, colonne, ligne);  // Remplace la valeur dans le dataframe
                        break;
                    }
                }
            }
            // Passe au token suivant
            token = strtok(NULL, ";");
        }
        ligne++;  // Passe à la ligne suivante
    }

    // Ferme le fichier
    fclose(file);

    // Retourne le dataframe rempli
    return cdf;
}


/**
 * @brief: Exporte les données du dataframe dans un fichier CSV.
 * @param1: Nom du fichier CSV de destination
 * @param2: Pointeur vers le dataframe à exporter
 */
void export_cdataframe(char* name, CDATAFRAME* cdf){
    FILE* file = NULL;
    // Ouverture du fichier en mode écriture
    file = fopen(name, "w");

    // Vérification de l'ouverture du fichier
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }


    char str[255];
    // Écriture des noms de colonnes dans le fichier CSV
    lnode* current_node = get_first_node(cdf);
    while (current_node != NULL){
        COLUMN *col = current_node->data;
        // Écrire le nom de la colonne dans le fichier
        fputs(col->title, file);
        if(current_node!= get_last_node(cdf)){
            // Ajouter un point-virgule après chaque nom de colonne sauf le dernier
            fputs(";", file);
        }

        current_node = get_next_node(cdf,current_node);
    }
    // Ajouter un saut de ligne après la ligne des noms de colonnes
    fputs("\n", file);


    // Écriture des données de chaque ligne dans le fichier CSV
    for(int i = 0; i< nb_lig(cdf); i++){

        lnode* current_node = get_first_node(cdf);

        while (current_node != NULL){
            COLUMN *col = current_node->data;
            // Convertir la valeur de la cellule en chaîne de caractères et verifier que ça à bien été fait
            if (convert_value(col,i,str,sizeof(str))!=-1) {
                // Écrire la valeur dans le fichier
                fputs(str, file);
                if (current_node != get_last_node(cdf)) {
                    // Ajouter un point-virgule après chaque valeur sauf la dernière
                    fputs(";", file);
                }
            }
            //On passe au noeud suivant
            current_node = get_next_node(cdf,current_node);
        }
        // Ajouter un saut de ligne après chaque ligne de données
        fputs("\n", file);
    }


    // Fermeture du fichier
    fclose(file);

}