/**
* Модуль для ввода/вывода
*/ 

#ifndef __IO__H__
#define __IO__H__

// Директивы препроцессора
#include "consts.h"
#include <string.h>
#include <stdio.h>

// Объявления функций

int count_int_arr_len(char *file_name, size_t *n);

int read_int_arr(char *file_name, int *pb, int *pe);

int write_int_arr(char *file_name, int *pb, int *pe);

#endif
