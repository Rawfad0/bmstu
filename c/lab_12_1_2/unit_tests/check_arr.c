#include "arr.h"
#include <check.h>
#include <stdlib.h>

START_TEST(test_left_cycle_shift)
{
    #define N 5
    int src[N] = { 1, 2, 3, 4, 5 };
    int res[N] = { 2, 3, 4, 5, 1 };

    k_left_cycle_shift(src, N, 1);
    
    for (int i = 0; i < N; i++)
        ck_assert_int_eq(src[i], res[i]);
    #undef N
}
END_TEST

START_TEST(test_count_new_arr_len)
{
    #define N 7
    int src[N] = { -1, 0, 1, 2, 3, 4, 5 };

    int n = count_new_arr_len(src, N);
    ck_assert_int_eq(n, 3);
    #undef N
}
END_TEST

START_TEST(test_filter_squares)
{
    #define N 7
    int src[N] = { -1, 0, 1, 2, 3, 4, 5 };
    int res[N] = { 0, 1, 4};
    
    int n = count_new_arr_len(src, N);
    ck_assert_int_eq(n, 3);

    int *dst = malloc(n * sizeof(int));
    filter_squares(src, N, dst);
    for (int i = 0; i < n; i++)
        ck_assert_int_eq(dst[i], res[i]);
    free(dst);
    #undef N
}
END_TEST

Suite* suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("suite");
    
    tc_pos = tcase_create("case");
    tcase_add_test(tc_pos, test_left_cycle_shift);
    tcase_add_test(tc_pos, test_count_new_arr_len);
    tcase_add_test(tc_pos, test_filter_squares);
    suite_add_tcase(s, tc_pos);

    return s;
}

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
