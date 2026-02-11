#ifndef __STATIC__ARRAY__STACK__H__
#define __STATIC__ARRAY__STACK__H__

#include <stdio.h>

#include "consts.h"

// Длина статического массива
#define MAX_ARR_LEN 10000

// Структура стека на статическом массиве
typedef struct
{
    char array[MAX_ARR_LEN];// Статический массив символов длиной MAX_ARR_LEN
    char *pe;               // Указатель за конец массива
    char *sp;               // Указатель за текущий элемент стека
} sa_stack_t;

// Операции со стеком
int sa_push(sa_stack_t *stack, char element);

int sa_pop(sa_stack_t *stack, char *element);

void sa_print(sa_stack_t *stack);

#endif
