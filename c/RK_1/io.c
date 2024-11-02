#include "io.h"

int read_3d(matrix_t *matrix)
{
	int rc = OK;
	if (scanf("%zu %zu %zu", &matrix->n, &matrix->m, &matrix->l) != 3)
		rc = ERR;
	else if (matrix->matrix = alloc(matrix->n, matrix->m, matrix->l), matrix->matrix == NULL)
		rc = ERR;
	else if (matrix->n == 0 || matrix->m == 0 || matrix->l == 0)
		rc = ERR;
	else
	{
		size_t count = 0;
		while (count < matrix->n*matrix->m*matrix->l && rc == OK)
			if (scanf("%d", (int *) matrix->matrix + count) == 1)
				count++;
			else
				rc = ERR;
	}
	return rc;
}

void print_3d(matrix_t matrix)
{
	printf("3D:\n");
	for (size_t k = 0; k < matrix.l; k++)
	{
		for (size_t i = 0; i < matrix.n; i++)
		{
			for (size_t j = 0; j < matrix.m; j++)
				printf("%d ",*((int *) matrix.matrix + matrix.n*matrix.m*k + matrix.m*i + j));
			printf("\n");
		}
		printf("\n");
	}
}

void print_2d(matrix2d_t matrix)
{
	printf("2D:\n");
	for (size_t i = 0; i < matrix.n; i++)
	{
		for (size_t j = 0; j < matrix.m; j++)
			printf("%d ",*((int *) matrix.matrix + matrix.m*i + j));
		printf("\n");
	}
}
