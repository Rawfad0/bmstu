#include "io.h"

void print_film(film_t film)
{
    printf("%s\n%s\n%d\n", film.title, film.name, film.year);
}

void print_film_arr(film_arr_t film_arr)
{
    for (size_t i = 0; i < film_arr.n; i++)
        print_film(film_arr.arr[i]);
}
