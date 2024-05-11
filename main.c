//
// Created by natha on 20/04/2024.
//

#include "column.h"
#include "CDataframe.h"
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

    int x = 3;
    int *ptr = &x;
    ptr = (void*) ptr;


    ENUM_TYPE cdftype [] = {INT,INT,INT};
    CDATAFRAME *cdf = create_cdataframe(cdftype, 3);
    fill_cdataframe_user(cdf);
    print_cdataframe(cdf);
    replace_value_cdataframe(cdf,ptr,1,12);
    print_cdataframe(cdf);




    return 0;
}

/*void *data[] = {
        (int []) {1, 2, 3},
        (char *[]) {"John", "Doe", "30"}
};


const int taille[] = {3, 3};*/
