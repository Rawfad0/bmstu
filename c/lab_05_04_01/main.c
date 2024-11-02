/**
 * @file main.c
 * @brief Задача 3
 * 
 * О каждом студенте известны:
 *  (a) фамилия, не более 25 символов;
 *  (b) имя, не более 10 символов;
 *  (c) оценки по четырём предметам, сохраняемые в виде массива целых беззнаковых в 32 бита.
 * 
 * Требуется написать программу, совершающую действие в ответ на вызов с ключом:
 *  (a) Сортировка студентов по фамилии, студенты с одинаковыми фамилиями
 *  должны быть упорядочены по имени. Результат выводится на экран.
 *  Запуск программы для обработки текстового файла:
 *      ./app.exe st FILE
 *  Запуск программы для обработки двоичного файла:
 *      ./app.exe sb FILE
 *  
 *  (b) Вывод информации о студентах, фамилии которых начинаются с заданной подстроки, в другой файл.
 *  Запуск программы для обработки текстового файла:
 *      ./app.exe ft FILE_SRC FILE_DST SUBSTR
 *  Запуск программы для обработки двоичного файла:
 *      ./app.exe fb FILE_SRC FILE_DST SUBSTR
 *
 *  (c) Удаление из файла студентов, чей средний балл меньше среднего балла
 *  по всему файлу. Результат записывается в тот же файл.
 *  Запуск программы для обработки текстового файла:
 *      ./app.exe dt FILE
 *  Запуск программы для обработки двоичного файла:
 *      ./app.exe db FILE
 */

#include "f.h"
#include "translator.h"
#include "io.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int truncate(const char *path, off_t length);

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
 * @brief Обработка ключа fb
 * 
 * @param argc количество аргументов командной строки
 * @param argv аргументы командной строки
 * @return int код выхода
 */
int find_bin(int argc, char **argv)
{
    FILE *f1, *f2;
    int r = 0;

    if (argc != 5)
        return EXIT_CODE_INCORRECT_ARGUMENT_COUNT;

    if (strlen(argv[4]) > LAST_NAME_MAX || strlen(argv[4]) == 0)
        return EXIT_CODE_INCORRECT_PREFIX;

    f1 = fopen(argv[2], "rb");
    if (f1 == NULL)
        return EXIT_CODE_INCORRECT_FILE;
    f2 = fopen(argv[3], "wb");
    if (f2 == NULL)
        return EXIT_CODE_INCORRECT_FILE;

    r = find_stud_bin_file(f1, f2, argv[4]);

    fclose(f1);
    fclose(f2);

    if (r != 0)
        truncate(argv[3], 0);

    return r;
}

/**
 * @brief Обработка ключа db
 * 
 * @param argc количество аргументов командной строки
 * @param argv аргументы командной строки
 * @return int код выхода
 */
int del_bin(int argc, char **argv)
{
    FILE *f;
    size_t new_size;
    int r = 0;

    if (argc != 3)
        return EXIT_CODE_INCORRECT_ARGUMENT_COUNT;

    f = fopen(argv[2], "r+b");
    if (!f)
        return EXIT_CODE_INCORRECT_FILE;

    r = del_stud_bin_file(f, &new_size);
    truncate(argv[2], new_size);

    fclose(f);
    
    return r;
}

/**
 * @brief Обработка ключа sb
 * 
 * @param argc количество аргументов командной строки
 * @param argv аргументы командной строки
 * @return int код выхода
 */
int sort_bin(int argc, char **argv)
{
    FILE *f;
    int r = 0;

    if (argc != 3)
        return EXIT_CODE_INCORRECT_ARGUMENT_COUNT;

    f = fopen(argv[2], "r+b");
    if (!f)
        return EXIT_CODE_INCORRECT_FILE;

    r = sort_stud_bin_file(f);
    if (r == 0)
        r = print_students(f);
    
    fclose(f);

    return r;
}

int main(int argc, char **argv)
{
    if (argc < 3)
        return EXIT_CODE_INCORRECT_ARGUMENT_COUNT;

    // Сортировка
    if (strcmp(argv[1], "sb") == 0)
        return sort_bin(argc, argv);
    // Поиск
    if (strcmp(argv[1], "fb") == 0)
        return find_bin(argc, argv);
    // Удаление
    if (strcmp(argv[1], "db") == 0)
        return del_bin(argc, argv);

    // Ключи преобразования файлов
    if (strcmp(argv[1], "t2b") == 0)
        return t2b(argc, argv);
    if (strcmp(argv[1], "b2t") == 0)
        return b2t(argc, argv);

    return EXIT_CODE_INCORRECT_ARGUMENT;
}
