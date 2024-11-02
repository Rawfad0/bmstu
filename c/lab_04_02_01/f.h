/**
* Модуль для основных вычислений программы
*/ 

#ifndef __F__H__
#define __F__H__

// Директивы препроцессора
#include "consts.h"

// Объявления функций
int split_line_to_array(char *line, char str_array[][WORD_MAX+1], size_t *n);

void str_array_sort(char str_array[][WORD_MAX+1], size_t n);

int is_valid_line(char *line);

#endif // __F__H__
