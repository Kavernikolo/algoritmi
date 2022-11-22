#include"../header/record.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int compare_ID(void *element_1, void *element_2)
{
    if (element_1 == NULL)
    {
        fprintf(stderr, "precedes_record_int_field: the first parameter is a null pointer");
            exit(EXIT_FAILURE);
    }
    
    if (element_2 == NULL)
    {
        fprintf(stderr, "precedes_record_int_field: the second parameter is a null pointer");
            exit(EXIT_FAILURE);
    }
    
    Record *x = (Record *)element_1;
    Record *y = (Record *)element_2;

    if (x->ID == y->ID){ return (0); }
    if (x->ID < y->ID){ return (-1); }
    
    return (1);
}

int compare_field_1(void *element_1, void *element_2)
{
    if (element_1 == NULL)
    {
        fprintf(stderr, "precedes_string: the first parameter is a null pointer");
            exit(EXIT_FAILURE);
    }
    
    if (element_2 == NULL)
    {
        fprintf(stderr, "precedes_string: the second parameter is a null pointer");
            exit(EXIT_FAILURE);
    }
    
    Record *x = (Record *)element_1;
    Record *y = (Record *)element_2;

    if (strcmp(x->field_1, y->field_1) == 0){ return (0); }
    if (strcmp(x->field_1, y->field_1) < 0){ return (-1); }
    
    return (1);
}

int compare_field_2(void *element_1, void *element_2)
{
    if (element_1 == NULL)
    {
        fprintf(stderr, "precedes_record_int_field: the first parameter is a null pointer");
            exit(EXIT_FAILURE);
    }
    
    if (element_2 == NULL)
    {
        fprintf(stderr, "precedes_record_int_field: the second parameter is a null pointer");
            exit(EXIT_FAILURE);
    }
    
    Record *x = (Record *)element_1;
    Record *y = (Record *)element_2;

    if (x->field_2 == y->field_2){ return (0); }
    if (x->field_2 < y->field_2){ return (-1); }
    
    return (1);
}

int compare_field_3(void *element_1, void *element_2)
{
    if (element_1 == NULL)
    {
        fprintf(stderr, "precedes_record_float_field: the first parameter is a null pointer");
            exit(EXIT_FAILURE);
    }
    
    if (element_2 == NULL)
    {
        fprintf(stderr, "precedes_record_float_field: the second parameter is a null pointer");
            exit(EXIT_FAILURE);
    }
    
    Record *x = (Record *)element_1;
    Record *y = (Record *)element_2;

    if (x->field_3 == y->field_3){ return (0); }
    if (x->field_3 < y->field_3){ return (-1); }
    
    return (1);
}