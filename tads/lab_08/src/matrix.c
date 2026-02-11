#include "matrix.h"


size_t **allocate_matrix(size_t n, size_t m)
{
    size_t **matrix = malloc(n * sizeof(size_t*) + n * m * sizeof(size_t));
    if (matrix)
    {
        matrix[0] = (size_t *) (matrix + n);
        for (size_t i = 1; i < n; i++)
            matrix[i] = matrix[0] + m * i;
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < m; j++)
                matrix[i][j] = 0;
    }
    return matrix;
}

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
        rc = RC_INCORRECT_INPUT;
    else if ((matrix->matrix = allocate_matrix(matrix->n, matrix->m)) == NULL)
        rc = RC_ALLOCATION_FAILED;
    else
    {
        size_t x, y;
        size_t value;
        while (rc == RC_OK && counter > 0)
        {
            if (fscanf(f, "%zu %zu %zu\n", &y, &x, &value) != 3)
                rc = RC_INCORRECT_INPUT;
            else if (y > matrix->n || x > matrix->m)
                rc = RC_INCORRECT_INPUT;
            else
                matrix->matrix[y][x] = value, matrix->matrix[x][y] = value;
            counter--;
        }
    }
    if (f)
        fclose(f);
    return rc;
}

void free_matrix(matrix_t *matrix)
{
    free(matrix->matrix);
    matrix->matrix = NULL;
}
