/**
 * @file main.c
 * @brief Обработка массива структур с динамическими полями
 *
 * Вариант №1
 * В текстовом файле хранится информация о кинофильмах, которая включает в себя
 * название кинофильма, фамилию режиссёра и год выхода на экран. Год выхода задаётся
 * целым числом. Количество кинофильмов в самом файле не указано. Требуется написать
 * программу, которая, будучи вызванной из командной строки:
 * app.exe FILE FIELD [KEY]
 * где FILE — имя файла, FIELD — анализируемое поле, KEY — значение ключа;
 * 1. считывает информацию о кинофильмах в массив. Информация после чтения полей
 *      каждой структуры помещается в массив таким образом, чтобы он сразу же был
 *      упорядочен по указанному полю.
 * 2. Если значение ключа не указано, выводит упорядоченный массив.
 * 3. Если значение ключа указано, выполняет двоичный поиск по полю и значению
 *      ключа. Если кинофильм с искомым значением ключа найден, программа выводит
 *      информацию о нём на экран, иначе программа выводит сообщение «Not found».
 * Возможные значения FIELD:
 * 1. «title» — название кинофильма;
 * 2. «name» — фамилия режиссёра;
 * 3. «year» — год выхода
 */

#include "consts.h"
#include "film.h"
#include "io.h"
#include <string.h>

int controller(int argc, char **argv, film_arr_t film_arr, int (*compar)(const void*, const void*));

int comparator_controller(char *field, int (**compar)(const void *, const void *));

int main(int argc, char **argv)
{
    if (argc != ARGC_WITH_KEY && argc != ARGC_WITHOUT_KEY)
        return RC_INCORRECT_ARG_COUNT;

    film_arr_t film_arr = { NULL, 0 };
    int (*compar)(const void*, const void*);
    int rc = RC_OK;

    if ((rc = comparator_controller(FIELD, &compar)));
    else if ((rc = read_film_array(FILENAME, &film_arr, (*compar))));
    else
        rc = controller(argc, argv, film_arr, (*compar));
    free_film_arr(&film_arr);

    return rc;
}

int comparator_controller(char *field, int (**compar)(const void *, const void *))
{
    int rc = RC_OK;
    if (strcmp("title", field) == 0)
        *compar = compare_by_title;
    else if (strcmp("name", field) == 0)
        *compar = compare_by_name;
    else if (strcmp("year", field) == 0)
        *compar = compare_by_year;
    else
        rc = RC_INCORRECT_FIELD;
    return rc;
}

int controller(int argc, char **argv, film_arr_t film_arr, int (*compar)(const void*, const void*))
{
    int rc = RC_OK;
    if (argc == ARGC_WITH_KEY)
    {
        film_t *film = NULL;
        char *end;
        if (strcmp("year", FIELD) == 0)
            if (strtol(KEY, &end, 10), end != KEY + strlen(KEY))
                rc = RC_INCORRECT_KEY;
        if (rc == RC_OK)
        {
            film = find_film(film_arr, FIELD, KEY, (*compar));
            if (film == NULL)
                printf("Not found\n");
            else
                print_film(*film);
        }
    }
    else
        print_film_arr(film_arr);
    return rc;
}
