/**
* Модуль для ввода/вывода
*/ 

#ifndef __IO__H__
#define __IO__H__

//
#include "consts.h"
#include "matrix.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

// 

/**
 * @brief Чтение матрицы из файла
 * 
 * @param filename имя файла
 * @param matrix матрица
 * @return int код возврата
 */
int read_matrix(char *filename, matrix_t *matrix); 

/**
 * @brief Ввод матрицы
 * 
 * @param matrix матрица
 * @return int код возврата
 */
int input_matrix(matrix_t *matrix);

/**
 * @brief Вывод матрицу в виде таблицы 
 * 
 * @param matrix матрица
 */
void print_matrix_as_table(matrix_t matrix);

/**
 * @brief Контроллер вывода матрицы
 * 
 * @param matrix матрица
 */
void print_matrix(matrix_t matrix);

/**
 * @brief Вывод меню программы
 * 
 */
void print_menu(void);

/**
 * @brief Вывод информации о программе
 * 
 */
void print_info(void);

/**
 * @brief Чтение строки определенной длины из стандартного потока ввода
 * 
 * @param pch указатель на принимаемую строку
 * @param n длина строки
 * @return int код возврата
 */
int get_input(char pch[], size_t n);

/**
 * @brief Получение выбранного пользователем пункта
 * 
 * @param option выбранный пункт
 * @return int код возврата
 */
int get_option(size_t *option);

/**
 * @brief Вывод сообщения, пояснящего ошибку
 * 
 * @param rc код возврата
 */
void print_error_msg(int rc);

/**
 * @brief Вывод сообщения, пояснящего ошибку, и возврат того же кода возврата
 * 
 * @param rc код возврата
 * @return int код возврата
 */
int print_error(int rc);

#endif
