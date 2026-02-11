#ifndef __LINKED__LIST__STACK__H__
#define __LINKED__LIST__STACK__H__

#include <stdlib.h>
#include <stdio.h>

#include "consts.h"

// Структура стека на односвзяном списке
typedef struct list_t list_t;

struct list_t
{
    list_t *next;   // Указатель на следующий элемент списка
    char value;     // Значение
};

typedef struct
{
    list_t *sp; // Указатель на текущий элемент стека
} ll_stack_t;

// Операции со стеком
int ll_push(ll_stack_t *stack, char *element);

int ll_pop(ll_stack_t *stack, list_t **list_node);

void ll_print(ll_stack_t *stack);

void ll_free(ll_stack_t *stack);

#endif
