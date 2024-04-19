#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour représenter une colonne
typedef struct {
    char *titre;
    int *donnees;
} Colonne;

// Fonction pour créer une colonne vide
Colonne* creerColonne(const char *titre) {
    Colonne *col = malloc(sizeof(Colonne));
    if (col == NULL) {
        return NULL; // Erreur d'allocation mémoire
    }

    col->titre = strdup(titre);
    if (col->titre == NULL) {
        free(col); // Nettoyer la mémoire allouée précédemment
        return NULL; // Erreur d'allocation mémoire
    }

    col->donnees = NULL;

    return col;
}

int main() {
    // Exemple d'utilisation de la fonction creerColonne
    Colonne *nouvellecolonne = creerColonne("Ma colonne");
     // on se retrouve avec un print pour être sur qu'il n'y a pas de soucis pour la création !
    if (nouvellecolonne != NULL) {
        printf("Colonne créée avec succès : %s\n", nouvellecolonne->titre);
    } else {
        printf("Erreur lors de la création de la colonne.\n");
    }

    free(nouvellecolonne->titre);
    free(nouvellecolonne);

    return 0;
}
