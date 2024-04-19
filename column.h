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

// Retourner le nombre d'occurrences d'une valeur x dans la colonne
int nbOccurrences(const Colonne *col, int x) {
    if (col == NULL || col->donnees == NULL) {
        return 0; // Colonne invalide ou vide
    }

    int occurrences = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] == x) {
            occurrences++;
        }
    }
    return occurrences;
}

// Retourner la valeur présente à la position x dans la colonne
int valeurALaPosition(const Colonne *col, int x) {
    if (col == NULL || col->donnees == NULL || x < 0 || x >= col->taille_logique) {
        return -1; // Colonne invalide, vide ou position invalide
    }
    return col->donnees[x];
}

// Retourner le nombre de valeurs supérieures à x dans la colonne
int nbValeursSuperieures(const Colonne *col, int x) {
    if (col == NULL || col->donnees == NULL) {
        return 0; // Colonne invalide ou vide
    }

    int nbSuperieures = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] > x) {
            nbSuperieures++;
        }
    }
    return nbSuperieures;
}

// Retourner le nombre de valeurs inférieures à x dans la colonne
int nbValeursInferieures(const Colonne *col, int x) {
    if (col == NULL || col->donnees == NULL) {
        return 0; // Colonne invalide ou vide
    }

    int nbInferieures = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] < x) {
            nbInferieures++;
        }
    }
    return nbInferieures;
}

// Retourner le nombre de valeurs égales à x dans la colonne
int nbValeursEgales(const Colonne *col, int x) {
    if (col == NULL || col->donnees == NULL) {
        return 0; // Colonne invalide ou vide
    }

    int nbEgales = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] == x) {
            nbEgales++;
        }
    }
    return nbEgales;
}

int main() {
    // Création d'une colonne
    Colonne *maColonne = creerColonne("Ma colonne");

    if (maColonne != NULL) {
        // Insertion de quelques valeurs dans la colonne
        insererValeur(maColonne, 10);
        insererValeur(maColonne, 20);
        insererValeur(maColonne, 30);
        insererValeur(maColonne, 20);
        insererValeur(maColonne, 40);

        // Affichage du contenu de la colonne
        afficherColonne(maColonne);

        // Exemples d'utilisation des nouvelles fonctions
        printf("Occurrences de la valeur 20 : %d\n", nbOccurrences(maColonne, 20));
        printf("Valeur à la position 2 : %d\n", valeurALaPosition(maColonne, 2));
        printf("Nombre de valeurs supérieures à 20 : %d\n", nbValeursSuperieures(maColonne, 20));
        printf("Nombre de valeurs inférieures à 20 : %)}}
