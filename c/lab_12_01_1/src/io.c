#include "io.h"

int count_int_arr_len(char *file_name, size_t *n)
{
    FILE *f = NULL;
    int temp;
    int rc = 0;

    f = fopen(file_name, "r");
    if (!f)
        rc = RC_INCORRECT_FILE;
    else
    {
        while (!feof(f) && rc == 0)
        {
            if (fscanf(f, "%d\n", &temp) != 1)
                rc = RC_INCORRECT_INPUT;   // Считанные данные не являются числом
            else
                (*n)++;
        }
        fclose(f);
        if (*n == 0)
            rc = RC_EMPTY_FILE;
    }

    return rc;
}

int read_int_arr(char *file_name, int *pb, int *pe)
{
    FILE *f = NULL;
    int *pa = pb;
    int rc = 0;

    f = fopen(file_name, "r");
    if (!f)
        rc = RC_INCORRECT_FILE;
    else
    {
        while (!feof(f) && rc == 0 && pa != pe)
            if (fscanf(f, "%d\n", pa) != 1)
                rc = RC_INCORRECT_INPUT;   // Считанные данные не являются числом
            else
                pa++;
        fclose(f);
    }
    return rc;
}

int write_int_arr(char *file_name, int *pb, int *pe)
{
    FILE *f = NULL;
    int rc = 0;

    f = fopen(file_name, "w");
    if (!f)
        rc = RC_INCORRECT_FILE;            // Не удалось открыть файл
    else
    {
        for (int *pa = pb; pa < pe && rc == 0; pa++)
            if (fprintf(f, "%d ", *pa) < 0)
                rc = RC_WRITE_ERROR;
        fclose(f);
    }

    return rc;
}
