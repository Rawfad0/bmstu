/**
 * @file main.c
 * 
 * Вариант 2. В виде списка представлены коэффициенты в убывающем порядке 
 * разложенного по схеме Горнера полинома с целыми коэффициентами.
 * 
 * Пример:
 * ∀𝑥 ∈ R 𝑃 (𝑥) = 4𝑥^3 + 2𝑥^2 + 6 = 4𝑥^3 + 2𝑥^2 + 0𝑥 + 6 = ((4𝑥 + 2)·𝑥 + 0)·𝑥 + 6,
 * List ↦ List ↦ 4 ↦ 2 ↦ 0 ↦ 6 ↦ ∅.
 *
 * Требуется:
 * (a) Реализовать подпрограмму вычисления 𝑃(𝑎) по введённому с клавиатуры 𝑎.
 * (b) Реализовать подпрограмму вычисления производной 𝑑/𝑑𝑥 𝑃(𝑥).
 * (c) Реализовать подпрограмму сложения двух полиномов.
 * (d) Реализовать подпрограмму разделения полинома на полиномы чётных и нечётных степеней.
 * 
 * Правила взаимодействия:
 * (a) При старте программы пользователь вводит одно из четырёх слов: val, ddx, sum, dvd. 
 * При вводе val за ним с новой строки следуют через пробел в одну строку множители и 
 * степени полинома от старшей к младшей, а со следующей строки — аргумент a.
 * (b) Выводить полином, сохранённый в виде списка, на экран в виде множителей и 
 * степеней через пробел от старшей к младшей. После окончания вывода печатать букву L.
 * 
 */

#include "consts.h"
#include "polynomial.h"
#include "list.h"

#include <string.h>
#include <stdio.h>

#define _POSIX_C_SOURCE 200809L

int controller(char *str);

int get_input(char **str, FILE *f);

int main(void)
{
    int rc = RC_OK;
    char *str = NULL;

    if ((rc = get_input(&str, stdin)) == RC_OK)
        rc = controller(str);

    return rc;
}

int get_input(char **str, FILE *f)
{
    int rc = RC_OK;
    size_t len = 0;
    int read;

    if ((read = getline(str, &len, f)) == -1 || read <= 1)
        rc = RC_INCORRECT_INPUT;
    else if ((*str)[strlen(*str) - 1] == '\n')
        (*str)[strlen(*str) - 1] = '\0';

    return rc;
}

int controller(char *str)
{
    int rc = RC_OK;

    if (strcmp(COMMAND_CALCULATE, str) == 0)
    {
        node_t *list = NULL;
        int value = 0;
        if ((rc = read_polynomial_list(&list)) != RC_OK);
        else if ((rc = read_variable_value(&value)) != RC_OK);
        else
            print_result(calculate(list, value));
        free_polynomial_list(&list);
    }
    else if (strcmp(COMMAND_DERIVATIVE, str) == 0)
    {
        node_t *list = NULL;
        if ((rc = read_polynomial_list(&list)) != RC_OK);
        else
            derivative(&list), print_polynomial_list(list);
        free_polynomial_list(&list);
    }
    else if (strcmp(COMMAND_ADD, str) == 0) 
    {
        node_t *list1 = NULL, *list2 = NULL, *list_res = NULL;
        if ((rc = read_polynomial_list(&list1)) != RC_OK);
        else if ((rc = read_polynomial_list(&list2)) != RC_OK);
        else
            print_polynomial_list(list_res = add(&list1, &list2));
        free_polynomial_list(&list1);
        free_polynomial_list(&list2);
        free_polynomial_list(&list_res);
    }
    else if (strcmp(COMMAND_DIVIDE, str) == 0)
    {
        node_t *list = NULL, *list1 = NULL, *list2 = NULL;
        if ((rc = read_polynomial_list(&list)) != RC_OK);
        else
        {
            divide(&list, &list1, &list2);
            print_polynomial_list(list1);
            print_polynomial_list(list2);
        }
        free_polynomial_list(&list);
        free_polynomial_list(&list1);
        free_polynomial_list(&list2);
    }    
    else
        rc = RC_INCORRECT_COMMAND;
    free(str);
    return rc;
}
