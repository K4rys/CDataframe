//
// Created by natha on 20/04/2024.
//

#include "column.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main() {
    COLUMN *mycol = create_column(CHAR, "Column 1");
    char a = 'A', c = 'C';

    insert_value(mycol, &a);

    insert_value(mycol, NULL);

    insert_value(mycol, &c);

    print_col(mycol);



    return 0;
}