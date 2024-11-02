#include "film.h"
#include "consts.h"
#include <check.h>
#include <stdlib.h>

START_TEST(read_and_sort_by_title)
{
    film_arr_t film_arr = { NULL, 0 };
    film_t films[5] = { 
        { "a", "b", 1 }, 
        { "abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabc", "cfnxrxv", 3113 },
        { "awfgw", "segsFE", 13 },
        { "dawaawdaw", "awfadawda", 1241 },
        { "sefsGDvzcs", "sesefsv", 314421 } };
    
    if (read_film_array("./func_tests/data/pos_01_in.txt", &film_arr, compare_by_title));
    else
        for (size_t i = 0; i < film_arr.n; i++)
        {
            ck_assert_str_eq(film_arr.arr[i].title, films[i].title);
            ck_assert_str_eq(film_arr.arr[i].name, films[i].name);
            ck_assert_int_eq(film_arr.arr[i].year, films[i].year);
        }
    free_film_arr(&film_arr);
}
END_TEST

Suite* matrix_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("matrix");
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, read_and_sort_by_title);
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
