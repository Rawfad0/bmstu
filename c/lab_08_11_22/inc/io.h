/**
* Модуль для ввода/вывода
*/ 

#ifndef __IO__H__
#define __IO__H__

// Директивы препроцессора
#include "consts.h"
#include "matrix.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Объявления функций

int read_matrix(char *filename, matrix_t *matrix);

int write_matrix(char *filename, matrix_t matrix);

#endif
