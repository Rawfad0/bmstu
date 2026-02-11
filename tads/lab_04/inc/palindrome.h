/**
* Модуль, проверяющий, что строка в стеке является палиндромом.
*/ 

#ifndef __PALINDROME__H__
#define __PALINDROME__H__

// Директивы включений
#include "consts.h"
#include "static_array_stack.h"
#include "linked_list_stack.h"

#include <stdbool.h>

// Функции

bool sa_is_palindrome(sa_stack_t *word, size_t word_len);

bool ll_is_palindrome(ll_stack_t *word, size_t word_len);

#endif
