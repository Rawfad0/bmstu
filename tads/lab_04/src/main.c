#include "ui.h"
#include "palindrome.h"
#include "static_array_stack.h"
// #include "da_stack.h"
#include "linked_list_stack.h"
#include "freed_mem_arr.h"
#include "compare.h"
#include "consts.h"

#include <stdio.h>
#include <time.h>

/**
 * @brief Контроллер
 * 
 * @param option выбранный пользователем пункт меню
 * @param filename имя файла
 * @param table таблица
 * @param key_table таблица ключей
 * @return int код возврата
 */
int controller(int option, sa_stack_t *sa_stack, ll_stack_t *ll_stack, fma_t *fma);
// int controller(int option, sa_stack_t *sa_stack, da_stack_t *da_stack, ll_stack_t *ll_stack, fma_t *fma);

int main(void)
{
    int rc = RC_OK;

    sa_stack_t sa_stack = { { '\0' }, NULL, NULL };
    sa_stack.pe = sa_stack.array + MAX_ARR_LEN;
    sa_stack.sp = sa_stack.array;
    // da_stack_t da_stack = { NULL, 0, NULL};
    ll_stack_t ll_stack = { NULL };
    fma_t fma = { NULL, 0 };

    size_t option = 0;
    while (option != OPT_EXIT)
    {
        print_menu();
        if ((rc = get_option(&option)))
            print_error(rc);    // Выбор пользователем пункта меню с последующей обработкой ошибок
        else if ((rc = controller(option, &sa_stack, &ll_stack, &fma)))
            print_error(rc);
    }

    // da_free(&da_stack);
    ll_free(&ll_stack);
    fma_free(&fma);

    return rc;
}

int controller(int option, sa_stack_t *sa_stack, ll_stack_t *ll_stack, fma_t *fma)
{
    int rc = RC_OK;

    switch (option)
    {
        case OPT_PRINT_INFO:
        {
            print_info();
            break;
        }
        case OPT_ADD_SAS:
        {
            clock_t start, finish, time = 0L;
            size_t i = 0;

            char *str = NULL;
            printf("Введите элементы подряд: ");
            get_input(&str, stdin);


            start = clock();
            for ( ; rc == RC_OK && str[i] != '\n'; i++)
            {
                if (sa_push(sa_stack, str[i]) != RC_OK)
                    break;
            }
            finish = clock();
            time += finish - start;

            free(str);  // Память была выделена в функции get_input функцией getline
            if (rc == RC_OK || rc == RC_STACK_EMPTY || rc == RC_STACK_FULL)
                printf("В стек было добавлено %zu элементов за время %ld тактов\n", i, time);
            break;
        }
        case OPT_DEL_SAS:
        {
            clock_t start, finish, time = 0L;
            size_t i = 0;
            char ch = '\0';

            char *str = NULL;
            printf("Введите число удаляемых элементов: ");
            get_input(&str, stdin);
            char *end;
            size_t num = strtol(str, &end, 10);
            if (end != str + strlen(str) - 1 || strlen(str) == 1)
                rc = RC_INCORRECT_INPUT;
            free(str);

            start = clock();
            for ( ; rc == RC_OK && i < num; i++)
            {
                if (sa_pop(sa_stack, &ch) != RC_OK)
                    break;
            }
            finish = clock();
            time += finish - start;
            if (rc == RC_OK || rc == RC_STACK_EMPTY || rc == RC_STACK_FULL)
                printf("Из стека было удалено %zu элементов за время %ld тактов\n", i, time);
            break;
        }
        case OPT_PRNT_SAS:
        {
            sa_print(sa_stack);
            break;
        }
        case OPT_ADD_LLS:
        {
            clock_t start, finish, time = 0L;
            size_t i = 0;

            char *str = NULL;
            printf("Введите элементы подряд: ");
            get_input(&str, stdin);
            start = clock();
            for ( ; rc == RC_OK && str[i] != '\n'; i++)
            {
                rc = ll_push(ll_stack, str + i);
            }
            finish = clock();
            time += finish - start;
            free(str);  // Память была выделена в функции get_input функцией getline
            if (rc == RC_OK || rc == RC_STACK_EMPTY || rc == RC_STACK_FULL)
                printf("В стек было добавлено %zu элементов за время %ld тактов\n", i, time);
            break;
        }
        case OPT_DEL_LLS:
        {
            clock_t start, finish, time = 0L;
            size_t i = 0;

            char *str = NULL;
            printf("Введите число удаляемых элементов: ");
            get_input(&str, stdin);
            char *end;
            size_t num = strtol(str, &end, 10);
            if (end != str + strlen(str) - 1 || strlen(str) == 1)
                rc = RC_INCORRECT_INPUT;
            free(str);

            list_t *tmp = NULL;
            start = clock();
            for ( ; rc == RC_OK && i < num; i++)
            {
                rc = ll_pop(ll_stack, &tmp);
                if (rc == RC_OK)
                {
                    fma_add(fma, tmp);
                    // printf("Из стека на списке был удален элемент '%lc'\n", tmp->value);
                    free(tmp);
                }
                else
                    break;
            }
            finish = clock();
            time += finish - start;
            if (rc == RC_OK || rc == RC_STACK_EMPTY || rc == RC_STACK_FULL)
                printf("Из стека было удалено %zu элементов за время %ld тактов\n", i, time);
            break;
        }
        case OPT_PRNT_LLS:
        {
            ll_print(ll_stack);
            break;
        }
        case OPT_PRINT_FREED_AREAS:
        {
            fma_print(fma);
            break;
        }
        case OPT_DETERM_PALINDROM:
        {
            sa_stack_t a_word = { { '\0' }, NULL, NULL };
            a_word.pe = a_word.array + MAX_ARR_LEN;
            a_word.sp = a_word.array;
            ll_stack_t l_word = { NULL };
            // Чтение строки
            char *str = NULL;
            printf("Введите строку: ");
            get_input(&str, stdin);
            if (strlen(str) <= 1)
                rc = RC_EMPTY_STR;
            // Добавление строки в стеки
            size_t i = 0;
            for ( ; rc == RC_OK && str[i] != '\n'; i++)
            {
                if (rc = ll_push(&l_word, str + i), rc != RC_OK)
                    break;
                else if (rc = sa_push(&a_word, str[i]), rc != RC_OK)
                    break;
                else
                    printf("В стек добавлен элемент '%lc'\n", str[i]);
            }
            if (rc == RC_OK)
            {
                bool a_flag, l_flag;
                clock_t start, finish, time;
                // Проверка стеком на массиве
                printf("Проверка через стек на массиве:\n");
                start = clock();
                a_flag = sa_is_palindrome(&a_word, i);
                finish = clock();
                time = finish - start;
                printf("За время %ld тактов было определено, что введенная строка %s %s палиндромом.\n", 
                    time, str, a_flag ? "ЯВЛЯЕТСЯ" : "НЕ ЯВЛЯЕТСЯ");
                // Проверка стеком на списке
                printf("Проверка через стек на списке:\n");
                start = clock();
                l_flag = ll_is_palindrome(&l_word, i);
                finish = clock();
                time = finish - start;
                printf("За время %ld тактов было определено, что введенная строка %s %s палиндромом.\n", 
                    time, str, l_flag ? "ЯВЛЯЕТСЯ" : "НЕ ЯВЛЯЕТСЯ");
            }
            free(str);
            break;
        }
        case OPT_COMPARE:
        {
            rc = compare();
            break;
        }
        case OPT_EXIT:
        {
            printf("Завершение программы.\n");
            break;
        }
        // case OPT_ADD_DAS:
        // {
        //     clock_t start, finish, time = 0L;
        //     size_t i = 0;

        //     char *str = NULL;
        //     printf("Введите элементы подряд: ");
        //     get_input(&str, stdin);

        //     start = clock();
        //     for ( ; rc == RC_OK && str[i] != '\n'; i++)
        //     {
        //         rc = da_push(da_stack, str[i]);
        //     }
        //     finish = clock();
        //     time += finish - start;

        //     free(str);  // Память была выделена в функции get_input функцией getline
        //     if (rc == RC_OK || rc == RC_STACK_EMPTY || rc == RC_STACK_FULL)
        //         printf("В стек было добавлено %zu элементов за время %ld тактов\n", i, time);
        //     break;
        // }
        // case OPT_DEL_DAS:
        // {
        //     clock_t start, finish, time = 0L;
        //     size_t i = 0;
        //     char ch = '\0';

        //     char *str = NULL;
        //     printf("Введите число удаляемых элементов: ");
        //     get_input(&str, stdin);
        //     char *end = NULL;
        //     size_t num = strtol(str, &end, 10);
        //     if (end != str + strlen(str) - 1 || strlen(str) == 1)
        //         rc = RC_INCORRECT_INPUT;
        //     free(str);

        //     start = clock();
        //     for ( ; rc == RC_OK && i < num; i++)
        //     {
        //         rc = da_pop(da_stack, &ch);
        //         if (rc != RC_OK)
        //             break;
        //     }
        //     finish = clock();
        //     time += finish - start;
        //     if (rc == RC_OK || rc == RC_STACK_EMPTY || rc == RC_STACK_FULL)
        //         printf("Из стека было удалено %zu элементов за время %ld тактов\n", i, time);
        //     break;
        // }
        // case OPT_PRNT_DAS:
        // {
        //     da_print(da_stack);
        //     break;
        // }
        default:
            printf("Некорректный номер пункта меню. Действия не существует.\n");
            return RC_INCORRECT_OPTION;
            break;
    }
    return rc;
}
