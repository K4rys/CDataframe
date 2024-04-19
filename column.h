#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour représenter une colonne
typedef struct {
    char *titre;
    int *donnees;
    int taille_physique; // Taille physique actuelle (nombre de cases allouées)
    int taille_logique;  // Taille logique actuelle (nombre de valeurs insérées)
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
    col->taille_physique = 0;
    col->taille_logique = 0;

    return col;
}

// Fonction pour libérer la mémoire allouée pour une colonne
void libererColonne(Colonne *col) {
    if (col == NULL) {
        return; // Rien à libérer
    }

    free(col->titre);
    free(col->donnees);
    free(col);
}

// Fonction pour afficher le contenu d'une colonne
void afficherColonne(const Colonne *col) {
    if (col == NULL) {
        printf("Colonne invalide.\n");
        return;
    }

    printf("Contenu de la colonne \"%s\":\n", col->titre);
    printf("Indice\tValeur\n");
    for (int i = 0; i < col->taille_logique; i++) {
        printf("%d\t%d\n", i, col->donnees[i]);
    }
}

// Fonction pour insérer une valeur dans une colonne
int insererValeur(Colonne *col, int valeur) {
    // Vérifier si la colonne existe
    if (col == NULL) {
        return 0; // Colonne invalide
    }

    // Vérifier si l'espace physique est épuisé
    if (col->taille_logique >= col->taille_physique) {
        // Réallouer de la mémoire pour 256 cases supplémentaires
        col->taille_physique += 256;
        int *nouvelles_donnees = realloc(col->donnees, col->taille_physique * sizeof(int));
        if (nouvelles_donnees == NULL) {
            // Erreur d'allocation mémoire, gestion de l'erreur
            fprintf(stderr, "Erreur : Impossible de réallouer de la mémoire pour la colonne.\n");
            return 0; // Échec de l'insertion
        }
        col->donnees = nouvelles_donnees;
    }

    // Insérer la valeur dans la colonne
    col->donnees[col->taille_logique++] = valeur;

    return 1; // Insertion réussie
}

int main() {
    // Création d'une colonne
    Colonne *maColonne = creerColonne("Ma colonne");

    if (maColonne != NULL) {
        // Insertion de quelques valeurs dans la colonne
        insererValeur(maColonne, 10);
        insererValeur(maColonne, 20);
        insererValeur(maColonne, 30);

        // Affichage du contenu de la colonne
        afficherColonne(maColonne);

        // Libération de la mémoire allouée pour la colonne
        libererColonne(maColonne);
    } else {
        printf("Erreur lors de la création de la colonne.\n");
    }

    return 0;
}
