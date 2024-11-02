#include "io.h"

int read_matrix(char *filename, matrix_t *matrix)
{
    size_t counter;
    int rc = RC_OK;

    FILE *f = fopen(filename, "r");
    if (!f)
        rc = RC_INCORRECT_FILE;
    else if (fscanf(f, "%zu %zu %zu\n", &matrix->n, &matrix->m, &counter) != 3)
        rc = RC_INCORRECT_INPUT;
    else if (matrix->n * matrix->m < counter)
        rc = RC_INCORRECT_COUNTER;
    else if ((matrix->matrix = allocate_matrix(matrix->n, matrix->m)) == NULL)
        rc = RC_ALLOCATION_FAILED;
    else
    {
        size_t x, y;
        double value;
        while (rc == RC_OK && counter > 0)
        {
            if (fscanf(f, "%zu %zu %lf\n", &y, &x, &value) != 3)
                rc = RC_INCORRECT_INPUT;
            else if (y == 0 || y > matrix->n || x == 0 || x > matrix->m)
                rc = RC_INCORRECT_INPUT;
            else
                matrix->matrix[y - 1][x - 1] = value;
            counter--;
        }
    }
    if (f)
        fclose(f);
    return rc;
}

int write_matrix(char *filename, matrix_t matrix)
{
    int rc = RC_OK;
    size_t counter = 0;
    for (size_t i = 0; i < matrix.n; i++)
        for (size_t j = 0; j < matrix.m; j++)
            if (fabs(matrix.matrix[i][j]) > MACHINE_EPS)
                counter++;

    FILE *f = fopen(filename, "w");
    if (!f)
        rc = RC_INCORRECT_FILE;
    else
    {
        fprintf(f, "%zu %zu %zu\n", matrix.n, matrix.m, counter);
        for (size_t i = 0; i < matrix.n; i++)
            for (size_t j = 0; j < matrix.m; j++)
                if (fabs(matrix.matrix[i][j]) > MACHINE_EPS)
                    fprintf(f, "%zu %zu %lf\n", i + 1, j + 1, matrix.matrix[i][j]);
        fclose(f);
    }
    return rc;
}
