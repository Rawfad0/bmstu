/**
* Модуль для вывода фильмов
*/ 

#ifndef __IO__H__
#define __IO__H__

// Директивы препроцессора
#include "consts.h"
#include "structs.h"
#include <string.h>
#include <stdio.h>

// Объявления функций

/**
 * @brief Чтение предметов из текстового файла
 * 
 * @param file_name имя файла
 * @param obj_arr массив предметов
 * @param n количество предметов
 * @return int код возврата
 */
int read_objects(char *file_name, struct object *obj_arr, size_t *n);

/**
 * @brief Вывод предметов
 * 
 * @param obj_arr массив предметов
 * @param n количество предметов
 */
void print_all_objects(struct object *obj_arr, size_t n);

#endif
