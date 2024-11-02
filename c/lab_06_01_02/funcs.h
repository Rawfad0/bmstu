/**
 * Модуль для основных вычислений программы
 */ 

#ifndef __FUNCS__H__
#define __FUNCS__H__

// Директивы препроцессора
#include "consts.h"
#include "structs.h"
#include <string.h>

// Объявления функций

/**
 * @brief Соортировка предметов по плотности
 * 
 * @param obj_arr массив предметов
 * @param n количество предметов
 */
void sort_objects_by_density(struct object *obj_arr, size_t n);

/**
 * @brief Поиск предметов начинающихся с префикса и их вывод 
 * 
 * @param obj_arr массив предметов
 * @param n количество предметов
 */
int find_prefix(struct object *obj_arr, size_t n, struct object *found_obj_arr, size_t *found_n, char *prefix);

#endif
