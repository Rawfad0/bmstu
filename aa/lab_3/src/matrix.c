#include "matrix.h"

double **alloc_matrix_data(size_t rows, size_t cols)
{
    double **matrix = malloc(rows * sizeof(double*) + rows * cols * sizeof(double));
    if (matrix)
    {
        matrix[0] = (double *) (matrix + rows);
        for (size_t i = 1; i < rows; i++)
            matrix[i] = matrix[0] + cols * i;
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                matrix[i][j] = 0;
    }
    return matrix;
}

matrix_t *matrix_create(size_t rows, size_t cols)
{
    matrix_t *matrix = malloc(sizeof(matrix_t));
    if (matrix)
    {
        matrix->rows = rows;
        matrix->cols = cols;
        matrix->data = alloc_matrix_data(rows, cols);
        if (!matrix->data)
        {
            free(matrix);
            matrix = NULL;
        }
    }
    return matrix;
}

void matrix_free(matrix_t **matrix)
{
    free((*matrix)->data);
    free(*matrix);
    *matrix = NULL;
}

matrix_error_t matrix_rand_fill(matrix_t *matrix, double rand_min, double rand_max)
{
    matrix_error_t rc = MATRIX_OK;
    if (!matrix)
        rc = MATRIX_MEM;
    else if (!matrix->data)
        rc = MATRIX_MEM;
    else if (rand_min > rand_max)
        rc = MATRIX_INVALID_PARAM;
    else
    {
        for (size_t i = 0; i < matrix->rows; i++)
            for (size_t j = 0; j < matrix->cols; j++)
                matrix->data[i][j] = rand_min + (double)rand() / RAND_MAX * (rand_max - rand_min);
    }
    return rc;
}

matrix_error_t matrix_print(matrix_t *matrix)
{
    matrix_error_t rc = MATRIX_OK;
    if (!matrix)
        rc = MATRIX_MEM;
    else if (!matrix->data)
        rc = MATRIX_MEM;
    else
    {
        for (size_t i = 0; i < matrix->rows; i++)
        {
            for (size_t j = 0; j < matrix->cols; j++)
                printf("%lf ", matrix->data[i][j]);
            printf("\n");
        }
        printf("\n");
    }
    return rc;
}

matrix_error_t matrix_input(matrix_t *matrix);

matrix_error_t matrix_mult_standart(const matrix_t *a, const matrix_t *b, matrix_t **r)
{
    matrix_error_t rc = MATRIX_OK;
    if (!a || !b || a->cols != b->rows)
        rc = MATRIX_INVALID_PARAM;
    else if (!(*r = matrix_create(a->rows, b->cols)))
        rc = MATRIX_MEM;
    else
    {
        for (size_t i = 0; i < a->rows; i++)
            for (size_t j = 0; j < b->cols; j++)
                for (size_t k = 0; k < a->cols; k++)
                    (*r)->data[i][j] += a->data[i][k] * b->data[k][j];
    }
    return rc;
}

matrix_error_t calc_row_factor(const matrix_t *matrix, double **row_factor)
{
    matrix_error_t rc = MATRIX_OK;
    if (matrix == NULL || matrix->data == NULL || row_factor == NULL || *row_factor != NULL)
        rc = MATRIX_INVALID_PARAM;
    else if (!(*row_factor = calloc(matrix->rows, sizeof(double))))
        rc = MATRIX_MEM;
    else
        for (size_t i = 0; i < matrix->rows; i++)
            for (size_t j = 0; j < matrix->cols / 2; j++)
                (*row_factor)[i] += matrix->data[i][2 * j] * matrix->data[i][2 * j + 1];
    return rc;
}

matrix_error_t calc_col_factor(const matrix_t *matrix, double **col_factor)
{
    matrix_error_t rc = MATRIX_OK;
    if (matrix == NULL || matrix->data == NULL || col_factor == NULL || *col_factor != NULL)
        rc = MATRIX_INVALID_PARAM;
    else if (!(*col_factor = calloc(matrix->cols, sizeof(double))))
        rc = MATRIX_MEM;
    else
        for (size_t i = 0; i < matrix->rows / 2; i++)
            for (size_t j = 0; j < matrix->cols; j++)
                (*col_factor)[j] += matrix->data[2 * i][j] * matrix->data[2 * i + 1][j];
    return rc;
}

matrix_error_t matrix_mult_winograd(const matrix_t *a, const matrix_t *b, matrix_t **r)
{
    matrix_error_t rc = MATRIX_OK;
    double *row_factor = NULL, *col_factor = NULL;
    if (a == NULL || a->data == NULL || b == NULL || b->data == NULL || a->cols != b->rows || r == NULL || *r != NULL)
        rc = MATRIX_INVALID_PARAM;
    else if (!(*r = matrix_create(a->rows, b->cols)))
        rc = MATRIX_MEM;
    else if ((rc = calc_row_factor(a, &row_factor)) != MATRIX_OK)
        matrix_free(r);
    else if ((rc = calc_col_factor(b, &col_factor)) != MATRIX_OK)
        matrix_free(r), free(row_factor);
    else
    {
        for (size_t i = 0; i < a->rows; i++)
        {
            for (size_t j = 0; j < b->cols; j++)
            {
                (*r)->data[i][j] = -row_factor[i] - col_factor[j];
                for (size_t k = 0; k < a->cols / 2; k++)
                    (*r)->data[i][j] += (a->data[i][2 * k + 1] + b->data[2 * k][j]) * (a->data[i][2 * k] + b->data[2 * k + 1][j]);
            }
        }
        if (a->cols % 2)
            for (size_t i = 0; i < a->rows; i++)
                for (size_t j = 0; j < b->cols; j++)
                    (*r)->data[i][j] += a->data[i][a->cols - 1] * b->data[b->rows - 1][j];
        free(row_factor);
        free(col_factor);
    }
    return rc;
}

matrix_error_t calc_row_factor_opt(const matrix_t *matrix, double **row_factor)
{
    matrix_error_t rc = MATRIX_OK;
    if (matrix == NULL || matrix->data == NULL || row_factor == NULL || *row_factor != NULL)
        rc = MATRIX_INVALID_PARAM;
    else if (!(*row_factor = calloc(matrix->rows, sizeof(double))))
        rc = MATRIX_MEM;
    else
        for (size_t i = 0; i < matrix->rows; i++)
            for (size_t j = 1; j < matrix->cols; j += 2)
                (*row_factor)[i] -= matrix->data[i][j - 1] * matrix->data[i][j];
    return rc;
}

matrix_error_t calc_col_factor_opt(const matrix_t *matrix, double **col_factor)
{
    matrix_error_t rc = MATRIX_OK;
    if (matrix == NULL || matrix->data == NULL || col_factor == NULL || *col_factor != NULL)
        rc = MATRIX_INVALID_PARAM;
    else if (!(*col_factor = calloc(matrix->cols, sizeof(double))))
        rc = MATRIX_MEM;
    else
        for (size_t i = 1; i < matrix->rows; i += 2)
            for (size_t j = 0; j < matrix->cols; j++)
                (*col_factor)[j] -= matrix->data[i - 1][j] * matrix->data[i][j];
    return rc;
}

matrix_error_t matrix_mult_winograd_opt(const matrix_t *a, const matrix_t *b, matrix_t **r)
{
    matrix_error_t rc = MATRIX_OK;
    double *row_factor = NULL, *col_factor = NULL;
    if (a == NULL || a->data == NULL || b == NULL || b->data == NULL || a->cols != b->rows || r == NULL || *r != NULL)
        rc = MATRIX_INVALID_PARAM;
    else if (!(*r = matrix_create(a->rows, b->cols)))
        rc = MATRIX_MEM;
    else if ((rc = calc_row_factor_opt(a, &row_factor)) != MATRIX_OK)
        matrix_free(r);
    else if ((rc = calc_col_factor_opt(b, &col_factor)) != MATRIX_OK)
        matrix_free(r), free(row_factor);
    else
    {
        int flag = a->cols % 2;
        for (size_t i = 0; i < a->rows; i++)
        {
            for (size_t j = 0; j < b->cols; j++)
            {
                (*r)->data[i][j] = row_factor[i] + col_factor[j];
                for (size_t k = 1; k < a->cols; k += 2)
                    (*r)->data[i][j] += (a->data[i][k] + b->data[k - 1][j]) * (a->data[i][k - 1] + b->data[k][j]);
                if (flag)
                    (*r)->data[i][j] += a->data[i][a->cols - 1] * b->data[b->rows - 1][j];
            }
        }
        free(row_factor);
        free(col_factor);
    }
    return rc;
}

void matrix_mult_standart_unsafe(const matrix_t *a, const matrix_t *b, matrix_t **r)
{
    *r = matrix_create(a->rows, b->cols);
    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < b->cols; j++)
            for (size_t k = 0; k < (*r)->cols; k++)
                (*r)->data[i][j] += a->data[i][k] * b->data[k][j];
}

void calc_row_factor_unsafe(const matrix_t *matrix, double **row_factor)
{
    *row_factor = calloc(matrix->rows, sizeof(double));
    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->cols / 2; j++)
            (*row_factor)[i] += matrix->data[i][2 * j] * matrix->data[i][2 * j + 1];
}

void calc_col_factor_unsafe(const matrix_t *matrix, double **col_factor)
{
    *col_factor = calloc(matrix->cols, sizeof(double));
    for (size_t i = 0; i < matrix->rows / 2; i++)
        for (size_t j = 0; j < matrix->cols; j++)
            (*col_factor)[j] += matrix->data[2 * i][j] * matrix->data[2 * i + 1][j];
}

void matrix_mult_winograd_unsafe(const matrix_t *a, const matrix_t *b, matrix_t **r)
{
    double *row_factor = NULL, *col_factor = NULL;
    *r = matrix_create(a->rows, b->cols);
    calc_row_factor_unsafe(a, &row_factor);
    calc_col_factor_unsafe(b, &col_factor);

    for (size_t i = 0; i < a->rows; i++)
    {
        for (size_t j = 0; j < b->cols; j++)
        {
            (*r)->data[i][j] = -row_factor[i] - col_factor[j];
            for (size_t k = 0; k < a->cols / 2; k++)
                (*r)->data[i][j] += (a->data[i][2 * k + 1] + b->data[2 * k][j]) * (a->data[i][2 * k] + b->data[2 * k + 1][j]);
        }
    }
    if (a->cols % 2)
        for (size_t i = 0; i < a->rows; i++)
            for (size_t j = 0; j < b->cols; j++)
                (*r)->data[i][j] += a->data[i][a->cols - 1] * b->data[b->rows - 1][j];
    free(row_factor);
    free(col_factor);
}

void calc_row_factor_opt_unsafe(const matrix_t *matrix, double **row_factor)
{
    *row_factor = calloc(matrix->rows, sizeof(double));
    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 1; j < matrix->cols; j += 2)
            (*row_factor)[i] -= matrix->data[i][j - 1] * matrix->data[i][j];
}

void calc_col_factor_opt_unsafe(const matrix_t *matrix, double **col_factor)
{
    *col_factor = calloc(matrix->cols, sizeof(double));
    for (size_t i = 1; i < matrix->rows; i += 2)
        for (size_t j = 0; j < matrix->cols; j++)
            (*col_factor)[j] -= matrix->data[i - 1][j] * matrix->data[i][j];
}

void matrix_mult_winograd_opt_unsafe(const matrix_t *a, const matrix_t *b, matrix_t **r)
{
    double *row_factor = NULL, *col_factor = NULL;
    *r = matrix_create(a->rows, b->cols);
    calc_row_factor_opt_unsafe(a, &row_factor);
    calc_col_factor_opt_unsafe(b, &col_factor);

    int flag = a->cols % 2;
    for (size_t i = 0; i < a->rows; i++)
    {
        for (size_t j = 0; j < b->cols; j++)
        {
            (*r)->data[i][j] = row_factor[i] + col_factor[j];
            for (size_t k = 1; k < a->cols; k += 2)
                (*r)->data[i][j] += (a->data[i][k] + b->data[k - 1][j]) * (a->data[i][k - 1] + b->data[k][j]);
            if (flag)
                (*r)->data[i][j] += a->data[i][a->cols - 1] * b->data[b->rows - 1][j];
        }
    }
    free(row_factor);
    free(col_factor);
}
