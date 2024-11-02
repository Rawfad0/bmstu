#include "my_snprintf.h"
#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <limits.h>

START_TEST(my_snprintf_ok)
{
    char *str1 = malloc(5*sizeof(char)), *str2 = malloc(5*sizeof(char));
    
    int rc1 = my_snprintf(str1, 5, "%s %s", "ab", "b");
    int rc2 = snprintf(str2, 5, "%s %s", "ab", "b");

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(str1, str2);

    free(str1);
    free(str2);
}
END_TEST

START_TEST(my_snprintf_empty_str)
{
    char *str1 = malloc(5*sizeof(char)), *str2 = malloc(5*sizeof(char));
    
    int rc1 = my_snprintf(str1, 5, "%s", "");
    int rc2 = snprintf(str2, 5, "%s", "");

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(str1, str2);

    free(str1);
    free(str2);
}
END_TEST

START_TEST(my_snprintf_str_and_char)
{
    char *str1 = malloc(5*sizeof(char)), *str2 = malloc(5*sizeof(char));
    
    int rc1 = my_snprintf(str1, 5, "%s %c", "ab", 'a');
    int rc2 = snprintf(str2, 5, "%s %c", "ab", 'a');

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(str1, str2);

    free(str1);
    free(str2);
}
END_TEST

START_TEST(my_snprintf_n_zero)
{
    char *str1 = malloc(5*sizeof(char)), *str2 = malloc(5*sizeof(char));
    
    int rc1 = my_snprintf(str1, 0, "%s %c", "ab", 'a');
    int rc2 = snprintf(str2, 0, "%s %c", "ab", 'a');

    ck_assert_int_eq(rc1, rc2);

    free(str1);
    free(str2);
}
END_TEST

START_TEST(my_snprintf_n_zero_str_NULL)
{
    char *str1 = NULL, *str2 = NULL;
    
    int rc1 = my_snprintf(str1, 0, "%s %c", "ab", 'a');
    int rc2 = snprintf(str2, 0, "%s %c", "ab", 'a');

    ck_assert_int_eq(rc1, rc2);

    free(str1);
    free(str2);
}
END_TEST

START_TEST(my_snprintf_str_and_num)
{
    char *str1 = malloc(7*sizeof(char)), *str2 = malloc(7*sizeof(char));
    
    int rc1 = my_snprintf(str1, 7, "%s %d", "ab", 123);
    int rc2 = snprintf(str2, 7, "%s %d", "ab", 123);
    
    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(str1, str2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(my_snprintf_neg_zero_pos)
{
    char *str1 = malloc(11*sizeof(char)), *str2 = malloc(11*sizeof(char));
    
    int rc1 = my_snprintf(str1, 11, "%d %d %d", -123, 0, 123);
    int rc2 = snprintf(str2, 11, "%d %d %d", -123, 0, 123);

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(str1, str2);
    
    free(str1);
    free(str2);
}
END_TEST

START_TEST(my_snprintf_str_and_neg_num)
{
    char *str1 = malloc(8*sizeof(char)), *str2 = malloc(8*sizeof(char));
    
    int rc1 = my_snprintf(str1, 8, "%s %d", "ab", -123);
    int rc2 = snprintf(str2, 8, "%s %d", "ab", -123);

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(str1, str2);

    free(str1);
    free(str2);
}
END_TEST

START_TEST(my_snprintf_5_d)
{
    #define N 30
    char *str1 = malloc(N*sizeof(char)), *str2 = malloc(N*sizeof(char));
    
    int rc1 = my_snprintf(str1, N, "%d + %d - %d * %d = %d", 20, 100, 1, -3, 20 + 100 - 1 * -3);
    int rc2 = snprintf(str2, N, "%d + %d - %d * %d = %d", 20, 100, 1, -3, 20 + 100 - 1 * -3);
    #undef N

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(str1, str2);
    
    free(str1);
    free(str2);
}
END_TEST

START_TEST(my_snprintf_strs_and_nums)
{
    #define N 100
    char *str1 = malloc(N*sizeof(char)), *str2 = malloc(N*sizeof(char));

    int rc1 = my_snprintf(str1, N, "affseSVvWEfwd%sawd ad%d\nfsefe%d%d%d%sesfwa%s%s\n", 
        "sadwdawd", 5242142, 441, 341, -123412, "sefad", "asfq2daces", "fawsscwq1212");
    int rc2 = snprintf(str2, N, "affseSVvWEfwd%sawd ad%d\nfsefe%d%d%d%sesfwa%s%s\n", 
        "sadwdawd", 5242142, 441, 341, -123412, "sefad", "asfq2daces", "fawsscwq1212");
    #undef N

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(str1, str2);
    
    free(str1);
    free(str2);
}
END_TEST

START_TEST(my_snprintf_d_lim)
{
    #define N 100
    char *str1 = malloc(N*sizeof(char)), *str2 = malloc(N*sizeof(char));

    int rc1 = my_snprintf(str1, N, "%d %d", INT_MIN, INT_MAX);
    int rc2 = snprintf(str2, N, "%d %d", INT_MIN, INT_MAX);
    #undef N

    ck_assert_int_eq(rc1, rc2);
    ck_assert_str_eq(str1, str2);
    
    free(str1);
    free(str2);
}
END_TEST

Suite* suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("suite");
    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, my_snprintf_ok);
    tcase_add_test(tc_pos, my_snprintf_empty_str);
    tcase_add_test(tc_pos, my_snprintf_str_and_char);
    tcase_add_test(tc_pos, my_snprintf_n_zero);
    tcase_add_test(tc_pos, my_snprintf_n_zero_str_NULL);
    tcase_add_test(tc_pos, my_snprintf_str_and_num);
    tcase_add_test(tc_pos, my_snprintf_neg_zero_pos);
    tcase_add_test(tc_pos, my_snprintf_str_and_neg_num);
    tcase_add_test(tc_pos, my_snprintf_5_d);
    tcase_add_test(tc_pos, my_snprintf_strs_and_nums);
    tcase_add_test(tc_pos, my_snprintf_d_lim);

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