
#include "CDataframe.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



// Crée un nouveau dataframe en demandant les noms des colonnes à l'utilisateur
// et en utilisant les types de colonnes spécifiés dans le tableau cdftype.
// @param cdftype: Tableau des types de colonnes
// @param size: Taille du tableau
// @return: Pointeur vers le nouveau dataframe
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
    return lst; // Retourne le dataframe sous forme de liste
}

// Supprime un dataframe en supprimant toutes ses colonnes et la liste associée.
// @param cdf: Pointeur vers le dataframe à supprimer
void delete_cdataframe(CDATAFRAME **cdf){
    // Parcours et suppression de chaque colonne du dataframe
    lnode* first_node = get_first_node((*cdf));
    lnode* current_node = first_node;
    while (current_node != get_last_node((*cdf))){
        delete_column(current_node->data);
        current_node = get_next_node((*cdf),current_node);
    }
    lst_erase((*cdf)); // Suppression de la liste
}

// Supprime une colonne du dataframe en utilisant son nom.
// @param cdf: Pointeur vers le dataframe
// @param col_name: Nom de la colonne à supprimer
void delete_column_in_cdataframe(CDATAFRAME *cdf, char *col_name){
    // Parcours du dataframe pour trouver la colonne avec le nom spécifié
    lnode* first_node = get_first_node(cdf);
    lnode* current_node = first_node;
    while (current_node != get_last_node(cdf)){
        COLUMN* column = current_node->data;
        if(strcmp(column->title,col_name)==0){
            delete_column(&column); // Suppression de la colonne
            current_node->data = NULL;
        }
        current_node = get_next_node(cdf,current_node);
    }
}

// Obtenir le nombre de colonnes dans le dataframe.
// @param cdf: Pointeur vers le dataframe
// @return: Nombre de colonnes dans le dataframe
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

// Remplit le dataframe en demandant à l'utilisateur d'entrer les valeurs pour chaque colonne.
// @param cdf: Pointeur vers le dataframe
void fill_cdataframe_user(CDATAFRAME *cdf) {
    lnode *current_node = get_first_node(cdf);
    
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

    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        int nombre;
        printf("Combien de valeurs souhaitez vous ajouter a la colonne %s:\n",col->title);
        scanf("%d",&nombre);
        for(int i = 0; i<nombre; i++) {
            printf("Enter values for column %s:\n", col->title);
            // Logique pour ajouter des valeurs à la colonne en fonction de son type
            // ...
        }
        current_node = get_next_node(cdf, current_node);
    }
}

// Fonction pour afficher le dataframe.
// @param cdf: Pointeur vers le dataframe
void print_cdataframe(CDATAFRAME *cdf) {
    // Parcours du dataframe et affichage de chaque colonne
    lnode *current_node = get_first_node(cdf);
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        printf("Column %s:\n", col->title);
        print_col(col); // Appel à une fonction pour imprimer les valeurs de la colonne
        printf("\n");
        current_node = get_next_node(cdf, current_node);
    }
}

// Fonction pour imprimer une partie du dataframe en fonction des indices de colonnes.
// @param cdf: Pointeur vers le dataframe
// @param debut: Indice de la première colonne à imprimer
// @param fin: Indice de la dernière colonne à imprimer
void printcol_cdataframe(CDATAFRAME *cdf, int debut, int fin){
    // Parcours du dataframe et impression des colonnes dans la plage spécifiée
    lnode *current_node = get_first_node(cdf);
    int compteur = 1;
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        if(compteur >= debut && compteur <=fin) {
            print_col(col); // Impression des valeurs de la colonne
        }
        compteur++;
        current_node = get_next_node(cdf, current_node);
    }
}

// Fonction pour imprimer une partie du dataframe en fonction des indices de lignes.
// @param cdf: Pointeur vers le dataframe
// @param debut: Indice de la première ligne à imprimer
// @param fin: Indice de la dernière ligne à imprimer
void printlig_cdataframe(CDATAFRAME *cdf, int debut, int fin) {
    // Parcours du dataframe et impression des valeurs des lignes dans la plage spécifiée
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

// Ajoute une ligne au dataframe en demandant à l'utilisateur d'entrer les valeurs pour chaque colonne.
// @param cdf: Pointeur vers le dataframe
void add_lig(CDATAFRAME *cdf){
    // Parcours du dataframe et ajout de valeurs à chaque colonne pour la nouvelle ligne
    lnode *current_node = get_first_node(cdf);
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        printf("Quel valeur souhaitez vous ajouter a colonne %s ligne %d : \n",col->title,col->size+1);
        // Logique pour ajouter une valeur à la colonne en fonction de son type
        // ...
        current_node = get_next_node(cdf, current_node);
    }
}

// Supprime une ligne du dataframe en utilisant son indice.
// @param cdf: Pointeur vers le dataframe
// @param indice: Indice de la ligne à supprimer
void del_lig(CDATAFRAME *cdf, int indice){
    // Parcours du dataframe et suppression de la valeur à l'indice spécifié pour chaque colonne
    lnode *current_node = get_first_node(cdf);
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        col->data[indice-1]=NULL;
        free(col->data[indice-1]);
        current_node = get_next_node(cdf, current_node);
    }
}

// Ajoute une colonne au dataframe en demandant à l'utilisateur d'entrer les valeurs pour la nouvelle colonne.
// @param cdf: Pointeur vers le dataframe
// @param coltype: Type de la nouvelle colonne
// @param indice: Indice de la colonne à ajouter
void add_col(CDATAFRAME *cdf, ENUM_TYPE coltype, int indice){
    // Demande le nom de la nouvelle colonne
    char titre[1220000];
    printf("Quel sera le nom de la nouvelle colonne : \n");
    scanf("%s",titre);
    COLUMN* col = create_column(coltype, strdup(titre));

    // Demande à l'utilisateur d'entrer les valeurs pour la nouvelle colonne
    int nombre;
    printf("Combien de valeurs souhaitez vous ajouter a la colonne %s:\n",col->title);
    scanf("%d",&nombre);
    for(int i = 0; i<nombre; i++) {
        printf("Enter values for column %s:\n", col->title);
        // Logique pour ajouter une valeur à la colonne en fonction de son type
        // ...
    }

    // Insère la nouvelle colonne à l'indice spécifié dans le dataframe
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

// Supprime une colonne du dataframe en utilisant son indice.
// @param cdf: Pointeur vers le dataframe
// @param indice: Indice de la colonne à supprimer
void del_col(CDATAFRAME *cdf, int indice){
    lnode *current_node = get_first_node(cdf);
    // Parcours du dataframe jusqu'à l'indice de la colonne à supprimer
    for (int i = 0; i < indice - 2; i++) {
        current_node = get_next_node(cdf,current_node);
    }
    // Suppression de la colonne à l'indice spécifié
    lst_delete_lnode(cdf, current_node);
}

// Renomme une colonne du dataframe en utilisant son indice.
// @param cdf: Pointeur vers le dataframe
// @param indice: Indice de la colonne à renommer
void rename_col(CDATAFRAME *cdf, int indice){
    lnode *current_node = get_first_node(cdf);
    // Parcours du dataframe jusqu'à l'indice de la colonne à renommer
    for (int i = 0; i < indice - 1; i++) {
        current_node = get_next_node(cdf,current_node);
    }
    // Obtention de la colonne à renommer
    COLUMN *col = current_node->data;
    char titre[1220000];
    // Demande du nouveau nom pour la colonne
    printf("Quel sera le nouveau nom de la colonne %d ? :\n",indice);
    scanf("%s",titre);
    // Attribution du nouveau nom à la colonne
    col->title = strdup(titre);
}

// Vérifie si une valeur est présente dans le dataframe et affiche la colonne correspondante.
// @param cdf: Pointeur vers le dataframe
// @param x: Valeur à rechercher
void is_in_cdataframe(CDATAFRAME *cdf,void* x){
    lnode *current_node = get_first_node(cdf);
    // Parcours du dataframe
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        // Vérification du nombre d'occurrences de la valeur dans la colonne
        if (nb_occurence(col,x)>=1){
            printf("La valeur se trouve dans le cdataframe a la colonne %s\n",col->title);
        }
        current_node = get_next_node(cdf, current_node);
    }
}

// Affiche les noms des colonnes du dataframe.
// @param cdf: Pointeur vers le dataframe
void print_column_name(CDATAFRAME *cdf){
    lnode *current_node = get_first_node(cdf);
    printf("Le nom des colonnes :\n");
    // Parcours du dataframe et affichage des noms de colonnes
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        printf("\t%s\n",col->title);
        current_node = get_next_node(cdf, current_node);
    }
}

// Compte le nombre de colonnes dans le dataframe.
// @param cdf: Pointeur vers le dataframe
// @return: Nombre de colonnes dans le dataframe
int nb_col(CDATAFRAME *cdf){
    lnode *current_node = get_first_node(cdf);
    int compteur = 0;
    // Parcours du dataframe et comptage des colonnes
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        compteur++;
        current_node = get_next_node(cdf, current_node);
    }
    return compteur;
}

// Compte le nombre maximal de lignes dans le dataframe.
// @param cdf: Pointeur vers le dataframe
// @return: Nombre maximal de lignes dans le dataframe
int nb_lig(CDATAFRAME *cdf){
    lnode *current_node = get_first_node(cdf);
    int max = 0;
    // Parcours du dataframe et recherche du nombre maximal de lignes
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        if(col->size > max){
            max = col->size;
        }
        current_node = get_next_node(cdf, current_node);
    }
    return max;
}

// Compte le nombre de cellules égales à une valeur donnée dans le dataframe.
// @param cdf: Pointeur vers le dataframe
// @param x: Valeur à comparer
void nb_equal_to(CDATAFRAME *cdf, void* x){
    lnode *current_node = get_first_node(cdf);
    int nb = 0;
    // Parcours du dataframe et comptage des occurrences de la valeur dans les colonnes
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        nb += nb_occurence(col,x);
        current_node = get_next_node(cdf, current_node);
    }
    printf("Il y a %d cellules égales à x", nb);
}

// Compte le nombre de cellules supérieures à une valeur donnée dans le dataframe.
// @param cdf: Pointeur vers le dataframe
// @param x: Valeur à comparer
void nb_superior_to(CDATAFRAME *cdf, void* x){
    lnode *current_node = get_first_node(cdf);
    int nb = 0;
    // Parcours du dataframe et comptage des valeurs supérieures à x dans les colonnes
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        nb += nb_value_superior(col,x);
        current_node = get_next_node(cdf, current_node);
    }
    printf("Il y a %d cellules supérieures à x", nb);
}

// Compte le nombre de cellules inférieures à une valeur donnée dans le dataframe.
// @param cdf: Pointeur vers le dataframe
// @param x: Valeur à comparer
void nb_inferior_to(CDATAFRAME *cdf, void* x){
    lnode *current_node = get_first_node(cdf);
    int nb = 0;
    // Parcours du dataframe et comptage des valeurs inférieures à x dans les colonnes
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        nb += nb_value_inferior(col,x);
        current_node = get_next_node(cdf, current_node);
    }
    printf("Il y a %d cellules inférieures à x", nb);
}

// Remplace la valeur d'une cellule dans le dataframe.
// @param cdf: Pointeur vers le dataframe
// @param value: Nouvelle valeur
// @param indice_col: Indice de la colonne
// @param indice_lig: Indice de la ligne
void replace_value_cdataframe(CDATAFRAME *cdf, void* value, int indice_col, int indice_lig){
    lnode *current_node = get_first_node(cdf);
    // Vérification de l'indice de la colonne par rapport au nombre de colonnes dans le dataframe
    if (indice_col > nb_col(cdf)){
        printf("Indice colonne : %d nb col : %d\n",indice_col, nb_col(cdf));
        return;
    }
    // Parcours du dataframe jusqu'à la colonne spécifiée
    for (int i = 1; i < indice_col; i++) {
        current_node = get_next_node(cdf,current_node);
    }
    COLUMN *col = current_node->data;
    // Vérification de l'indice de ligne par rapport à la taille maximale de la colonne
    if (indice_lig >= col->max_size) {
        // Réallocation de mémoire si nécessaire pour la colonne
        if (col->max_size == 0) {
            col->data = malloc(REALOC_SIZE * sizeof(int));
            col->max_size = 256;
        } else {
            col->max_size += REALOC_SIZE;
            col->data = realloc(col->data, col->max_size * sizeof(int));
        }
        // Vérification de la réussite de la réallocation de mémoire
        if (col->data == NULL) {
            printf("Échec de l'allocation mémoire.\n");
            return;
        }
    }
    // Attribution de la nouvelle valeur à la cellule spécifiée
    switch(col->column_type) {
        case INT: {
            // Allocation de mémoire pour la nouvelle valeur
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
    // Mise à jour de la taille de la colonne si nécessaire
    if (col->size < indice_lig){
        col->size = indice_lig;
    }
}

// Charge les données d'un fichier CSV dans le dataframe.
// @param name: Nom du fichier CSV
// @param cdftype: Tableau des types de données des colonnes
// @param size: Nombre de colonnes
// @return: Pointeur vers le dataframe contenant les données chargées
CDATAFRAME* load_from_csv(char* name, ENUM_TYPE *cdftype, int size) {
    FILE* file;
    // Création du dataframe
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
    // Lecture du fichier ligne par ligne
    while (fgets(line, sizeof(line), file) != NULL) {
        // Découpage de la ligne en tokens séparés par des points-virgules
        char *token = strtok(line, ";");
        colonne = 0;
        // Parcours des tokens pour chaque colonne
        for (int i =0; i<size;i++){
            colonne++;
            COLUMN *col = get_first_node(cdf)->data;
            // Conversion du token en fonction du type de données de la colonne
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

// Exporte les données du dataframe dans un fichier CSV.
// @param name: Nom du fichier CSV de destination
// @param cdf: Pointeur vers le dataframe à exporter
void export_cdataframe(char* name, CDATAFRAME* cdf){
    FILE* file = NULL;
    file = fopen(name, "w");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }
    char str[255];
    // Écriture des noms de colonnes dans le fichier CSV
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
    // Écriture des données de chaque ligne dans le fichier CSV
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
