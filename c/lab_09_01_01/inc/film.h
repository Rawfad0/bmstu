/**
 * @file film.h
 * @brief Модуль для структуры фильма и работы с ним
 */

#ifndef __FILM__H__
#define __FILM__H__

#include "consts.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _POSIX_C_SOURCE 200809L

// Структура фильма
typedef struct
{
    char *title;
    char *name;
    int year;
} film_t;

// Струтура динамического массива фильмов
typedef struct
{
    film_t *arr;
    size_t n;
} film_arr_t;

// Основные функции для работы с массивом фильмов
int read_film_array(char *file_name, film_arr_t *film_arr, int (*compar)(const void*, const void*));

film_t *find_film(film_arr_t film_arr, char *field, char *key, int (*compar)(const void*, const void*));

// Функция освобождения памяти структур
void free_film(film_t *film);

void free_film_arr(film_arr_t *film_arr);

// Функции сравнения фильмов по полям
int compare_by_title(const void *p, const void *q);

int compare_by_name(const void *p, const void *q);

int compare_by_year(const void *p, const void *q);

#endif
