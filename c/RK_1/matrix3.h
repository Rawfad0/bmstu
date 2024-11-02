#ifndef __M__H__
#define __M__H__

#include <stddef.h>
#include <stdlib.h>
#include "const.h"

typedef struct
{
	int ***matrix;
	size_t n;
	size_t m;
	size_t l;
} matrix_t;

typedef struct
{
	int **matrix;
	size_t n;
	size_t m;
} matrix2d_t;

int ***alloc(size_t n, size_t m, size_t l);

int **alloc2d(size_t n, size_t m); 

int fill_2d(matrix_t matrix, matrix2d_t *matrix2);

#endif