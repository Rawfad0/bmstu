/**
* Модуль для основных вычислений программы
*/ 

#ifndef __F__H__
#define __F__H__

// Директивы препроцессора
#include "consts.h"
#include "structs.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Объявления функций

/**
 * @brief Перевод из строки в структуру действительного числа
 * 
 * @param real_num_str строка с действительным числом
 * @param real_num действительное число
 * @return int код возврата
 */
int str_to_real_num(char *real_num_str, real_num *real_num);

/**
 * @brief Перевод из строки в структуру целого числа
 * 
 * @param integer_num_str строка с целым числом
 * @param integer_num целое число
 * @return int код возврата
 */
int str_to_int_num(char *integer_num_str, int_num *integer_num);

/**
 * @brief Перевод структуры результата в строку
 * 
 * @param res_num стркуктура результата
 * @param res_num_str строка результата
 * @return int код возврата
 */
int res_to_str(calc_num res_num, char *res_num_str);

/**
 * @brief Произведение чисел
 * 
 * @param real_num_str строка с действительным числом
 * @param integer_num_str строка с целым числом
 * @return int код возврата
 */
int calculate(real_num real_num, int_num integer_num, calc_num *res_num);

#endif // __F__H__
