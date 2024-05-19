
//
// Created by natha on 21/04/2024.
//

#ifndef CDATAFRAME_COLUMNV2_H
#define CDATAFRAME_COLUMNV2_H
#define ASC 0
#define DESC 1
#define REALOC_SIZE 256

enum enum_type
{
    NULLVAL = 1 , UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
};
typedef enum enum_type ENUM_TYPE;

union column_type{
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
};
typedef union column_type COL_TYPE ;

struct column {
    char *title;
    unsigned int size;
    unsigned int max_size;
    ENUM_TYPE column_type;
    COL_TYPE **data; // array of pointers to stored data
    unsigned long long int *index; // array of integers
};
typedef struct column COLUMN;

COLUMN *create_column(ENUM_TYPE type, char *title);
int insert_value(COLUMN *col, void *value);
void delete_column(COLUMN **col);
int convert_value(COLUMN *col, unsigned long long int i, char *str, int size);
void print_col(COLUMN* col);
int nb_occurence(COLUMN* col, void *value);
void* get_value(COLUMN* col, int i);
int nb_value_superior(COLUMN* col, void* value);
int nb_value_inferior(COLUMN* col, void* value);
int nb_value_equal(COLUMN* col, void *value);

char* get_value_indice(COLUMN* col,int indice,char *str);
#endif //CDATAFRAME_COLUMNV2_H
