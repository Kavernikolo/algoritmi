#include"../header/error_handling.h"

#include<stdlib.h>
#include<stdio.h>

void exception(char *message)
{
    int errnum = errno;

    fprintf(stderr, "%s: %s\n", message, strerror(errnum));
        exit(EXIT_FAILURE);
}

void file_exception(){ exception("Error opening file"); }
void argc_exception(){ exception("Error in the number of cl argument"); }

void scanf_exception(){ exception("Error while retreiving data"); }

void malloc_exception(){ exception("Error while allocating memory"); }