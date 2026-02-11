/**
 * Модуль содержащий функцию сортировки и сравнения чисел
 */ 

#ifndef __SORTS__H__
#define __SORTS__H__

// Директивы препроцессора
#include <string.h>

// Объявления функций
/**
 * @brief Функция сортировки бинарными вставками
 * 
 * @param base Указатель на начало сортируемой области
 * @param nmemb количество элементов
 * @param size размер элемента
 * @param compar указатель на функцию сравнения элементов
 */
void insertion_sort(void *base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));

/**
 * @brief Функция сортировки бинарными вставками
 * 
 * @param base Указатель на начало сортируемой области
 * @param nmemb количество элементов
 * @param size размер элемента
 * @param compar указатель на функцию сравнения элементов
 */
void binary_insertion_sort(void *base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));

#endif