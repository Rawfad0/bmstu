/**
 * Модуль для работы с бинарными файлами.
 */ 

#ifndef __BIN__H__
#define __BIN__H__

// Директивы препроцессора
#include "consts.h"
#include <stdio.h>

// Объявления функций
int bin_file_size(FILE *f, size_t *size);

int get_number_by_pos(FILE *f, size_t pos, int *num);

int put_number_by_pos(FILE *f, size_t pos, int *num);

#endif
