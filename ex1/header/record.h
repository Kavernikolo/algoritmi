typedef struct _Record
{
    int ID;

    char *field_1;
    int field_2;
    float field_3;
}Record;

int compare_ID(void *, void *);

int compare_field_1(void *, void *);
int compare_field_2(void *, void *);
int compare_field_3(void *, void *);