#ifndef __IO__H__
#define __IO__H__

#include <stdio.h>
#include "matrix3.h"
#include "const.h"

int read_3d(matrix_t *matrix);
void print_3d(matrix_t matrix);

void print_2d(matrix2d_t matrix);
#endif