#include "f.h"

/*!
 * \brief Заполянет матрицу спиралью
 *
 * \param matrix матрица
 * \param m количество строк матрицы
 * \param n количество столбцов матрицы
 *
 * Данная функция принимает целочисленную квадратную матрицу matrix размера n на n,
 * затем заполняет её по спирали по часовой стреклке элементами от 1 до n*n.
 */
int matrix_spiral_fill(long int matrix[][N_MAX], size_t n)
{   
    long int k = 1;
    size_t x = 0;
    size_t y = 0;

    for (size_t round = 0; round < (n + 1) / 2; round++)
    {
        for (size_t i = 0; i < (n - 1 - 2 * round) * 4; i++)
        {
            matrix[y][x] = k++;

            if (x >= y && n - 1 - x > y)
                x++;
            else if (x > y && n - 1 - x <= y)
                y++;
            else if (x <= y && n - 1 - x < y)
                x--;
            else if (x < y && n - 1 - x >= y)
                y--;
        }
        x++;
        y++;
    }

    if (n % 2 == 1)
        matrix[(n - 1) / 2][(n - 1) / 2] = k;

    return 0;
}
