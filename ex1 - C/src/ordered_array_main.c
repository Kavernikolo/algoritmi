#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>

#include "ordered_array.h"

int compare_field_ID(void *element_1, void *element_2)
{
  record *a = (record *)element_1;
  record *b = (record *)element_2;
  return a->ID - b->ID;
}

int compare_field_1(void *element_1, void *element_2)
{
  record *a = (record *)element_1;
  record *b = (record *)element_2;
  return strcmp(a->field_1, b->field_1);
}

int compare_field_2(void *element_1, void *element_2)
{
  record *a = (record *)element_1;
  record *b = (record *)element_2;
  return a->field_2 - b->field_2;
}

int compare_field_3(void *element_1, void *element_2)
{
  record *a = (record *)element_1;
  record *b = (record *)element_2;
  if (a->field_3 > b->field_3)
  {
    return 1;
  }
  else if (a->field_3 < b->field_3)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

int compare_int(void *element_1, void *element_2)
{
  int *a = (int *)element_1;
  int *b = (int *)element_2;
  return (*a) - (*b);
}

int compare_float(void *element_1, void *element_2)
{
  float *a = (float *)element_1;
  float *b = (float *)element_2;
  if (*a > *b)
  {
    return 1;
  }
  else if (*a < *b)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

int compare_string(void *element_1, void *element_2)
{
  char *a = (char *)element_1;
  char *b = (char *)element_2;
  return strcmp(a, b);
}

int file_exists(const char* filename)
{
    struct stat buffer;
    int exist = stat(filename,&buffer);
    
    if(exist == 0){ return TRUE; }
    else{ return FALSE; }
}

void isOrdered(OrderedArray *array, int (*compare)(void *, void *))
{
    int sortingIsCorrect = TRUE;

    int i = 0;

    while (sortingIsCorrect == TRUE && i < array->size)
    {        
        if((*compare)(ordered_array_get(array, i), ordered_array_get(array, i++)) <= 0){ i++; }
        else{sortingIsCorrect = FALSE; }
    }

    i = 0;
    while (i < array->size)
    {
        record *array_element = (record*)ordered_array_get(array, i);
            printf("%d, %s, %d, %f\n", array_element->ID, array_element->field_1, array_element->field_2, array_element->field_3);
        
        i++;
    }
    
    
    if(sortingIsCorrect == TRUE){printf("The sorting is correct");}
    else{printf("The sorting is wrong");}
}

void print_array(OrderedArray *array, int index) 
{
    printf("\nSave data...\n");

    const char *file_ID_name = "records-ID-ordered.csv";
    
    const char *file_field_1_name = "records-field_1-ordered.csv";
    const char *file_field_2_name = "records-field_2-ordered.csv";
    const char *file_field_3_name = "records-field_3-ordered.csv";

    if(!file_exists(file_ID_name))
    {
        FILE *file = fopen(file_ID_name, "w");

        for(int i = 0; i < index; i++)
        {
            record *array_element = (record*)ordered_array_get(array, i);
            fprintf(file, "%d, %s, %d, %f\n", array_element->ID, array_element->field_1, array_element->field_2, array_element->field_3);
        }

        fclose(file);
    }
    else if(!file_exists(file_field_1_name))
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
        quick_binary_insertion_sort(array, compare);
    gettimeofday(&end, NULL);
    time_taken = (double)end.tv_sec + (double)end.tv_usec / 1e6 - (double)start.tv_sec - (double)start.tv_usec / 1e6;

    printf("Array ordered in: %fs\n\n", time_taken);

    print_array(array, array->size);
    //isOrdered(array, compare);

    free_array(array);
}

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        printf("Usage: ordered_array_main <file_name>\n");
        exit(EXIT_FAILURE);
    }

    printf("\n------------ID------------\n");
        test_with_comparison_function(argv[1], compare_field_ID);

    printf("\n------------STRING------------\n");
        test_with_comparison_function(argv[1], compare_field_1);
    
    printf("\n\n------------INT------------\n");
        test_with_comparison_function(argv[1], compare_field_2);
    
    printf("\n\n------------FLOAT------------\n");
        test_with_comparison_function(argv[1], compare_field_3);

    return (EXIT_SUCCESS);
}