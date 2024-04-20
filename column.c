//
// Created by natha on 20/04/2024.
//

#include "column.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>




// Fonction pour créer une colonne vide
COLUMN* create_COLUMN(char *title) {

    COLUMN *col = malloc(sizeof(COLUMN));

    if (col == NULL) {
        printf("Colonne invalide.\n");
        return NULL;
    }

    col->titre = title;
    col->donnees = NULL;
    col->taille_physique = 0;
    col->taille_logique = 0;

    return col;
}

// Fonction pour insérer une valeur dans une COLUMN
int insererValeur(COLUMN *col, int value) {

    if (col == NULL) {
        printf("Colonne invalide.\n");
        return 0;
    }

    if (col->taille_physique == 0){
        col->donnees = (int*) malloc(REALOC_SIZE*sizeof(int));
    }

    if (col->taille_logique >= col->taille_physique) {
        col->taille_physique += REALOC_SIZE;
        col->donnees = realloc(col->donnees, col->taille_physique * sizeof(int));

        if (col->donnees == NULL) {
            return 0;
        }
    }

    col->donnees[col->taille_logique++] = value;

    return 1;
}

// Fonction pour libérer la mémoire allouée pour une colonnne
void delete_COLUMN(COLUMN **col) {

    if (*col == NULL) {
        printf("Colonne invalide.\n");
        return;
    }

    free((*col)->titre);
    free((*col)->donnees);
    free((*col));
    *col = NULL;
}

// Fonction pour afficher le contenu d'une COLUMN
void print_col(COLUMN* col){

    if (col == NULL) {
        printf("Colonne invalide.\n");
        return;
    }

    for (int i = 0; i < col->taille_logique; i++) {
        printf("[%d]\t%d\n", i, col->donnees[i]);
    }
}

// Retourner le nombre d'occurrences d'une valeur x dans la COLUMN
int nbOccurrences(COLUMN *col, int x) {

    if (col == NULL || col->donnees == NULL) {
        return -1;
    }

    int occurrences = 0;

    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] == x) {
            occurrences++;
        }
    }

    return occurrences;
}

// Retourner la valeur présente à la position x dans la COLUMN
int valeurALaPosition(const COLUMN *col, int x) {

    if (col == NULL || col->donnees == NULL || x < 0 || x >= col->taille_logique) {
        return -1;
    }

    return col->donnees[x];
}

// Retourner le nombre de valeurs supérieures à x dans la COLUMN
int nbValeursSuperieures(const COLUMN *col, int x) {

    if (col == NULL || col->donnees == NULL) {
        return -1;
    }

    int nbSuperieures = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] > x) {
            nbSuperieures++;
        }
    }

    return nbSuperieures;
}

// Retourner le nombre de valeurs inférieures à x dans la COLUMN
int nbValeursInferieures(const COLUMN *col, int x) {
    if (col == NULL || col->donnees == NULL) {
        return -1;
    }

    int nbInferieures = 0;

    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] < x) {
            nbInferieures++;
        }
    }

    return nbInferieures;
}

// Retourner le nombre de valeurs égales à x dans la COLUMN
int nbValeursEgales(const COLUMN *col, int x) {

    if (col == NULL || col->donnees == NULL) {
        return -1;
    }

    int nbEgales = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] == x) {
            nbEgales++;
        }
    }

    return nbEgales;
}


