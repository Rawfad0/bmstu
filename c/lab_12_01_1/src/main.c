/**
 * @file main.c
 * 
 * Написать программу, которая упорядочивает данные в целочисленном массиве по возрастанию. 
 * Данные в массив считываются из текстового файла. Память под массив выделяется динамически. 
 * Количество элементов в файле не указано и определяется при первом проходе по текстовому файлу, 
 * во время второго прохода числа считываются в массив.
 *
 * Требуется написать программу, которая, будучи вызванной из командной строки:
 * app.exe IN_FILE OUT_FILE [f]
 * где IN_FILE — имя файла с входными данными, OUT_FILE — имя файла с выходными данными, 
 * f — запрос фильтрации перед сортировкой;
 * 1. Считает количество элементов, записанных в файле.
 * 2. Выделяет память под соответствующее количество элементов.
 * 3. Читает файл ещё раз, заполняя динамический массив.
 * 4. Если указан параметр f, вызывает функцию-фильтр.
 * 5. Сортирует массив с новыми элементами с помощью назначенного преподавателем алгоритма сортировки.
 * 6. Записывает элементы отсортированного массива в текстовый файл.
 *
 * Функция-фильтр работает следующим образом:
 * 1. определяет количество элементов массива, которые удовлетворяют заданному условию;
 * 2. выделяет память под соответствующее количество элементов;
 * 3. копирует элементы, удовлетворяющие условию, из старого массива в новый.
 *
 * Функция-фильтр имеет следующие название и прототип:
 * int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
 * На вход функции-фильтру могут поступать некорректные данные.
 *
 * Функция сортировки реализуется универсальной, т. е. имеет одинаковый прототип с функцией qsort
 * из стандартной библиотеки и называется mysort.
 *
 */

#include "consts.h"
#include "io.h"
#include "mysort.h"
#include "key.h"
#include <string.h>
#include <stdlib.h>

int controller(int argc, char **argv, int *pb, int *pe);

int main(int argc, char **argv)
{
    if (argc != ARGC_NO_FILTER && argc != ARGC_FILTER)
        return RC_INCORRECT_ARGUMENT_COUNT;    // некорректное количество аргументов

    size_t n = 0;
    int rc = 0;

    if (!(rc = count_int_arr_len(FILE_IN, &n)))
    {
        int *pb = malloc(n * sizeof(int));
        if (!pb)
            rc = RC_ALLOCATION_FAILED;
        else
        {
            int *pe = pb + n;
            if (!(rc = read_int_arr(FILE_IN, pb, pe)))
                rc = controller(argc, argv, pb, pe);
            free(pb);
        }
    }
    return rc;
}

int controller(int argc, char **argv, int *pb, int *pe)
{
    int rc = 0;

    if (argc == ARGC_FILTER && !strcmp(F_ARG, FILTER_KEY))
    {
        size_t size = 0;
        int *pb_new = NULL, *pe_new = NULL;
        if ((rc = get_new_arr_size(pb, pe, &pb_new, &pe_new)) != RC_OK);
        else if (size = pe_new - pb_new, (pb_new = malloc(size * sizeof(int))) == NULL)
            rc = RC_ALLOCATION_FAILED;
        else if (pe_new = pb_new + size, (rc = key(pb, pe, pb_new)) == RC_OK)
        {
            mysort(pb_new, pe_new - pb_new, sizeof(int), compare_int);
            rc = write_int_arr(FILE_OUT, pb_new, pe_new);
        }
        if (pb_new != NULL)
            free(pb_new);
    }  
    else if (argc == ARGC_NO_FILTER)
    {
        mysort(pb, pe - pb, sizeof(int), compare_int);
        rc = write_int_arr(FILE_OUT, pb, pe);
    }
    else 
        rc = RC_INCORRECT_ARGUMENT;
    return rc;
}
