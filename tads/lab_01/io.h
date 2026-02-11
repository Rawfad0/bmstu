/**
 * Модуль содержащий функции ввода/вывода 
 */

#ifndef __IO__H__
#define __IO__H__

// Директивы препроцессора
#include "consts.h"
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

// Объявления функций

/**
 * @brief Выводит меню и запрашивает действие
 * 
 * @param option выбранный пункт
 */
void menu_get_selected_option(int *option);

/**
 * @brief Выводит информацию о программе
 */
void info(void);

/**
 * @brief Ввод действительного числа
 * 
 * @param real_num_s строка с действительным числом 
 * @return int код возврата
 */
int input_real_num(char *real_num_s);

/**
 * @brief Ввод целого числа
 * 
 * @param integer_num_s строка с целым числом
 * @return int код возврата
 */
int input_int_num(char *integer_num_s);

/**
 * @brief Вывод результата
 * 
 * @param result_num строка с результатом
 */
void print_result(char *result_num);

#endif