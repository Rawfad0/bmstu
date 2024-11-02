#include "mysort.h"
#include <check.h>
#include <stdlib.h>

// int module_test_mysort(void)
// {
//     int counter = 0;
//     size_t n;

//     n = 4;
//     int arr_1_1[4] = {0, 1, 2, 3};
//     int arr_1_2[4] = {0, 1, 2, 3};
//     counter += check_sort(arr_1_1, arr_1_2, n);

//     n = 4;
//     int arr_2_1[4] = {3, 2, 1, 0};
//     int arr_2_2[4] = {3, 2, 1, 0};
//     counter += check_sort(arr_2_1, arr_2_2, n);

//     n = 4;
//     int arr_3_1[4] = {1, 6, 3, 5};
//     int arr_3_2[4] = {1, 6, 3, 5};
//     counter += check_sort(arr_3_1, arr_3_2, n);

//     n = 7;
//     int arr_4_1[7] = {0, 1, 1, 1, 0, -1, -1};
//     int arr_4_2[7] = {0, 1, 1, 1, 0, -1, -1};
//     counter += check_sort(arr_4_1, arr_4_2, n);

//     return counter;
// }

// int check_sort(int *arr_1, int *arr_2, size_t n)
// {
//     size_t i;
//     mysort(arr_1, sizeof(int), n, compare_int);
//     qsort(arr_2, sizeof(int), n, compare_int);
//     for (i = 0; i < n && arr_1[i] == arr_2[i]; i++)
//         ;
//     if (i != n)
//         return 1;

//     return 0;
// }

START_TEST(test_compare_int_two_zeros)
{
    int a = 0, b = 0;
    int res;

    res = compare_int((const void *) &a, (const void *) &b);
    ck_assert_double_eq(res, 0);
}
END_TEST

START_TEST(test_compare_int_equal_positive)
{
    int a = 11, b = 11;
    int res;

    res = compare_int((const void *) &a, (const void *) &b);
    ck_assert_double_eq(res, 0);
}
END_TEST

START_TEST(test_compare_int_equal_negative)
{
    int a = -397, b = -397;
    int res;

    res = compare_int((const void *) &a, (const void *) &b);
    ck_assert_double_eq(res, 0);
}
END_TEST

START_TEST(test_compare_int_first_larger)
{
    int a = 21, b = 11;
    int res;

    res = compare_int((const void *) &a, (const void *) &b);
    ck_assert_double_eq(res, 10);
}
END_TEST

START_TEST(test_compare_int_second_larger)
{
    int a = 11, b = 21;
    int res;

    res = compare_int((const void *) &a, (const void *) &b);
    ck_assert_double_eq(res, -10);
}
END_TEST

START_TEST(test_compare_int_diff_sign)
{
    int a = 1, b = -1;
    int res;

    res = compare_int((const void *) &a, (const void *) &b);
    ck_assert_double_eq(res, 2);
}
END_TEST

Suite* compare_int_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("compare_int");
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_compare_int_two_zeros);
    tcase_add_test(tc_pos, test_compare_int_equal_positive);
    tcase_add_test(tc_pos, test_compare_int_equal_negative);
    tcase_add_test(tc_pos, test_compare_int_first_larger);
    tcase_add_test(tc_pos, test_compare_int_second_larger);
    tcase_add_test(tc_pos, test_compare_int_diff_sign);
    suite_add_tcase(s, tc_pos);

    return s;
}

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = compare_int_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
