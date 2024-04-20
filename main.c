//
// Created by natha on 20/04/2024.
//

#include "column.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main() {

    COLUMN *maCOLUMN = create_COLUMN("Ma COLUMN");
    setlocale(LC_CTYPE,"");
    if (maCOLUMN != NULL) {
        insererValeur(maCOLUMN, 10);
        insererValeur(maCOLUMN, 20);
        insererValeur(maCOLUMN, 30);
        insererValeur(maCOLUMN, 20);
        insererValeur(maCOLUMN, 40);

        print_col(maCOLUMN);

        printf("Occurrences de la valeur 20 : %d\n", nbOccurrences(maCOLUMN, 20));
        printf("Valeur à la position 2 : %d\n", valeurALaPosition(maCOLUMN, 2));
        printf("Nombre de valeurs supérieures à 20 : %d\n", nbValeursSuperieures(maCOLUMN, 20));
        printf("Nombre de valeurs inférieures à 20 : %d", nbValeursInferieures(maCOLUMN,20));
    }

    return 0;
}