#include "list.h"
#include <check.h>
#include <stdlib.h>

void list_freer(node_t **node)
{
    while (*node != NULL)
        pop_front(node);
}


START_TEST(front_back_split_len_even)
{
    node_t *l1 = NULL, *l2 = NULL;
    for (size_t i = 0; i < 10; i++)
        insert(&l1, make_node(NULL), NULL);
    
    front_back_split(l1, &l2);

    size_t i1 = 0, i2 = 0;
    for (node_t *node = l1; node != NULL; i1++, node = next_node(node));
    for (node_t *node = l2; node != NULL; i2++, node = next_node(node));

    ck_assert_int_eq(i1, 5);
    ck_assert_int_eq(i2, 5);

    list_freer(&l1);
    list_freer(&l2);
}
END_TEST

START_TEST(front_back_split_len_odd)
{
    node_t *l1 = NULL, *l2 = NULL;
    for (size_t i = 0; i < 9; i++)
        insert(&l1, make_node(NULL), NULL);
    
    front_back_split(l1, &l2);

    size_t i1 = 0, i2 = 0;
    for (node_t *node = l1; node != NULL; i1++, node = next_node(node));
    for (node_t *node = l2; node != NULL; i2++, node = next_node(node));

    ck_assert_int_eq(i1, 5);
    ck_assert_int_eq(i2, 4);

    list_freer(&l1);
    list_freer(&l2);
}
END_TEST

START_TEST(front_back_split_len_1)
{
    node_t *l1 = NULL, *l2 = NULL;
    for (size_t i = 0; i < 1; i++)
        insert(&l1, make_node(NULL), NULL);
    
    front_back_split(l1, &l2);

    size_t i1 = 0, i2 = 0;
    for (node_t *node = l1; node != NULL; i1++, node = next_node(node));
    for (node_t *node = l2; node != NULL; i2++, node = next_node(node));

    ck_assert_int_eq(i1, 1);
    ck_assert_int_eq(i2, 0);

    list_freer(&l1);
    list_freer(&l2);
}
END_TEST

START_TEST(front_back_split_len_0)
{
    node_t *l1 = NULL, *l2 = NULL;
    
    front_back_split(l1, &l2);

    size_t i1 = 0, i2 = 0;
    for (node_t *node = l1; node != NULL; i1++, node = next_node(node));
    for (node_t *node = l2; node != NULL; i2++, node = next_node(node));

    ck_assert_int_eq(i1, 0);
    ck_assert_int_eq(i2, 0);

    list_freer(&l1);
    list_freer(&l2);
}
END_TEST

START_TEST(front_back_split_NULL)
{
    node_t *l1 = NULL;
    for (size_t i = 0; i < 9; i++)
        insert(&l1, make_node(NULL), NULL);
    
    front_back_split(l1, NULL);

    size_t i1 = 0;
    for (node_t *node = l1; node != NULL; i1++, node = next_node(node));

    ck_assert_int_eq(i1, 9);

    list_freer(&l1);
}
END_TEST

Suite* suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("suite");
    
    tc_pos = tcase_create("case");

    tcase_add_test(tc_pos, front_back_split_len_even);
    tcase_add_test(tc_pos, front_back_split_len_odd);
    tcase_add_test(tc_pos, front_back_split_len_1);
    tcase_add_test(tc_pos, front_back_split_len_0);
    tcase_add_test(tc_pos, front_back_split_NULL);

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
