/**
 * @file main.c
 * @brief Умножение длинных действительного и целого чисел и вывод в нормализованном виде
 * 
 * Смоделировать операцию умножения действительного числа в форме [+-]m.n Е [+-]K, 
 * где суммарная длина мантиссы (m+n) - до 40 значащих цифр, 
 * а величина порядка K - до 5 цифр, на целое число длиной до 30 десятичных цифр. 
 * Результат выдать в форме [+-]0.m1 Е [+-]K1, где m1 - до 30 значащих цифр, а K1 - до 5 цифр.
 */

#include "f.h"
#include "io.h"
#include "consts.h"
#include "structs.h"
#include <stdio.h>

/**
 * @brief Управление умножением
 * 
 * @return int код выхода
 */
int multiplication_controller(void)
{
    char real_num_str[REAL_NUM_LEN];        // Вводимое действительное число
    char int_num_str[INT_NUM_LEN];          // Вводимое целое число
    char result_num_str[REAL_NUM_LEN];      // Выводимое действительное число
    real_num real_num = {1, { 0 }, 0};      // Структура действительного числа
    int_num integer_num = {1, { 0 }};       // Структура целого числа
    calc_num res_num = {1, { 0 }, 0};       // Структура выводимого числа
    int rc = 0;

    if ((rc = input_real_num(real_num_str)))
        return rc;
    else if ((rc = str_to_real_num(real_num_str, &real_num)))
        return rc;
    else if ((rc = input_int_num(int_num_str)))
        return rc;
    else if ((rc = str_to_int_num(int_num_str, &integer_num)))
        return rc;
    else if ((rc = calculate(real_num, integer_num, &res_num)))
        return rc;
    else if ((rc = res_to_str(res_num, result_num_str)))
        return rc;
    else
        print_result(result_num_str);
    return rc;
}

int main(void)
{
    int option;                     // Выбранное действие меню
    
    do
    {
        option = 0;
        menu_get_selected_option(&option);
        switch (option)
        {
            case 1:
                info();
                break;
            case 2:
                multiplication_controller();
                break;
            case 3:
                break;
            default:
                printf("Действие с введенным пунктом отсутствует.\n\n");
                break;
        }
    } while (option != 3);

    return OK;
}