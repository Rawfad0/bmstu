#include "associative_array.h"
#include <check.h>
#include <stdlib.h>

#include <stdio.h>

assoc_array_error_t fill_array(assoc_array_t arr, size_t n, char **keys, int *nums)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    for (size_t i = 0; i < n && rc == ASSOC_ARRAY_OK; i++)
        rc = assoc_array_insert(arr, keys[i], nums[i]);
    return rc;
}

START_TEST(assoc_array_destroy_ok)
{
    assoc_array_t aa = assoc_array_create();
    assoc_array_destroy(&aa);
    ck_assert_ptr_eq(aa, NULL);
}
END_TEST

START_TEST(assoc_array_destroy_array_has_not_created)
{
    assoc_array_destroy(NULL);
    ck_assert_int_eq(0, 0);
}
END_TEST

START_TEST(assoc_array_insert_ok)
{
    char *keys[] = { "a", "ab", "123", "abssesawmcmw", "2rsd3" };
    int nums[] = { 1, 2, 3, 4, 5 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 5, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");
    assoc_array_error_t rc = assoc_array_insert(aa, "abcd", 5);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    
    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_insert_ok_min)
{
    char *keys[] = { "a", "ab", "123", "abssesawmcmw", "2rsd3" };
    int nums[] = { 1, 2, 3, 4, 5 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 5, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");
    assoc_array_error_t rc = assoc_array_insert(aa, "1", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    
    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_insert_ok_max)
{
    char *keys[] = { "a", "ab", "123", "abssesawmcmw", "2rsd3" };
    int nums[] = { 1, 2, 3, 4, 5 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 5, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");
    assoc_array_error_t rc = assoc_array_insert(aa, "zbcd", 0);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    
    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_insert_NULL)
{
    assoc_array_t aa = assoc_array_create();
    assoc_array_error_t rc = assoc_array_insert(aa, NULL, 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    
    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_insert_array_has_not_created)
{
    assoc_array_error_t rc = assoc_array_insert(NULL, "abcd", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(assoc_array_insert_empty_key)
{
    assoc_array_t aa = assoc_array_create();
    
    assoc_array_error_t rc = assoc_array_insert(aa, "", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    
    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_insert_key_exist)
{
    char *keys[] = { "abcd" };
    int nums[] = { 1 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 1, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");
    assoc_array_error_t rc = assoc_array_insert(aa, "abcd", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);
    
    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_find_ok)
{
    char *keys[] = { "abcd", "abc", "ab", "a" };
    int nums[] = { 1, 2, 3, 4 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 4, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");

    int *num = NULL;
    assoc_array_error_t rc = assoc_array_find(aa, "abc", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, 2);
    
    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_find_NULL)
{
    assoc_array_t aa = assoc_array_create();

    int *num = NULL;
    assoc_array_error_t rc = assoc_array_find(aa, NULL, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    
    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_find_array_has_not_created)
{
    int *num = NULL;
    assoc_array_error_t rc = assoc_array_find(NULL, "abcd", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(assoc_array_find_empty_key)
{
    assoc_array_t aa = assoc_array_create();

    int *num = NULL;
    assoc_array_error_t rc = assoc_array_find(aa, "", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    
    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_find_key_not_exist)
{
    char *keys[] = { "abcd" };
    int nums[] = { 1 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 1, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");

    int *num = NULL;
    assoc_array_error_t rc = assoc_array_find(aa, "abcde", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    
    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_find_ppnum_is_NULL)
{
    char *keys[] = { "abcd" };
    int nums[] = { 1 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 1, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");

    assoc_array_error_t rc = assoc_array_find(aa, "abcd", NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    
    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_remove_exist)
{
    char *keys[] = { "a", "ab", "123", "abssesawmcmw", "2rsd3" };
    int nums[] = { 1, 2, 3, 4, 5 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 5, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");
    assoc_array_error_t rc = assoc_array_remove(aa, "a");
    
    int *num = NULL;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(ASSOC_ARRAY_NOT_FOUND, assoc_array_find(aa, "a", &num));
    ck_assert_ptr_eq(num, NULL);

    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_remove_min)
{
    char *keys[] = { "a", "ab", "123", "abssesawmcmw", "2rsd3" };
    int nums[] = { 1, 2, 3, 4, 5 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 5, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");
    assoc_array_error_t rc = assoc_array_remove(aa, "123");
    
    int *num = NULL;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(ASSOC_ARRAY_NOT_FOUND, assoc_array_find(aa, "123", &num));
    ck_assert_ptr_eq(num, NULL);

    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_remove_mid)
{
    char *keys[] = { "cda", "bcd", "pssesawmcmw", "a", "rsd3" };
    int nums[] = { 1, 2, 3, 4, 5 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 5, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");
    assoc_array_error_t rc = assoc_array_remove(aa, "cda");
    
    int *num = NULL;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(ASSOC_ARRAY_NOT_FOUND, assoc_array_find(aa, "cda", &num));
    ck_assert_ptr_eq(num, NULL);

    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_remove_max)
{
    char *keys[] = { "a", "ab", "123", "abssesawmcmw", "2rsd3" };
    int nums[] = { 1, 2, 3, 4, 5 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 5, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");
    assoc_array_error_t rc = assoc_array_remove(aa, "abssesawmcmw");
    
    int *num = NULL;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(ASSOC_ARRAY_NOT_FOUND, assoc_array_find(aa, "abssesawmcmw", &num));
    ck_assert_ptr_eq(num, NULL);

    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_remove_last)
{
    char *keys[] = { "abc123" };
    int nums[] = { 1 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 1, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");
    assoc_array_error_t rc = assoc_array_remove(aa, "abc123");
    
    int *num = NULL;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(ASSOC_ARRAY_NOT_FOUND, assoc_array_find(aa, "abc123", &num));
    ck_assert_ptr_eq(num, NULL);

    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_remove_all)
{
    char *keys[] = { "a", "ab", "123", "abssesawmcmw", "2rsd3" };
    int nums[] = { 1, 2, 3, 4, 5 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 5, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");
    int *num = NULL;
    assoc_array_error_t rc = ASSOC_ARRAY_OK;

    rc = assoc_array_remove(aa, "a");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(ASSOC_ARRAY_NOT_FOUND, assoc_array_find(aa, "a", &num));
    ck_assert_ptr_eq(num, NULL);

    rc = assoc_array_remove(aa, "ab");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(ASSOC_ARRAY_NOT_FOUND, assoc_array_find(aa, "ab", &num));
    ck_assert_ptr_eq(num, NULL);

    rc = assoc_array_remove(aa, "123");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(ASSOC_ARRAY_NOT_FOUND, assoc_array_find(aa, "123", &num));
    ck_assert_ptr_eq(num, NULL);

    rc = assoc_array_remove(aa, "abssesawmcmw");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(ASSOC_ARRAY_NOT_FOUND, assoc_array_find(aa, "abssesawmcmw", &num));
    ck_assert_ptr_eq(num, NULL);

    rc = assoc_array_remove(aa, "2rsd3");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(ASSOC_ARRAY_NOT_FOUND, assoc_array_find(aa, "2rsd3", &num));
    ck_assert_ptr_eq(num, NULL);

    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_remove_exist_two_times)
{
    char *keys[] = { "a", "ab", "123", "abssesawmcmw", "2rsd3" };
    int nums[] = { 1, 2, 3, 4, 5 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 5, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");
    assoc_array_error_t rc1 = assoc_array_remove(aa, "a");
    assoc_array_error_t rc2 = assoc_array_remove(aa, "a");

    int *num = NULL;
    ck_assert_int_eq(rc1, ASSOC_ARRAY_OK);
    ck_assert_int_eq(rc2, ASSOC_ARRAY_NOT_FOUND);
    ck_assert_int_eq(ASSOC_ARRAY_NOT_FOUND, assoc_array_find(aa, "a", &num));
    ck_assert_ptr_eq(num, NULL);
    
    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_remove_not_exist)
{
    char *keys[] = { "a", "ab", "123", "abssesawmcmw", "2rsd3" };
    int nums[] = { 1, 2, 3, 4, 5 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 5, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");
    assoc_array_error_t rc = assoc_array_remove(aa, "aa");
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_remove_NULL)
{
    assoc_array_t aa = assoc_array_create();

    assoc_array_error_t rc = assoc_array_remove(aa, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    
    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_remove_array_has_not_created)
{
    assoc_array_error_t rc = assoc_array_remove(NULL, "abcd");
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(assoc_array_remove_empty_key)
{
    assoc_array_t aa = assoc_array_create();

    assoc_array_error_t rc = assoc_array_remove(aa, "");
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    
    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_remove_empty_arr)
{
    assoc_array_t aa = assoc_array_create();

    assoc_array_error_t rc = assoc_array_remove(aa, "aa");
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    
    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_each_func_NULL)
{
    char *keys[] = { "abcd" };
    int nums[] = { 1 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 1, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");

    assoc_array_error_t rc = assoc_array_each(aa, NULL, "abc");
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&aa);
}
END_TEST

void count_keys(const char *key, int *value, void *param)
{
    size_t *c = param;
    if (key != NULL && value != NULL)
        ++*c;
}

START_TEST(assoc_array_each_empty_arr)
{
    assoc_array_t aa = assoc_array_create();

    size_t c = 0;
    assoc_array_error_t rc = assoc_array_each(aa, (*count_keys), &c);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(c, 0);

    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_each_count)
{
    char *keys[] = { "abcd", "abb", "b", "gsfes" };
    int nums[] = { 1, 2, 3, 4 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 4, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");

    size_t c = 0;
    assoc_array_error_t rc = assoc_array_each(aa, (*count_keys), &c);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(c, 4);

    assoc_array_destroy(&aa);
}
END_TEST

START_TEST(assoc_array_min_ok)
{
    char *keys[] = { "abcd", "abb", "b", "gsfes" };
    int nums[] = { 1, 2, 3, 4 };

    assoc_array_t aa = assoc_array_create();
    if (fill_array(aa, 4, keys, nums) != ASSOC_ARRAY_OK)
        printf("Error in func: fill_array\n");

    int *p = NULL;
    assoc_array_error_t rc = assoc_array_min(aa, &p);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*p, 2);

    assoc_array_destroy(&aa);
}
END_TEST

Suite* associative_array_suite(void)
{
    Suite *s;
    TCase *tcase;

    s = suite_create("associative_array");
    
    tcase = tcase_create("case");
    // assoc_array_destroy
    tcase_add_test(tcase, assoc_array_destroy_ok);
    tcase_add_test(tcase, assoc_array_destroy_array_has_not_created);
    // assoc_array_insert
    tcase_add_test(tcase, assoc_array_insert_ok);
    tcase_add_test(tcase, assoc_array_insert_ok_min);
    tcase_add_test(tcase, assoc_array_insert_ok_max);
    tcase_add_test(tcase, assoc_array_insert_NULL);
    tcase_add_test(tcase, assoc_array_insert_array_has_not_created);
    tcase_add_test(tcase, assoc_array_insert_empty_key);
    tcase_add_test(tcase, assoc_array_insert_key_exist);
    // assoc_array_find
    tcase_add_test(tcase, assoc_array_find_ok);
    tcase_add_test(tcase, assoc_array_find_NULL);
    tcase_add_test(tcase, assoc_array_find_array_has_not_created);
    tcase_add_test(tcase, assoc_array_find_empty_key);
    tcase_add_test(tcase, assoc_array_find_key_not_exist);
    tcase_add_test(tcase, assoc_array_find_ppnum_is_NULL);
    // assoc_array_remove
    tcase_add_test(tcase, assoc_array_remove_exist);
    tcase_add_test(tcase, assoc_array_remove_exist_two_times);
    tcase_add_test(tcase, assoc_array_remove_min);
    tcase_add_test(tcase, assoc_array_remove_mid);
    tcase_add_test(tcase, assoc_array_remove_max);
    tcase_add_test(tcase, assoc_array_remove_last);
    tcase_add_test(tcase, assoc_array_remove_all);
    tcase_add_test(tcase, assoc_array_remove_not_exist);
    tcase_add_test(tcase, assoc_array_remove_NULL);
    tcase_add_test(tcase, assoc_array_remove_array_has_not_created);
    tcase_add_test(tcase, assoc_array_remove_empty_key);
    tcase_add_test(tcase, assoc_array_remove_empty_arr);
    // assoc_array_each
    tcase_add_test(tcase, assoc_array_each_func_NULL);
    tcase_add_test(tcase, assoc_array_each_empty_arr);
    tcase_add_test(tcase, assoc_array_each_count);
    // assoc_array_min
    tcase_add_test(tcase, assoc_array_min_ok);

    suite_add_tcase(s, tcase);

    return s;
}

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = associative_array_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
