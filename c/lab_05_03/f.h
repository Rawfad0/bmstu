/**
 * Модуль для основных вычислений программы
 */ 

#ifndef __F__H__
#define __F__H__

// Директивы препроцессора
#include "consts.h"
#include "bin.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Объявления функций
void fill_random_int_bin_file(FILE *f, size_t num);

int print_int_bin_file(FILE *f);

int sort_int_bin_file(FILE *f);

#endif
