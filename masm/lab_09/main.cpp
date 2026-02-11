#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>

struct matrix
{
    float **data;
    size_t n;
    size_t m;
};
typedef matrix matrix_t;

matrix_t matrix_alloc(size_t n, size_t m)
{
    matrix_t matrix;
    matrix.n = n;
    matrix.m = m;

    matrix.data = (float **) calloc(matrix.n, sizeof(float*));

    for (size_t i = 0; i < matrix.n; i++)
        matrix.data[i] = (float *)calloc(matrix.m, sizeof(float));

    return matrix;
}
void matrix_free(matrix_t &matrix)
{
    for (size_t i = 0; i < matrix.n; i++)
    {
        if (matrix.data[i])
            free(matrix.data[i]);
        matrix.data[i] = NULL;
    }

    if (matrix.data)
        free(matrix.data);
    
    matrix.data = NULL;
    matrix.n = 0;
    matrix.m = 0;
}

void read_size(size_t &n, size_t &m)
{
    std::cout << "Enter rows count: ";
    std::cin >> n;

    std::cout << "Enter cols count: ";
    std::cin >> m;
}

void matrix_data_read(matrix_t &matrix, size_t rows, size_t cols)
{
    std::cout << "Enter matrix elements:" << std::endl;

    matrix = matrix_alloc(rows, cols);

    for (size_t i = 0; i < matrix.n; i++)
        for (size_t j = 0; j < matrix.m; j++)
            std::cin >> matrix.data[i][j];
}

void matrix_read(matrix &matrix)
{
    read_size(matrix.n, matrix.m);
    matrix_data_read(matrix, matrix.n, matrix.m);
}

void matrix_print(matrix_t &matrix)
{
    for (size_t i = 0; i < matrix.n; i++)
    {
        for (size_t j = 0; j < matrix.m; j++)
            std::cout << matrix.data[i][j] << "\t";
        std::cout << std::endl;
    }
}

matrix_t matrix_transpose(matrix_t &matrix)
{
    matrix_t res = matrix_alloc(matrix.m, matrix.n);

    for (size_t i = 0; i < matrix.n; i++)
        for (size_t j = 0; j < matrix.m; j++)
            res.data[j][i] = matrix.data[i][j];

    return res;
}

static float dot_product(float *a, float *b, size_t m)
{
    float tmp = 0;
    for (size_t k = 0; k < m; k++)
        tmp += a[k] * b[k];

    return tmp;
}


void pack(float* a, float* b, size_t need, size_t have)
{
    size_t i = 0;
    while (i < have && i < need)
    {
        a[i] = b[i];
        i++;
    }
    while (i < need)
    {
        a[i] = 0;
        i++;
    }
}

float dot_product_asm(float* a, float* b, size_t size)
{
    // В 128-битном регистре xxmi помещается 4 32-битных float'а
    // Поэтому имеет смысл отправлять скомпонованные по четыре чИсла
    // float a_buf[4];     // Упакованные 4 числа из первой матрицы 
    // float b_buf[4];     // Упакованные 4 числа из второй матрицы
    float tmp = 0;
    float res = 0;

    for (size_t i = 0; i < size; i += 4, a += 4, b += 4)
    {
        // pack(a_buf, a, 4, (size - i));  
        // pack(b_buf, b, 4, (size - i));
        __asm(
            "mov %%rax, %1  \n"
            "mov %%rbx, %2  \n"
            "movups xmm0, [%%rax]   \n"
            "movups xmm1, [%%rbx]   \n"
            // "movss , %2   \n"
            // "movups xmm0, [%1]    \n" // Загрузка первой группы в нулевой регистр
            // "movups xmm1, [%2]    \n" // Загрузка второй группы в первый регистр
            "mulps xmm0, xmm1   \n" // Их поэлементное умножение (результат в xmm0)
            "haddps xmm0, xmm0  \n" // Дважды попарно сложить (горизонтальное в xmm0)
            "haddps xmm0, xmm0  \n" 
            "movss %0, xmm0     \n" // Выгрузить результат в tmp
            :"=m"(tmp)
            :"m"(a), "m"(b)
            // :"r"(a), "r"(b)
            // :"m"(((__float128 *)a)), "m"(((__float128 *)b))
            // :"m"(*((__float128 *)a)), "m"(*((__float128 *)b))
            :"xmm0", "xmm1", "rax", "rbx"
        );
        res += tmp;
    }

    return res;
}

matrix_t matrix_mul(matrix_t &a, matrix_t &b)
{
    matrix_t trans_b = matrix_transpose(b);

    matrix_t res = matrix_alloc(a.n, b.m);

    for (size_t i = 0; i < res.n; i++)
        for (size_t j = 0; j < res.m; j++)
            res.data[i][j] = dot_product(a.data[i], trans_b.data[j], a.m);
    matrix_free(trans_b);

    return res;
}

matrix_t matrix_mul_sse(matrix_t &a, matrix_t &b)
{
    matrix_t trans_b = matrix_transpose(b);

    matrix_t res = matrix_alloc(a.n, b.m);

    for (size_t i = 0; i < res.n; i++)
        for (size_t j = 0; j < res.m; j++)
            res.data[i][j] = dot_product_asm(a.data[i], trans_b.data[j], a.m);

    matrix_free(trans_b);

    return res;
}

int main()
{
    int rc = 0;
    matrix_t a, b;

    std::cout << "\nA matrix:\n";
    matrix_read(a);

    std::cout << "\nB matrix:\n";
    matrix_read(b);

    std::cout << "\nA:\n";
    matrix_print(a);
    std::cout << "\nB:\n";
    matrix_print(b);

    if (a.m != b.n)
    {
        std::cout << "\nError: The number of columns in the first matrix should be equal to the number of rows in the second.\n";
        rc = -1;
    }
    else
    {
        matrix_t res;
        std::cout << "\nResult CPP:\n";
        res = matrix_mul(a, b);
        matrix_print(res);
        matrix_free(res);

        std::cout << "\nResult ASM:\n";
        res = matrix_mul_sse(a, b);
        matrix_print(res);
        matrix_free(res);
    }

    matrix_free(a);
    matrix_free(b);

    return rc;
}