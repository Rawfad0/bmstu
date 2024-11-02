#include <stdio.h>
#include "matrix3.h"
#include "io.h"
#include <stdlib.h>

int main(void)
{
	matrix_t matrix = {NULL, 0, 0, 0};
	matrix2d_t matrix2d = {NULL, 0, 0};
	int rc = OK;
	if (rc = read_3d(&matrix), rc != OK);
	else if (rc = fill_2d(matrix, &matrix2d), rc != OK);
	else 
	{
		print_3d(matrix);
		print_2d(matrix2d);
	}
	free(matrix.matrix);
	free(matrix2d.matrix);
	return rc;
}
