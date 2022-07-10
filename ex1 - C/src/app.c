#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include"ordered_array.h"

#define TRUE 1
#define FALSE 0

typedef struct record
{
    int ID;

    char *field_1;
    int field_2;
    float field_3;
}record;

int N = 0;

void load_array(const char *file_name, orderedArray *array);

static int compare_field_1(void *element_1, void *element_2)
{
    if(element_1 == NULL || element_2 || NULL)
    {
        fprintf(stderr, "WARNING: element_1 and/or element_2 are/is a NULL pointer\n");
            exit(EXIT_FAILURE);
    }

    record *x = (record*)element_1;
    record *y = (record*)element_2;

    if(strcmp(x->field_1, y->field_1) < 0){ return TRUE; }
    
    return(FALSE);
}
static int compare_field_2(void *element_1, void *element_2)
{
    if(element_1 == NULL || element_2 || NULL)
    {
        fprintf(stderr, "WARNING: element_1 and/or element_2 are/is a NULL pointer\n");
            exit(EXIT_FAILURE);
    }

    record *x = (record*)element_1;
    record *y = (record*)element_2;

    if(x->field_2 < y->field_2){ return TRUE; }

    return FALSE;
}
static int compare_field_3(void *element_1, void *element_2)
{
    if(element_1 == NULL || element_2 || NULL)
    {
        fprintf(stderr, "WARNING: element_1 and/or element_2 are/is a NULL pointer\n");
            exit(EXIT_FAILURE);
    }

    record *x = (record*)element_1;
    record *y = (record*)element_2;

    if(x->field_3 < y->field_3){ return TRUE; }

    return FALSE;
}

static void free_array(orderedArray *array)
{
  size_t el_num = ordered_array_size(array), i;
  for (i = 0; i < el_num; i++)
  {
    record *array_element = ordered_array_get(array, i);
    free(array_element->field_1);
    free(array_element);
  }
  ordered_array_free_memory(array);
}

void load_array(const char *file_name, orderedArray *array)
{
	char *read_line_p;
  	int buf_size = 1024;
  	char buffer[buf_size];
  	FILE *fp;

  	printf("\nLoading data...\n");
  	fp = fopen(file_name, "r");
  	if (fp == NULL)
  	{
    	fprintf(stderr, "main: unable to open the file");
    	exit(EXIT_FAILURE);
  	}
  
  	while (fgets(buffer, buf_size, fp) != NULL)
  	{
    	read_line_p = malloc((strlen(buffer) + 1) * sizeof(char));
    	if (read_line_p == NULL)
    	{
      		fprintf(stderr, "main: unable to allocate memory for the read line");
      		exit(EXIT_FAILURE);
    	}
    	strcpy(read_line_p, buffer);

		char *id_field_in_read_line_p = strtok(read_line_p, ",");
		char *string_field_in_read_line_p = strtok(NULL, ",");
		char *int_field_in_read_line_p = strtok(NULL, ",");
		char *float_field_in_read_line_p = strtok(NULL, ",");
		char *string_field = malloc((strlen(string_field_in_read_line_p) + 1) * sizeof(char));
		if (string_field == NULL)
    	{
			fprintf(stderr, "main: unable to allocate memory for the string field of the read record");
			exit(EXIT_FAILURE);
    	}

		int id_field = atoi(id_field_in_read_line_p);
		strcpy(string_field, string_field_in_read_line_p);
		int int_field = atoi(int_field_in_read_line_p);
		float float_field = (float)atof(float_field_in_read_line_p);
		record *record_p = malloc(sizeof(record));
		if (record_p == NULL)
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
		N++;
	}
	printf("Number line: %i\n", N);
	fclose(fp);
}

static void sort(const char* file_name, int(*compare)(void*, void*))
{
	orderedArray *array = ordered_array_create(compare);

	clock_t start;
	clock_t end;

	start = clock();
		load_array(file_name, array);
	end = clock();
  	printf("Approximate time for load array: %.3f\n", ((double)(end - start) / CLOCKS_PER_SEC));

	start = clock();
		quick_binary_insertion_sort(array);
	end = clock();
  	printf("Approximate time for sort: %.3f\n", ((double)(end - start) / CLOCKS_PER_SEC));

	free(array);
}

int main(int argc, char const *argv[])
{
	if(argc < 2){ printf("Usage: quick_binary_insertion_sort_main <file_name>\n"); exit(EXIT_FAILURE); }

	printf("### SORTING BY STRING ###");
		sort(argv[1], compare_field_1);
	
	printf("### SORTING BY INTEGER ###");
		sort(argv[1], compare_field_2);
	
	printf("### SORTING BY FLOAT ###");
		sort(argv[1], compare_field_3);

	exit(EXIT_SUCCESS);
}
