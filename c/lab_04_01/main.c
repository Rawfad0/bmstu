/*!
 * \file
 * \brief Задача 1
 *
 * Решение этой задачи размещается в папке lab_04_01. В функции main следует
 * сравнить поведение реализованных функций1 и функций из стандартной библиотеки. 
 * От студента ожидается ровно один функциональный тест в этой задаче — на вход ничего не подаётся, 
 * файл pos_01_in.txt пуст, на экран следует распечатывать количество 
 * проваленных сравнений поведения реализованных функций и функций стандартной библиотеки.
 * Требуется самостоятельно реализовать аналоги следующих строковых функций:
 * 0. strpbrk;
 * 1. strspn;
 * 2. strcspn;
 * 3. strchr;
 * 4. strrchr. 
 */

#include <string.h>
#include "f.h"
#include "consts.h"
#include <stdio.h>

void test_my_strbprk(int *failures)
{
    *failures += (strpbrk("hello world", "o") != my_strpbrk("hello world", "o")) + 
        (strpbrk("hello world", "h") != my_strpbrk("hello world", "h")) + 
        (strpbrk("hello world", "wr") != my_strpbrk("hello world", "wr")) + 
        (strpbrk("hello world", "") != my_strpbrk("hello world", "")) + 
        (strpbrk("hello world", "a") != my_strpbrk("hello world", "a")) + 
        (strpbrk("hello world", "\0") != my_strpbrk("hello world", "\0")) + 
        (strpbrk("", "a") != my_strpbrk("", "a")) + 
        (strpbrk("", "") != my_strpbrk("", "")) + 
        (strpbrk("", "\0") != my_strpbrk("", "\0"));
}

void test_my_strspn(int *failures)
{
    *failures += (strspn("hello world", "ehlo") != my_strspn("hello world", "ehlo")) + 
        (strspn("hello world", "a") != my_strspn("hello world", "a")) + 
        (strspn("hello world", "") != my_strspn("hello world", "")) + 
        (strspn("hello world", "\0") != my_strspn("hello world", "\0")) + 
        (strspn("", "") != my_strspn("", "")) + 
        (strspn("", "a") != my_strspn("", "a")) + 
        (strspn("", "\0") != my_strspn("", "\0"));
}

void test_my_strcspn(int *failures)
{
    *failures += (strcspn("hello world", "o") != my_strcspn("hello world", "o")) + 
        (strcspn("hello world", "h") != my_strcspn("hello world", "h")) + 
        (strcspn("hello world", "d") != my_strcspn("hello world", "d")) + 
        (strcspn("hello world", " ") != my_strcspn("hello world", " ")) + 
        (strcspn("hello world", "\0") != my_strcspn("hello world", "\0")) + 
        (strcspn("hello world", "") != my_strcspn("hello world", "")) + 
        (strcspn("hello world", "hd") != my_strcspn("hello world", "hd")) + 
        (strcspn("", "") != my_strcspn("", "")) + 
        (strcspn("", "o") != my_strcspn("", "o")) + 
        (strcspn("", "\0") != my_strcspn("", "\0")) + 
        (strcspn("", "h") != my_strcspn("", "h")) + 
        (strcspn("a", "") != my_strcspn("a", "")) + 
        (strcspn("a", "a") != my_strcspn("a", "a")) + 
        (strcspn("a", "\0") != my_strcspn("a", "\0")) + 
        (strcspn("a", "aaa") != my_strcspn("a", "aaa")) + 
        (strcspn("a", "o") != my_strcspn("a", "o"));
}

void test_my_strchr(int *failures)
{
    *failures += (strchr("hello world", 'o') != my_strchr("hello world", 'o')) + 
        (strchr("hello world", 'h') != my_strchr("hello world", 'h')) + 
        (strchr("hello world", 'd') != my_strchr("hello world", 'd')) + 
        (strchr("hello world", ' ') != my_strchr("hello world", ' ')) + 
        (strchr("hello world", '\0') != my_strchr("hello world", '\0')) + 
        (strchr("", 'a') != my_strchr("", 'a')) + 
        (strchr("", '\0') != my_strchr("", '\0')) + 
        (strchr("a", 'a') != my_strchr("a", 'a')) + 
        (strchr("a", 'o') != my_strchr("a", 'o')) + 
        (strchr("a", '\0') != my_strchr("a", '\0'));
}

void test_my_strrchr(int *failures)
{
    *failures += (strrchr("hello world", 'o') != my_strrchr("hello world", 'o')) + 
        (strrchr("hello world", 'h') != my_strrchr("hello world", 'h')) + 
        (strrchr("hello world", 'd') != my_strrchr("hello world", 'd')) + 
        (strrchr("hello world", ' ') != my_strrchr("hello world", ' ')) + 
        (strrchr("hello world", '\0') != my_strrchr("hello world", '\0')) + 
        (strrchr("", 'a') != my_strrchr("", 'a')) + 
        (strrchr("", '\0') != my_strrchr("", '\0')) + 
        (strrchr("a", 'a') != my_strrchr("a", 'a')) + 
        (strrchr("a", 'o') != my_strrchr("a", 'o')) + 
        (strrchr("a", '\0') != my_strrchr("a", '\0')) + 
        (strrchr("aa", ' ') != my_strrchr("aa", ' ')) + 
        (strrchr("aa", 'a') != my_strrchr("aa", 'a')) + 
        (strrchr("aa", 'o') != my_strrchr("aa", 'o')) + 
        (strrchr("aa", '\0') != my_strrchr("aa", '\0')) + 
        (strrchr("aa", '\n') != my_strrchr("aa", '\n')) + 
        (strrchr("\0", '\0') != my_strrchr("\0", '\0'));
}

int main(void)
{
    int failures = 0;
    // strpbrk
    test_my_strbprk(&failures);

    // strspn
    test_my_strspn(&failures);

    // strcspn
    test_my_strcspn(&failures);

    // strchr 
    test_my_strchr(&failures);
        
    // strrchr
    test_my_strrchr(&failures);

    printf("%d\n", failures);

    return 0;
}
