//
// Created by natha on 20/04/2024.
//

#include "column.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main() {
    COLUMN *mycol = create_column(INT, "Column 1");
    int a = 8, c = 9;
    int* ptr =&a;
    insert_value(mycol, &a);

    insert_value(mycol, &c);

    nb_occurence(mycol,7);

    print_col(mycol);



    return 0;
}