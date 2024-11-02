#include "consts.h"
#include "io.h"
#include "matrix.h"
#include <string.h>

int controller(int argc, char **argv);

int main(int argc, char **argv)
{
    int rc = RC_OK;
    if (argc != ARGC_1_FILE_INPUT && argc != ARGC_2_FILE_INPUT)
        rc = RC_INCORRECT_ARG_COUNT;
    else
        rc = controller(argc, argv);
    
    return rc;
}

int addition_controller(char *file_in_1, char *file_in_2, char *file_out)
{
    int rc = RC_OK;
    matrix_t matrix1 = { NULL, 0, 0 }, matrix2 = { NULL, 0, 0 }, matrix_res = { NULL, 0, 0 };
    if ((rc = read_matrix(file_in_1, &matrix1)));
    else if ((rc = read_matrix(file_in_2, &matrix2)));
    else if (matrix1.n != matrix2.n || matrix1.m != matrix2.m)
        rc = RC_INCORRECT_SIZE;
    else if (matrix_res.matrix = allocate_matrix(matrix1.n, matrix1.m), matrix_res.matrix == NULL)
        rc = RC_ALLOCATION_FAILED;
    else
    {
        matrix_addition(matrix1, matrix2, &matrix_res);
        rc = write_matrix(file_out, matrix_res);
    }
    free(matrix1.matrix), free(matrix2.matrix), free(matrix_res.matrix);
    return rc;
}

int multiplication_controller(char *file_in_1, char *file_in_2, char *file_out)
{
    int rc = RC_OK;
    matrix_t matrix1 = { NULL, 0, 0 }, matrix2 = { NULL, 0, 0 }, matrix_res = { NULL, 0, 0 };
    if ((rc = read_matrix(file_in_1, &matrix1)));
    else if ((rc = read_matrix(file_in_2, &matrix2)));
    else if (matrix1.m != matrix2.n)
        rc = RC_INCORRECT_SIZE;
    else if ((matrix_res.matrix = allocate_matrix(matrix1.n, matrix2.m)) == NULL)
        rc = RC_ALLOCATION_FAILED;
    else
    {
        matrix_multiplication(matrix1, matrix2, &matrix_res);
        rc = write_matrix(file_out, matrix_res);
    }
    free(matrix1.matrix), free(matrix2.matrix), free(matrix_res.matrix);

    return rc;
}

int solve_controller(char *file_in, char *file_out)
{
    int rc = RC_OK;
    matrix_t matrix = { NULL, 0, 0 }, matrix_res = { NULL, 0, 0 };
    if ((rc = read_matrix(file_in, &matrix)));
    else if (matrix.n + 1 != matrix.m)
        rc = RC_INCORRECT_SIZE;
    else if ((matrix_res.matrix = allocate_matrix(matrix.n, 1)) == NULL)
        rc = RC_ALLOCATION_FAILED;
    else if ((rc = matrix_solve(matrix, &matrix_res)));
    else
        rc = write_matrix(file_out, matrix_res);
    free(matrix.matrix), free(matrix_res.matrix);

    return rc;
}

int controller(int argc, char **argv)
{
    int rc = RC_OK;
    if (strcmp(argv[1], ACTION_ADDITION) == 0 && argc == ARGC_2_FILE_INPUT)
        rc = addition_controller(argv[2], argv[3], argv[4]);
    else if (strcmp(argv[1], ACTION_MULTIPLICATION) == 0 && argc == ARGC_2_FILE_INPUT)
        rc = multiplication_controller(argv[2], argv[3], argv[4]);
    else if (strcmp(argv[1], ACTION_OPERATION) == 0 && argc == ARGC_1_FILE_INPUT)
        rc = solve_controller(argv[2], argv[3]);
    else
        rc = RC_INCORRECT_ACTION;
    return rc;
}
