/**
 * Модуль содержащий структуры и методы работы с матрицами
 */ 

#ifndef __KEY__H__
#define __KEY__H__

// Директивы препроцессора
#include "consts.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>


/**
 * @brief Структура стандартной матрицы
 * 
 */
typedef struct
{
    int **matrix;   // Указатель на массив указателей на строки матрицы
    size_t n, m;    // Количество строк и столбцов соответственно
} matrix_t;

/**
 * @brief Структура разреженной матрицы
 * 
 */
typedef struct
{
    int *a;     // Вектор A ненулевых элементов
    size_t *ia; // Вектор IA номеров элементов с которых начинается описание i-й строки 
    size_t *ja; // Вектор JA номеров столбцов элементов вектора A
    size_t n, m;// Количество строк и столбцов соответственно
    size_t k;   // Количество ненулевых элементов 
} sparse_matrix_t;

// Объявления функций

/**
 * @brief Выделение памяти под матрицу
 * 
 * @param n количество строк в матрице
 * @param m количество столбцов в матрице
 * @return int** указаетель на массив n указателей на начала строк матрицы
 */
int **allocate_matrix(size_t n, size_t m);

/**
 * @brief Является ли разреженная матрица
 * 
 * @param matrix 
 * @return int 
 */
int is_matrix_valid(matrix_t matrix);

/**
 * @brief Освобождение матрицы
 * 
 * @param matrix матрица
 */
void free_matrix(matrix_t *matrix); 

/**
 * @brief 
 * 
 * @param matrix1 
 * @param matrix2 
 * @param matrix_res 
 * @return int 
 */
int matrix_addition(matrix_t matrix1, matrix_t matrix2, matrix_t *matrix_res);

/**
 * @brief Создание разреженной матрицы
 * 
 * @param n количество строк
 * @param m количество стоблцов
 * @return sparse_matrix_t разреженная матрица
 */
sparse_matrix_t create_sparse_matrix(size_t n, size_t m);

/**
 * @brief Проверка разреженной матрицы на корректность
 * 
 * @param matrix матрица
 * @return int код возврата
 */
int is_sparse_matrix_valid(sparse_matrix_t matrix);

/**
 * @brief Проверка матрицы на корректность
 * 
 * @param matrix матрица
 * @return int код возврата
 */
void free_sparse_matrix(sparse_matrix_t *matrix);

/**
 * @brief Сложение разреженных матриц
 * 
 * @param matrix1 первая матрица
 * @param matrix2 вторая матрица
 * @param matrix_res получившаяся матрица
 * @return int код возврата
 */
int sparse_matrix_addition(sparse_matrix_t matrix1, sparse_matrix_t matrix2, sparse_matrix_t *matrix_res);

/**
 * @brief Создание разреженной матрицы на основе обычной
 * 
 * @param matrix матрица
 * @return sparse_matrix_t разреженная матрица 
 */
sparse_matrix_t matrix_std_to_sparse(matrix_t matrix);

/**
 * @brief Создание матрицы на основе разреженной матрице
 * 
 * @param matrix разреженная матрица
 * @return matrix_t матрица
 */
matrix_t matrix_sparse_to_std(sparse_matrix_t matrix);

/**
 * @brief Сравнение алгоритмов сложения
 * 
 * @param matrix1 первая матрица
 * @param matrix2 вторая матрица
 * @param sparse_matrix1 первая разреженная матрица
 * @param sparse_matrix2 вторая разреженная матрица
 * @return int код возврата
 */
int compare(matrix_t matrix1, matrix_t matrix2, sparse_matrix_t sparse_matrix1, sparse_matrix_t sparse_matrix2);

void print_sparse_matrix(sparse_matrix_t matrix);

#endif
