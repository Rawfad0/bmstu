#include "matrix.h"

/**
 * @brief Выделение памяти под матрицу
 * 
 * @param n количество строк в матрице
 * @param m количество столбцов в матрице
 * @return double** указаетель на массив n указателей на начала строк матрицы
 */
double **allocate_matrix(size_t n, size_t m)
{
    double **matrix = malloc(n * sizeof(double*) + n * m * sizeof(double));
    if (matrix)
    {
        matrix[0] = (double *) (matrix + n);
        for (size_t i = 1; i < n; i++)
            matrix[i] = matrix[0] + m * i;
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < m; j++)
                matrix[i][j] = 0;
    }
    return matrix;
}

void matrix_addition(matrix_t matrix1, matrix_t matrix2, matrix_t *matrix_res)
{
    matrix_res->n = matrix1.n;
    matrix_res->m = matrix1.m;
    for (size_t i = 0; i < matrix1.n; i++)
        for (size_t j = 0; j < matrix1.m; j++)
            matrix_res->matrix[i][j] = matrix1.matrix[i][j] + matrix2.matrix[i][j];
}

void matrix_multiplication(matrix_t matrix1, matrix_t matrix2, matrix_t *matrix_res)
{
    matrix_res->n = matrix1.n;
    matrix_res->m = matrix2.m;
    for (size_t i = 0; i < matrix_res->n; i++)
        for (size_t j = 0; j < matrix_res->m; j++)
            for (size_t k = 0; k < matrix1.m; k++)
                matrix_res->matrix[i][j] += matrix1.matrix[i][k] * matrix2.matrix[k][j];
}

/**
 * @brief Поиск главного элемента в активной подматрице
 * 
 * @param matrix матрица
 * @param k с какого столбца и строчки матрицы начинается активная подматрица
 * @param i_max строка главного элемента
 * @param j_max столбец максимального элемента
 */
void find_max_in_active_matrix(matrix_t matrix, size_t k, size_t *i_max, size_t *j_max)
{
    *i_max = k, *j_max = k;
    for (size_t i = k; i < matrix.n; i++)
        for (size_t j = k; j < matrix.n; j++)
            if (fabs(matrix.matrix[i][j]) > fabs(matrix.matrix[*i_max][*j_max]) + MACHINE_EPS)
                *i_max = i, *j_max = j;
}

void swap(void *pa, void *pb, size_t size)
{
    char p_temp[size];
    memcpy(p_temp, pa, size);
    memcpy(pa, pb, size);
    memcpy(pb, p_temp, size);
}

void swap_rows(matrix_t matrix, size_t i, size_t j)
{
    swap((void *) (matrix.matrix + i), (void *) (matrix.matrix + j), sizeof(double *));
}

void swap_columns(matrix_t matrix, size_t i, size_t j)
{
    for (size_t row = 0; row < matrix.n; row++)
        swap(matrix.matrix[row] + i, matrix.matrix[row] + j, sizeof(double));
}

int make_triangle_matrix(matrix_t matrix, size_t column_swaps[])
{
    size_t i_max = 0, j_max = 0;
    int rc = RC_OK;
    for (size_t k = 0; k < matrix.n && rc == RC_OK; k++)
    {
        // Находим главный элемент в активной подматрице
        find_max_in_active_matrix(matrix, k, &i_max, &j_max);
        if (fabs(matrix.matrix[i_max][j_max]) < MACHINE_EPS)
            rc = RC_UNSOLVABLE_MATRIX;
        else
        {
            // Перемещаем главные строку и стобец так, чтобы он главный элемент оказался на диагонали
            if (k != matrix.n - 1)
            {
                column_swaps[k] = j_max;
                swap_columns(matrix, k, j_max);
                swap_rows(matrix, k, i_max);
            }
            // Нормирование главной строки
            for (size_t j = k + 1; j < matrix.m; j++)
                matrix.matrix[k][j] /= matrix.matrix[k][k];
            matrix.matrix[k][k] = 1;
            // Цикл вычитаний из последующих строк
            for (size_t i = k + 1; i < matrix.n; i++)
            {
                for (size_t j = k + 1; j < matrix.m; j++)
                    matrix.matrix[i][j] -= matrix.matrix[i][k] * matrix.matrix[k][j];
                matrix.matrix[i][k] -= matrix.matrix[i][k] * matrix.matrix[k][k];
            }
        }
    }
    return rc;
}

int matrix_solve(matrix_t matrix, matrix_t *matrix_res)
{
    size_t column_swaps[matrix.n - 1]; 
    int rc = RC_OK;
    if (rc = make_triangle_matrix(matrix, column_swaps), rc == RC_OK)
    {
        // Заполнение столбца решений на основе матрицы треугольного вида
        matrix_res->n = matrix.n;
        matrix_res->m = 1;
        for (int k = matrix.n - 1; k >= 0; k--)
        {
            matrix_res->matrix[k][0] = matrix.matrix[k][matrix.n] / matrix.matrix[k][k];
            for (int i = 0; i < k; i++)
                matrix.matrix[i][matrix.n] -= matrix.matrix[i][k] * matrix_res->matrix[k][0];
        }
        // Перестановка строк в столбце решений, т.к. столбцы матрицы были переставлены
        for (int k = matrix.n - 2; k >= 0; k--)
            swap_rows(*matrix_res, k, column_swaps[k]);
    }
    return rc;
}