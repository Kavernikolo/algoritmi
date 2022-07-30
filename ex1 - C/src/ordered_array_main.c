#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>

#include "ordered_array.h"

typedef struct _record
{
    int ID;

    char *field_1;
    int field_2;
    float field_3;
}record;

int file_exists(const char* filename)
{
    struct stat buffer;
    int exist = stat(filename,&buffer);
    
    if(exist == 0){ return TRUE; }
    else{ return FALSE; }
}

void print_array(OrderedArray *array, int index) 
{
    printf("\nSave data...\n");

    const char *file_ID_name = "records-ID-ordered.csv";
    const char *file_field_1_name = "records-field_1-ordered.csv";
    const char *file_field_2_name = "records-field_2-ordered.csv";
    const char *file_field_3_name = "records-field_3-ordered.csv";

    if(!file_exists(file_field_1_name))
    {
        FILE *file = fopen(file_field_1_name, "w");

        for(int i = 0; i < index; i++)
        {
            record *array_element = (record*)ordered_array_get(array, i);
            fprintf(file, "%d, %s, %d, %f\n", array_element->ID, array_element->field_1, array_element->field_2, array_element->field_3);
        }

        fclose(file);
    }
    else if(!file_exists(file_field_2_name))
    {
        FILE *file = fopen(file_field_2_name, "w");

        for(int i = 0; i < index; i++)
        {
            record *array_element = (record*)ordered_array_get(array, i);
            fprintf(file, "%d, %s, %d, %f\n", array_element->ID, array_element->field_1, array_element->field_2, array_element->field_3);
        }

        fclose(file);
    }
    else
    {
        FILE *file = fopen(file_field_3_name, "w");

        for(int i = 0; i < index; i++)
        {
            record *array_element = (record*)ordered_array_get(array, i);
            fprintf(file, "%d, %s, %d, %f\n", array_element->ID, array_element->field_1, array_element->field_2, array_element->field_3);
        }

        fclose(file);
    }
}


static int compare_field_1(void *r1_p, void *r2_p)
{
    if(r1_p == NULL)
    {
        fprintf(stderr, "precedes_string: the first parameter is a null pointer\n");
            exit(EXIT_FAILURE);
    }
    
    if(r2_p == NULL)
    {
        fprintf(stderr, "precedes_string: the second parameter is a null pointer\n");
            exit(EXIT_FAILURE);
    }

    record *rec1_p = (record *)r1_p;
    record *rec2_p = (record *)r2_p;
    if(strcmp(rec1_p->field_1, rec2_p->field_1) < 0){ return TRUE; }

    return FALSE;
}

static int compare_field_2(void *r1_p, void *r2_p)
{
    if(r1_p == NULL)
    {
        fprintf(stderr, "precedes_record_int_field: the first parameter is a null pointer\n");
            exit(EXIT_FAILURE);
    }

    if(r2_p == NULL)
    {
        fprintf(stderr, "precedes_record_int_field: the second parameter is a null pointer\n");
            exit(EXIT_FAILURE);
    }

    record *rec1_p = (record *)r1_p;
    record *rec2_p = (record *)r2_p;
    if(rec1_p->field_2 < rec2_p->field_2){ return TRUE; }

    return FALSE;
}

static int compare_field_3(void *r1_p, void *r2_p)
{
    if(r1_p == NULL)
    {
        fprintf(stderr, "precedes_record_int_field: the first parameter is a null pointer\n");
            exit(EXIT_FAILURE);
    }

    if(r2_p == NULL)
    {
        fprintf(stderr, "precedes_record_int_field: the second parameter is a null pointer\n");
            exit(EXIT_FAILURE);
    }

    record *rec1_p = (record *)r1_p;
    record *rec2_p = (record *)r2_p;
    if(rec1_p->field_3 < rec2_p->field_3){ return TRUE; }
    
    return FALSE;
}

static void free_array(OrderedArray *array)
{
    size_t el_num = ordered_array_size(array), i;
    for(i = 0; i < el_num; i++)
    {
        record *array_element = (record *)ordered_array_get(array, i);
    
        free(array_element->field_1);
        free(array_element);
    }
    
    ordered_array_free_memory(array);
}

static void load_array(const char *file_name, OrderedArray *array)
{
    char *read_line_p;
    int buf_size = 1024;
    char buffer[buf_size];
    
    FILE *fp;

    printf("\nLoading data...\n");
    fp = fopen(file_name, "r");
    if(fp == NULL)
    {
        fprintf(stderr, "main: unable to open the file");
            exit(EXIT_FAILURE);
    }

    while(fgets(buffer, buf_size, fp) != NULL)
    {
        read_line_p = malloc((strlen(buffer) + 1) * sizeof(char));
        if(read_line_p == NULL)
        {
            fprintf(stderr, "main: unable to allocate memory forthe read line");
                exit(EXIT_FAILURE);
        }
        strcpy(read_line_p, buffer);

        char *id_field_in_read_line_p = strtok(read_line_p, ",");
        char *string_field_in_read_line_p = strtok(NULL, ",");
        char *int_field_in_read_line_p = strtok(NULL, ",");
        char *float_field_in_read_line_p = strtok(NULL, ",");
        char *string_field = malloc((strlen(string_field_in_read_line_p) + 1) * sizeof(char));

        if(string_field == NULL)
        {
            fprintf(stderr, "main: unable to allocate memory forthe string field of the read record");
                exit(EXIT_FAILURE);
        }

        int id_field = atoi(id_field_in_read_line_p);
        strcpy(string_field, string_field_in_read_line_p);
        int int_field = atoi(int_field_in_read_line_p);
        float float_field = (float)atof(float_field_in_read_line_p);
        
        record *record_p = malloc(sizeof(record));
        if(record_p == NULL)
        {
            fprintf(stderr, "main: unable to allocate memory for the read record");
                exit(EXIT_FAILURE);
        }

        record_p->ID = id_field;
        record_p->field_1 = string_field;
        record_p->field_2 = int_field;
        record_p->field_3 = float_field;

        ordered_array_add(array, (void *)record_p);
        free(read_line_p);
    } 
    
    fclose(fp);
}

static void test_with_comparison_function(const char *file_name, int (*compare)(void *, void *))
{
    double time_taken = 0;
    struct timeval start, end;

    OrderedArray *array = ordered_array_create(compare);

    gettimeofday(&start, NULL);
        load_array(file_name, array);
    gettimeofday(&end, NULL);
    time_taken = (double)end.tv_sec + (double)end.tv_usec / 1e6 - (double)start.tv_sec - (double)start.tv_usec / 1e6;
    printf("\nData loaded: %fs\n", time_taken);

    time_taken = 0;

    gettimeofday(&start, NULL);
        quick_binary_insertion_sort(array);
    gettimeofday(&end, NULL);
    time_taken = (double)end.tv_sec + (double)end.tv_usec / 1e6 - (double)start.tv_sec - (double)start.tv_usec / 1e6;

    printf("Array ordered in: %fs\n\n", time_taken);

    print_array(array, array->size);

    free_array(array);
}

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        printf("Usage: ordered_array_main <file_name>\n");
        exit(EXIT_FAILURE);
    }

    printf("\n------------STRING------------\n");
        test_with_comparison_function(argv[1], compare_field_1);
    
    printf("\n\n------------INT------------\n");
        test_with_comparison_function(argv[1], compare_field_2);
    
    printf("\n\n------------FLOAT------------\n");
        test_with_comparison_function(argv[1], compare_field_3);

    return (EXIT_SUCCESS);
}