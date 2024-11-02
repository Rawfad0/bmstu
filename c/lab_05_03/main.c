/**
 * @file main.c
 * @brief Задача 3
 * 
 * 1. создавать файл и заполнять его случайными числами;
 * 2. выводить числа из файла на экран (app.exe p file);
 * 3. упорядочивать числа в файле (app.exe s file).
 * Тип int, сортировка выбором по возрастанию.
 */

#include "f.h"
#include "translator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Обработка ключа t2b
 * 
 * @param argc количество аргументов командной строки
 * @param argv аргументы командной строки
 * @return int код выхода
 */
int t2b(int argc, char **argv)
{
    FILE *f, *b;
    int r = 0;

    if (argc != 4)
        return EXIT_CODE_INCORRECT_ARGUMENT_COUNT;

    f = fopen(argv[2], "r");
    b = fopen(argv[3], "wb");
    if (!f)
        return EXIT_CODE_INCORRECT_FILE;

    r = text_to_binary(b, f);

    fclose(f);
    fclose(b);
    
    return r;
}

/**
 * @brief Обработка ключа b2t
 * 
 * @param argc количество аргументов командной строки
 * @param argv аргументы командной строки
 * @return int код выхода
 */
int b2t(int argc, char **argv)
{
    FILE *f, *b;
    int r = 0;

    if (argc != 4)
        return EXIT_CODE_INCORRECT_ARGUMENT_COUNT;

    b = fopen(argv[2], "rb");
    f = fopen(argv[3], "w");
    if (!f)
        return EXIT_CODE_INCORRECT_FILE;

    r = binary_to_text(b, f);

    fclose(f);
    fclose(b);
    
    return r;
}

/**
 * @brief Обработка ключа c
 * 
 * @param argc количество аргументов командной строки
 * @param argv аргументы командной строки
 * @return int код выхода
 */
int fill(int argc, char **argv)
{
    FILE *f;
    size_t num;
    char *end_ptr;

    if (argc != 4)
        return EXIT_CODE_INCORRECT_ARGUMENT_COUNT;

    num = strtoul(argv[2], &end_ptr, 10);
    if (*end_ptr != '\0')
        return EXIT_CODE_INCORRECT_ARGUMENT;

    f = fopen(argv[3], "wb");
    if (!f)
        return EXIT_CODE_INCORRECT_FILE;

    fill_random_int_bin_file(f, num);

    fclose(f);

    return 0;
}

/**
 * @brief Обработка ключа p
 * 
 * @param argc количество аргументов командной строки
 * @param argv аргументы командной строки
 * @return int код выхода
 */
int print(int argc, char **argv)
{
    FILE *f;
    int r = 0;

    if (argc != 3)
        return EXIT_CODE_INCORRECT_ARGUMENT_COUNT;

    f = fopen(argv[2], "rb");
    if (!f)
        return EXIT_CODE_INCORRECT_FILE;

    r = print_int_bin_file(f);

    fclose(f);
    
    return r;
}

/**
 * @brief Обработка ключа s
 * 
 * @param argc количество аргументов командной строки
 * @param argv аргументы командной строки
 * @return int код выхода
 */
int sort(int argc, char **argv)
{
    FILE *f;
    int r = 0;

    if (argc != 3)
        return EXIT_CODE_INCORRECT_ARGUMENT_COUNT;

    f = fopen(argv[2], "r+b");
    if (!f)
        return EXIT_CODE_INCORRECT_FILE;

    r = sort_int_bin_file(f);

    fclose(f);

    return r;
}

int main(int argc, char **argv)
{
    if (argc < 3)
        return EXIT_CODE_INCORRECT_ARGUMENT_COUNT;

    if (strcmp(argv[1], "c") == 0)
        return fill(argc, argv);
    if (strcmp(argv[1], "p") == 0)
        return print(argc, argv);
    if (strcmp(argv[1], "s") == 0)
        return sort(argc, argv);

    // Ключи преобразования файлов
    if (strcmp(argv[1], "t2b") == 0)
        return t2b(argc, argv);
    if (strcmp(argv[1], "b2t") == 0)
        return b2t(argc, argv);

    return EXIT_CODE_INCORRECT_ARGUMENT;
}
