/**
 * @file main.c
 * @brief Лабораторная работа №6
 *
 * Вариант No2
 * В текстовом файле хранится информация о предметах, которая включает в себя название предмета, 
 * его массу и объём. В названии предмета не более двадцати пяти символов. 
 * Масса и объём задаются вещественными числами. Количество предметов в файле не указано. 
 * Требуется написать программу, которая, будучи вызванной из командной строки:
 * "app.exe FILE [PREFIX]", где FILE — имя файла, PREFIX — искомая начальная подстрока;
 *  1. считывает информацию о предметах в массив.
 *  2. Если подстрока не указана, сортирует информацию о предметах по возрастанию значения плотности, 
 * после чего выводит упорядоченный массив на экран.
 *  3. Если значение подстроки равно «ALL», выводит информацию обо всех предметах.
 *  4. Если подстрока указана и не равна «ALL», выводит на экран информацию о предметах, 
 * названия которых начинаются с указанной подстроки.
 *
 */

#include "funcs.h"
#include "io.h"
#include "consts.h"
#include "structs.h"
#include <string.h>

int controller(int argc, char **argv, struct object *obj_arr, size_t n);

int main(int argc, char **argv)
{
    if (argc != NO_PREFIX && argc != PREFIX)
        return EXIT_CODE_INCORRECT_ARGUMENT_COUNT;
    
    struct object obj_arr[N_MAX];
    size_t n = 0;
    int rc = 0;
    char *file_name = argv[1];
    
    if (rc = read_objects(file_name, obj_arr, &n), rc == 0)
        rc = controller(argc, argv, obj_arr, n);
    
    return rc;
}

int controller(int argc, char **argv, struct object *obj_arr, size_t n)
{
    int rc = 0;
    char *prefix;

    if (argc == NO_PREFIX)
    {
        sort_objects_by_density(obj_arr, n);        // Сортировка по плотности
        print_all_objects(obj_arr, n);              // Вывод отсортированного массива
    }
    else if (prefix = argv[2], strlen(prefix) > NAME_MAX)
        rc = EXIT_CODE_INCORRECT_PREFIX;
    else if (!strcmp(prefix, "ALL"))
        print_all_objects(obj_arr, n);              // Вывод всех объектов если префикс = "ALL"
    else
    {
        // Поиск и вывод элементов по префикс
        struct object found_obj_arr[N_MAX];
        size_t found_n = 0;
        if (rc = find_prefix(obj_arr, n, found_obj_arr, &found_n, prefix), !rc)
            print_all_objects(found_obj_arr, found_n);
    }
    return rc;
}
