#include "polynomial.h"
#include "list.h"
#include <check.h>
#include <stdlib.h>

START_TEST(ddx)
{
    node_t *list1 = NULL, *list2 = NULL;
    term_t *term = NULL;
    term = malloc(sizeof(term_t));
    term->coefficient = 1;
    term->power = 1;
    push_front(&list1, make_node(term));

    term = malloc(sizeof(term_t));
    term->coefficient = 0;
    term->power = 0;
    push_front(&list1, make_node(term));

    list1 = reverse(list1);

    term = malloc(sizeof(term_t));
    term->coefficient = 0;
    term->power = 0;
    push_front(&list2, make_node(term));

    term = malloc(sizeof(term_t));
    term->coefficient = 1;
    term->power = 1;
    push_front(&list2, make_node(term));


    for (node_t *node1 = list1, *node2 = list2; node1 != NULL && node2 != NULL; node1 = next_node(node1), node2 = next_node(node2))
        ck_assert_int_eq(compare_by_power(get_data(node1), get_data(node2)), 0);   

    free_polynomial_list(&list1);
    free_polynomial_list(&list2);
}
END_TEST

Suite* polynomial_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("film");
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, ddx);
    suite_add_tcase(s, tc_pos);

    return s;
}

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = polynomial_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
