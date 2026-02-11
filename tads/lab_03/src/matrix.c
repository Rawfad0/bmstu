#include "matrix.h"

int **allocate_matrix(size_t n, size_t m)
{
    int **matrix = malloc(n * sizeof(int*) + n * m * sizeof(int));
    if (matrix)
    {
        matrix[0] = (int *) (matrix + n);
        for (size_t i = 1; i < n; i++)
            matrix[i] = matrix[0] + m * i;
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < m; j++)
                matrix[i][j] = 0;
    }
    return matrix;
}

int is_matrix_valid(matrix_t matrix)
{
    if (matrix.matrix != NULL)
        return VALID_MATRIX;
    return INVALID_MATRIX;
}

void free_matrix(matrix_t *matrix)
{
    free(matrix->matrix);
    matrix->matrix = NULL;
}

int matrix_addition(matrix_t matrix1, matrix_t matrix2, matrix_t *matrix_res)
{
    if (matrix1.n != matrix2.n || matrix1.m != matrix2.m)
        return RC_INCORRECT_SIZE;
    matrix_res->n = matrix1.n;
    matrix_res->m = matrix1.m;
    for (size_t i = 0; i < matrix1.n; i++)
        for (size_t j = 0; j < matrix1.m; j++)
            matrix_res->matrix[i][j] = matrix1.matrix[i][j] + matrix2.matrix[i][j];
    return RC_OK;
}

int sparse_matrix_add(sparse_matrix_t *matrix, int value, size_t j)
{
    int rc = RC_OK;
    void *tmp1 = realloc(matrix->a, (matrix->k + 1) * sizeof(int));
    void *tmp2 = realloc(matrix->ja, (matrix->k + 1) * sizeof(size_t));
    
    if (tmp1 == NULL || tmp2 == NULL)
        rc = RC_ALLOCATION_FAILED;
    else
    {
        matrix->a = tmp1;
        matrix->a[matrix->k] = value;
        matrix->ja = tmp2;
        matrix->ja[matrix->k] = j;
        (matrix->k)++;
    }
    if (rc != RC_OK)
        printf("ALLOC ERROR");
    return RC_OK;
}

sparse_matrix_t create_sparse_matrix(size_t n, size_t m)
{
    sparse_matrix_t sparse_matrix = { NULL, NULL, NULL, 0, 0, 0 };
    if (n != 0 && (sparse_matrix.ia = malloc(n * sizeof(size_t))) != NULL)
        for (size_t i = 0; i < n; i++)
            sparse_matrix.ia[i] = 0;
    sparse_matrix.n = n, sparse_matrix.m = m;
    return sparse_matrix;
}

int is_sparse_matrix_valid(sparse_matrix_t matrix)
{
    if (matrix.a != NULL && matrix.ia != NULL && matrix.ja != NULL)
        return VALID_MATRIX;
    return INVALID_MATRIX;
}

void free_sparse_matrix(sparse_matrix_t *matrix)
{
    free(matrix->a);
    matrix->a = NULL;
    free(matrix->ia);
    matrix->ia = NULL;
    free(matrix->ja);
    matrix->ja = NULL;
}

int sparse_matrix_addition(sparse_matrix_t matrix1, sparse_matrix_t matrix2, sparse_matrix_t *matrix_res)
{
    if (matrix1.n != matrix2.n || matrix1.m != matrix2.m)
        return RC_INCORRECT_SIZE;
    size_t counter = 0;
    int rc = RC_OK;
    for (size_t i = 0; i < matrix1.n; i++)
    {
        size_t j1_i = matrix1.ia[i];
        size_t j2_i = matrix2.ia[i];
        while (j1_i < matrix1.k && j2_i < matrix2.k && 
            ((i == matrix1.n - 1 && j1_i < matrix1.k && j2_i < matrix2.k) || 
            (i != matrix1.n - 1 && j1_i < matrix1.ia[i+1] && j2_i < matrix2.ia[i+1])))
        {
            if (matrix1.ja[j1_i] < matrix2.ja[j2_i])
                if ((rc = sparse_matrix_add(matrix_res, VALUE1, matrix1.ja[j1_i])))
                    return rc;
                else
                    j1_i++, counter++;
            else if (matrix1.ja[j1_i] > matrix2.ja[j2_i])
                if ((rc = sparse_matrix_add(matrix_res, VALUE2, matrix2.ja[j2_i])))
                    return rc;
                else
                    j2_i++, counter++;
            else if (VALUE1 + VALUE2 != 0)
                if ((rc = sparse_matrix_add(matrix_res, VALUE1 + VALUE2, matrix1.ja[j1_i])))
                    return rc;
                else
                    j1_i++, j2_i++, counter++;
            else
                j1_i++, j2_i++;
        }

        while ((i == matrix1.n - 1 && j1_i < matrix1.k) || (i != matrix1.n - 1 && j1_i < matrix1.ia[i+1]))
            if ((rc = sparse_matrix_add(matrix_res, VALUE1, matrix1.ja[j1_i])))
                return rc;
            else
                j1_i++, counter++;
        while ((i == matrix1.n - 1 && j2_i < matrix2.k) || (i != matrix1.n - 1 && j2_i < matrix2.ia[i+1]))
            if ((rc = sparse_matrix_add(matrix_res, VALUE2, matrix2.ja[j2_i])))
                return rc;
            else
                j2_i++, counter++;

        if (i == 0)
            matrix_res->ia[0] = 0;
        if (i != matrix_res->n - 1)
            matrix_res->ia[i + 1] = counter;
    }
    return RC_OK;
}

sparse_matrix_t matrix_std_to_sparse(matrix_t matrix)
{
    sparse_matrix_t sparse_matrix = create_sparse_matrix(matrix.n, matrix.m);
    size_t counter = 0;
    for (size_t i = 0; i < matrix.n; i++)
    {
        for (size_t j = 0; j < matrix.m; j++)
            if (matrix.matrix[i][j] != 0)
                sparse_matrix_add(&sparse_matrix, matrix.matrix[i][j], j+1), counter++;
        if (i == 0)
            sparse_matrix.ia[0] = 0;
        if (i != matrix.n - 1)
            sparse_matrix.ia[i + 1] = counter;
    }
    sparse_matrix.n = matrix.n;
    sparse_matrix.m = matrix.m;
    return sparse_matrix;
}

matrix_t matrix_sparse_to_std(sparse_matrix_t matrix)
{
    matrix_t matrix_std = { NULL, matrix.n, matrix.m };
    matrix_std.matrix = allocate_matrix(matrix.n, matrix.m);
    for (size_t i = 0; i < matrix.n; i++)
    {
        // printf("j: %zu %zu\n", matrix.ia[i], matrix.ia[i+1]);
        for (size_t j = matrix.ia[i]; (i == matrix.n - 1 && j < matrix.k) || (i != matrix.n - 1 && j < matrix.ia[i+1]); j++)
        {
            // printf(". %zu %zu | %zu | %zu %zu | %d \n", i, j, matrix.ja[j]-1, i, matrix.ja[j]-1, matrix.a[j]);
            matrix_std.matrix[i][matrix.ja[j]-1] = matrix.a[j];
        }
    }
    return matrix_std;
}

// Функция для замера времени сложения стандартных матриц
double measure_matrix_addition(matrix_t matrix1, matrix_t matrix2, matrix_t matrix_res)
{
    struct timeval tb, te;

    gettimeofday(&tb, NULL);
    matrix_addition(matrix1, matrix2, &matrix_res);
    gettimeofday(&te, NULL);

    return te.tv_sec - tb.tv_sec + (te.tv_usec - tb.tv_usec) / 1000000.0;
}

// Функция для замера времени сложения разреженных матриц
double measure_smatrix_addition(sparse_matrix_t matrix1, sparse_matrix_t matrix2, sparse_matrix_t matrix_res)
{
    struct timeval tb, te;

    gettimeofday(&tb, NULL);
    sparse_matrix_addition(matrix1, matrix2, &matrix_res);
    gettimeofday(&te, NULL);

    return te.tv_sec - tb.tv_sec + (te.tv_usec - tb.tv_usec) / 1000000.0;
}

int compare(matrix_t matrix1, matrix_t matrix2, sparse_matrix_t sparse_matrix1, sparse_matrix_t sparse_matrix2)
{
    int rc = RC_OK;

    // Время сложения
    double matrix_addition_s = 0;
    double smatrix_addition_s = 0;

    matrix_t matrix_res = { NULL, 0, 0 };
    sparse_matrix_t sparse_matrix_res = create_sparse_matrix(matrix1.n, matrix1.m);

    if ((matrix_res.matrix = allocate_matrix(matrix1.n, matrix1.m)) == NULL)
        return RC_ALLOCATION_FAILED;

    // Сложение стандартных матриц
    for (size_t i = 0; i < REPEAT; i++)
        matrix_addition_s += measure_matrix_addition(matrix1, matrix2, matrix_res);

    // Сложение разреженных матриц
    for (size_t i = 0; i < REPEAT; i++)
        smatrix_addition_s += measure_smatrix_addition(sparse_matrix1, sparse_matrix2, sparse_matrix_res);

    // Память
    size_t std_mem = sizeof(matrix1) + matrix1.n*matrix1.m*sizeof(int) + sizeof(matrix2) + matrix2.n*matrix2.m*sizeof(int);
    size_t sparse_mem = sizeof(sparse_matrix1) + sparse_matrix1.k*sizeof(int) + sparse_matrix1.k*sizeof(size_t) + sparse_matrix1.n*sizeof(size_t)
        + sizeof(sparse_matrix2) + sparse_matrix2.k*sizeof(int) + sparse_matrix2.k*sizeof(size_t) + sparse_matrix2.n*sizeof(size_t);

    // Вывод таблицей
    printf("%.*s\n", 61, BLANKSx150);
    printf("%s%-*u|%-*s|%-*s|%-*s \n", "Addition comparison, s, N=", 8, REPEAT, 12, "Matrix", 12, "Sparse matrix", 15, "%% better");
    printf("%.*s+%.*s\n", 35, BLANKSx150, 12+15+1, BLANKSx150);
    printf("%-*s|%*lf|%*lf|%.*lf%%\n", 35, "Time", 12, matrix_addition_s, 12, \
        smatrix_addition_s, 3, matrix_addition_s / smatrix_addition_s * 100 - 100);
    printf("%-*s|%*zu|%*zu|%.*lf%%\n", 35, "Memory", 12, std_mem, 
        12, sparse_mem, 3, (double) std_mem / sparse_mem  * 100 - 100);
    printf("%.*s+%.*s\n", 35, BLANKSx150, 12+15+1, BLANKSx150);
    
    return rc;
}

void print_sparse_matrix(sparse_matrix_t matrix)
{
    printf("a = {");
    for (size_t i = 0; i < matrix.k; i++)
        printf("%d ", matrix.a[i]);
    printf("}\nja = {");
    for (size_t i = 0; i < matrix.k; i++)
        printf("%zu ", matrix.ja[i]);
    printf("}\nia = {");
    for (size_t i = 0; i < matrix.n; i++)
        printf("%zu ", matrix.ia[i]);
    printf("}\n");
}