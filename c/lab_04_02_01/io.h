/**
* Модуль для ввода строки и вывода слов
*/ 

#ifndef __IO__H__
#define __IO__H__

// Директивы препроцессора
#include "consts.h"

// Объявления функций
int line_input(char *line);

void print_str_array(char str_array[][WORD_MAX+1], size_t n);

#endif // __IO__H__
