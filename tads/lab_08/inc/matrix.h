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
// #include <sys/time.h>

/**
 * @brief Структура стандартной матрицы
 * 
 */
typedef struct
{
    size_t **matrix;   // Указатель на массив указателей на строки матрицы
    size_t n, m;    // Количество строк и столбцов соответственно
} matrix_t;

/**
 * @brief Чтение матрицы из файла
 * 
 * @param filename имя файла
 * @param matrix матрица
 * @return int код возврата
 */
int read_matrix(char *filename, matrix_t *matrix);

/**
 * @brief Освобождение матрицы
 * 
 * @param matrix матрица
 */
void free_matrix(matrix_t *matrix); 

#endif
