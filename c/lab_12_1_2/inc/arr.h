/**
 * Модуль содержащий функции для работы с массивом:
 * Вариант 1
 * 1. Реализовать функцию циклического сдвига массива на k позиций влево.
 * 2. Реализовать функцию, которая из одного массива помещает в другой
 * элементы первого, которые являются полными квадратами.
 */ 

#ifndef __ARR__H__
#define __ARR__H__

#include <math.h>
#include <stddef.h>

// Объявления функций
void k_left_cycle_shift(int *arr, size_t n, size_t k);

int count_new_arr_len(int *arr, size_t n);

void filter_squares(int *arr_src, size_t n_src, int *arr_dst);

#endif