#ifndef __DYNAMIC__ARRAY__STACK__H__
#define __DYNAMIC__ARRAY__STACK__H__

#include <stdlib.h>
#include <stdio.h>

#include "consts.h"

// Структура стека на динамическом массиве
typedef struct
{
    char *array;    // Статический массив символов длиной MAX_ARR_LEN
    // size_t n;       // Количество элементов в массиве
    size_t alloc_n; // Количество аллоцированных элементов
    char *sp;       // Указатель за текущий элемент стека
} da_stack_t;

// Операции со стеком
int da_push(da_stack_t *das, char element);

int da_pop(da_stack_t *das, char *element);

void da_print(da_stack_t *das);

void da_free(da_stack_t *das);

#endif
