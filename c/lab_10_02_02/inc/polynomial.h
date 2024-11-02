/**
 * @file polynomial.h
 * @brief Модуль для структуры члена полинома и работы с ними
 */

#ifndef __POLYNOMIAL__H__
#define __POLYNOMIAL__H__

#include "consts.h"
#include "list.h"

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

#define _POSIX_C_SOURCE 200809L

// Структура члена полинома
typedef struct
{
    int coefficient;    // Коэффициент
    int power;          // Степень
} term_t;

// Функции для ввода/вывода списка полинома
int read_polynomial_list(node_t **polynomial);

void print_polynomial_list(node_t *polynomial);

int read_variable_value(int *value);

void print_result(int value);

// Функции для работы со списками полиномов
int calculate(node_t *polynomial, int x);

void derivative(node_t **polynomial);

node_t *add(node_t **polynomial1, node_t **polynomial2);

void divide(node_t **polynomial_src, node_t **polynomial1, node_t **polynomial2);
// Функция освобождения памяти структур
void free_polynomial_list(node_t **head);

void free_term(term_t *polynomial);

// Функция сравнения членов по степеням
int compare_by_power(const void *p, const void *q);

#endif
