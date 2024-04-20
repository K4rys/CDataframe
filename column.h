//
// Created by natha on 20/04/2024.
//

#ifndef CDATAFRAME_COLUMN_H
#define CDATAFRAME_COLUMN_H

#define REALOC_SIZE 256

typedef struct {
    char *titre;
    int taille_physique;
    int taille_logique;
    int *donnees;

} COLUMN;

COLUMN *create_COLUMN(char* title);
int insererValeur(COLUMN *col, int value);
void delete_COLUMN(COLUMN **col);
void print_col(COLUMN* col);
int nbOccurrences(COLUMN *col, int x);
int valeurALaPosition(const COLUMN *col, int x);
int nbValeursSuperieures(const COLUMN *col, int x);
int nbValeursInferieures(const COLUMN *col, int x);
int nbValeursEgales(const COLUMN *col, int x);



#endif //CDATAFRAME_COLUMN_H
