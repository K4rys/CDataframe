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
    COLUMN *mycol = create_column(INT, "Column 1");
    int a = 1; int b = 2; int c = 3; int d = 4; int e = 5;

    insert_value(mycol, &b);

    insert_value(mycol, &c);

    insert_value(mycol, &a);

    insert_value(mycol, &d);

    insert_value(mycol, &e);

    double x = 3.1;
    double *ptr = &x;
    ptr = (void*) ptr;

    ENUM_TYPE type[] = {STRING,DOUBLE};
    char* name = "C:\\Users\\natha\\CLionProjects\\CDataframe\\export.csv";
    CDATAFRAME *cdf = load_from_csv(name,  type, 2);
    print_cdataframe(cdf);



    return 0;
}




