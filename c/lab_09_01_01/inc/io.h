/**
 * @file io.h
 * @brief Модуль вывода фильмов
 * 
 */

#ifndef __IO__H__
#define __IO__H__

#include "consts.h"
#include "film.h"
#include <stdio.h>

// Функции
void print_film(film_t film);

void print_film_arr(film_arr_t film_arr);

#endif
