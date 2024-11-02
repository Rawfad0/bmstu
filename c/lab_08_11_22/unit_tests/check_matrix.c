#include "matrix.h"
#include "io.h"
#include "consts.h"
#include <math.h>
#include <check.h>
#include <stdlib.h>

START_TEST(test_sum_2_matrix)
{
    matrix_t matrix1 = { NULL, 0, 0 }, matrix2 = { NULL, 0, 0 }, matrix_res = { NULL, 0, 0 }, matrix_res_exp = { NULL, 0, 0 };
    if ((read_matrix("func_tests/data/pos_01_in.txt", &matrix1)));
    else if ((read_matrix("func_tests/data/pos_01_in2.txt", &matrix2)));
    else if ((read_matrix("func_tests/data/pos_01_out.txt", &matrix_res_exp)));
    else if (matrix1.n != matrix2.n || matrix1.m != matrix2.m);
    else if (matrix_res.matrix = allocate_matrix(matrix1.n, matrix1.m), matrix_res.matrix == NULL);
    else
    {
        matrix_addition(matrix1, matrix2, &matrix_res);

        for (size_t i = 0; i < matrix1.n; i++)
            for (size_t j = 0; j < matrix1.n; j++)
                ck_assert_double_lt(fabs(matrix_res.matrix[i][j] - matrix_res_exp.matrix[i][j]), MACHINE_EPS);
    }
    free(matrix1.matrix), free(matrix2.matrix), free(matrix_res.matrix), free(matrix_res_exp.matrix);
}
END_TEST

START_TEST(test_sum_with_negative_matrix)
{
    matrix_t matrix1 = { NULL, 0, 0 }, matrix2 = { NULL, 0, 0 }, matrix_res = { NULL, 0, 0 }, matrix_res_exp = { NULL, 0, 0 };
    if ((read_matrix("func_tests/data/pos_02_in.txt", &matrix1)));
    else if ((read_matrix("func_tests/data/pos_02_in2.txt", &matrix2)));
    else if ((read_matrix("func_tests/data/pos_02_out.txt", &matrix_res_exp)));
    else if (matrix1.n != matrix2.n || matrix1.m != matrix2.m);
    else if (matrix_res.matrix = allocate_matrix(matrix1.n, matrix2.m), matrix_res.matrix == NULL);
    else
    {
        matrix_addition(matrix1, matrix2, &matrix_res);

        for (size_t i = 0; i < matrix1.n; i++)
            for (size_t j = 0; j < matrix1.n; j++)
                ck_assert_double_lt(fabs(matrix_res.matrix[i][j] - matrix_res_exp.matrix[i][j]), MACHINE_EPS);
    }
    free(matrix1.matrix), free(matrix2.matrix), free(matrix_res.matrix), free(matrix_res_exp.matrix);
}
END_TEST

START_TEST(test_mult_matrix)
{
    matrix_t matrix1 = { NULL, 0, 0 }, matrix2 = { NULL, 0, 0 }, matrix_res = { NULL, 0, 0 }, matrix_res_exp = { NULL, 0, 0 };
    if ((read_matrix("func_tests/data/pos_03_in.txt", &matrix1)));
    else if ((read_matrix("func_tests/data/pos_03_in2.txt", &matrix2)));
    else if ((read_matrix("func_tests/data/pos_03_out.txt", &matrix_res_exp)));
    else if (matrix1.n != matrix2.n || matrix1.m != matrix2.m);
    else if (matrix_res.matrix = allocate_matrix(matrix1.n, matrix2.m), matrix_res.matrix == NULL);
    else
    {
        matrix_multiplication(matrix1, matrix2, &matrix_res);

        for (size_t i = 0; i < matrix1.n; i++)
            for (size_t j = 0; j < matrix2.m; j++)
                ck_assert_double_lt(fabs(matrix_res.matrix[i][j] - matrix_res_exp.matrix[i][j]), MACHINE_EPS);
    }
    free(matrix1.matrix), free(matrix2.matrix), free(matrix_res.matrix), free(matrix_res_exp.matrix);
}
END_TEST

START_TEST(test_mult_unit_matrix)
{
    matrix_t matrix1 = { NULL, 0, 0 }, matrix2 = { NULL, 0, 0 }, matrix_res = { NULL, 0, 0 }, matrix_res_exp = { NULL, 0, 0 };
    if ((read_matrix("func_tests/data/pos_04_in.txt", &matrix1)));
    else if ((read_matrix("func_tests/data/pos_04_in2.txt", &matrix2)));
    else if ((read_matrix("func_tests/data/pos_04_out.txt", &matrix_res_exp)));
    else if (matrix1.m != matrix2.n);
    else if (matrix_res.matrix = allocate_matrix(matrix1.n, matrix2.m), matrix_res.matrix == NULL);
    else
    {
        matrix_multiplication(matrix1, matrix2, &matrix_res);

        for (size_t i = 0; i < matrix1.n; i++)
            for (size_t j = 0; j < matrix2.m; j++)
                ck_assert_double_lt(fabs(matrix_res.matrix[i][j] - matrix_res_exp.matrix[i][j]), MACHINE_EPS);
    }
    free(matrix1.matrix), free(matrix2.matrix), free(matrix_res.matrix), free(matrix_res_exp.matrix);
}
END_TEST

START_TEST(test_mult_zero_matrix)
{
    matrix_t matrix1 = { NULL, 0, 0 }, matrix2 = { NULL, 0, 0 }, matrix_res = { NULL, 0, 0 }, matrix_res_exp = { NULL, 0, 0 };
    if ((read_matrix("func_tests/data/pos_05_in.txt", &matrix1)));
    else if ((read_matrix("func_tests/data/pos_05_in2.txt", &matrix2)));
    else if ((read_matrix("func_tests/data/pos_05_out.txt", &matrix_res_exp)));
    else if (matrix1.m != matrix2.n);
    else if (matrix_res.matrix = allocate_matrix(matrix1.n, matrix1.m), matrix_res.matrix == NULL);
    else
    {
        matrix_multiplication(matrix1, matrix2, &matrix_res);

        for (size_t i = 0; i < matrix1.n; i++)
            for (size_t j = 0; j < matrix2.m; j++)
                ck_assert_double_lt(fabs(matrix_res.matrix[i][j] - matrix_res_exp.matrix[i][j]), MACHINE_EPS);
    }
    free(matrix1.matrix), free(matrix2.matrix), free(matrix_res.matrix), free(matrix_res_exp.matrix);
}
END_TEST

START_TEST(test_solve_1x2_matrix)
{
    matrix_t matrix1 = { NULL, 0, 0 }, matrix_res = { NULL, 0, 0 }, matrix_res_exp = { NULL, 0, 0 };
    if ((read_matrix("func_tests/data/pos_06_in2.txt", &matrix1)));
    else if ((read_matrix("func_tests/data/pos_06_out.txt", &matrix_res_exp)));
    else if (matrix1.n + 1 != matrix1.m);
    else if (!(matrix_res.matrix = allocate_matrix(matrix1.m, 1)));
    else
    {
        matrix_solve(matrix1, &matrix_res);

        for (size_t i = 0; i < matrix_res_exp.n; i++)
            for (size_t j = 0; j < matrix_res_exp.m; j++)
                ck_assert_double_lt(fabs(matrix_res.matrix[i][j] - matrix_res_exp.matrix[i][j]), MACHINE_EPS);
    }
    free(matrix1.matrix), free(matrix_res.matrix), free(matrix_res_exp.matrix);
}
END_TEST

START_TEST(test_solve_2x3_matrix)
{
    matrix_t matrix1 = { NULL, 0, 0 }, matrix_res = { NULL, 0, 0 }, matrix_res_exp = { NULL, 0, 0 };
    if ((read_matrix("func_tests/data/pos_07_in2.txt", &matrix1)));
    else if ((read_matrix("func_tests/data/pos_07_out.txt", &matrix_res_exp)));
    else if (matrix1.n + 1 != matrix1.m);
    else if (!(matrix_res.matrix = allocate_matrix(matrix1.m, 1)));
    else
    {
        matrix_solve(matrix1, &matrix_res);

        for (size_t i = 0; i < matrix_res_exp.n; i++)
            for (size_t j = 0; j < matrix_res_exp.m; j++)
                ck_assert_double_lt(fabs(matrix_res.matrix[i][j] - matrix_res_exp.matrix[i][j]), MACHINE_EPS);
    }
    free(matrix1.matrix), free(matrix_res.matrix), free(matrix_res_exp.matrix);
}
END_TEST

START_TEST(test_solve_3x4_matrix)
{
    matrix_t matrix1 = { NULL, 0, 0 }, matrix_res = { NULL, 0, 0 }, matrix_res_exp = { NULL, 0, 0 };
    if ((read_matrix("func_tests/data/pos_07_in2.txt", &matrix1)));
    else if ((read_matrix("func_tests/data/pos_07_out.txt", &matrix_res_exp)));
    else if (matrix1.n + 1 != matrix1.m);
    else if (!(matrix_res.matrix = allocate_matrix(matrix1.m, 1)));
    else
    {
        matrix_solve(matrix1, &matrix_res);

        for (size_t i = 0; i < matrix_res_exp.n; i++)
            for (size_t j = 0; j < matrix_res_exp.m; j++)
                ck_assert_double_lt(fabs(matrix_res.matrix[i][j] - matrix_res_exp.matrix[i][j]), MACHINE_EPS);
    }
    free(matrix1.matrix), free(matrix_res.matrix), free(matrix_res_exp.matrix);
}
END_TEST

Suite* matrix_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("matrix");
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sum_2_matrix);
    tcase_add_test(tc_pos, test_sum_with_negative_matrix);
    tcase_add_test(tc_pos, test_mult_matrix);
    tcase_add_test(tc_pos, test_mult_unit_matrix);
    tcase_add_test(tc_pos, test_mult_zero_matrix);
    tcase_add_test(tc_pos, test_solve_1x2_matrix);
    tcase_add_test(tc_pos, test_solve_2x3_matrix);
    tcase_add_test(tc_pos, test_solve_3x4_matrix);
    suite_add_tcase(s, tc_pos);

    return s;
}

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = matrix_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}