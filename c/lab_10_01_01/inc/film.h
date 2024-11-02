/**
 * @file film.h
 * @brief Модуль для структуры фильма и работы с ним
 */

#ifndef __FILM__H__
#define __FILM__H__

#include "consts.h"
#include "list.h"

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

// Структура фильма
typedef struct
{
    char *title;
    char *name;
    int year;
} film_t;

// Основные функции для работы со списком фильмов
int read_film_list(char *file_name, node_t **film_arr);

int write_film_list(char *file_name, node_t *film_arr);

// Функция освобождения памяти структур
void free_film_list(node_t **film_list);

void free_film(film_t *film);

// Функции сравнения фильмов по полям
int compare_by_year(const void *p, const void *q);

#endif