#include "mysort.h"
#include <check.h>
#include <stdlib.h>

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
