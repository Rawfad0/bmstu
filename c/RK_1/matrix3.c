#include "matrix3.h"

int ***alloc(size_t n, size_t m, size_t l)
{
	int ***matrix = malloc(sizeof(int)*n*m*l);
	if (matrix != NULL)
	{
		for (size_t k = 0; k < l; k++)
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < m; j++)
					*((int*)matrix + n*m*k + m*i + j) = 0;
	}
	return matrix;
}

int **alloc2d(size_t n, size_t m)
{
	int **matrix = malloc(sizeof(int)*n*m);
	if (matrix != NULL)
	{
		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < m; j++)
				*((int*)matrix + m*i + j) = 0;
	}
	return matrix;
}

int fill_2d(matrix_t matrix, matrix2d_t *matrix2)
{
	int rc = OK;
	if (matrix2->matrix = alloc2d(matrix.n, matrix.m), matrix2->matrix == NULL)
		rc = ERR;
	else
	{
		matrix2->n = matrix.n;
		matrix2->m = matrix.m;
		for (size_t i = 0; i < matrix2->n; i++)
			for (size_t j = 0; j < matrix2->m; j++)
				for (size_t k = 0; k < matrix.l; k++)
					*((int*)matrix2->matrix + matrix2->m*i + j) += *((int *) matrix.matrix + matrix.n*matrix.m*k + matrix.m*i + j);
	}
	return rc;
}
