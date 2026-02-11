/**
* Модуль для пользовательского интерфейса.
*/ 

#ifndef __UI__H__
#define __UI__H__

// Директивы включений
#include "consts.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _POSIX_C_SOURCE 200809L

// Функции

// Функции вывода меню и информации о программе
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
 * @brief
 * 
 * @param str 
 * @return int 
 * Указатель *str нужно будет очистить
 */
int get_input(char **str, FILE *f);

// Функции чтения из командной строки
/**
 * @brief Чтение строки определенной длины из стандартного потока ввода
 * 
 * @param pch указатель на принимаемую строку
 * @param n длина строки
 * @return int код возврата
 */
int get_n_input(char pch[], size_t n);

/**
 * @brief Получение выбранного пользователем пункта
 * 
 * @param option выбранный пункт
 * @return int код возврата
 */
int get_option(size_t *option);


// Функции вывода сообщений об ошибке
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
