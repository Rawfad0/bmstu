#include "film.h"

void free_film(film_t *film)
{
    free(film->title);
    free(film->name);
}

void free_film_arr(film_arr_t *film_arr)
{
    for (size_t i = 0; i < film_arr->n; i++)
        free_film(film_arr->arr + i);
    free(film_arr->arr);
    film_arr->n = 0;
}

int compare_by_title(const void *p, const void *q)
{
    return strcmp(((film_t *) p)->title, ((film_t *) q)->title);
}

int compare_by_name(const void *p, const void *q)
{
    return strcmp(((film_t *) p)->name, ((film_t *) q)->name);
}

int compare_by_year(const void *p, const void *q)
{
    return ((film_t *) p)->year - ((film_t *) q)->year;
}

void *binary_search(void *base, void *x, size_t nmemb, size_t size, int (*compar)(const void*, const void*))
{
    char *pb = base, *pe = (char *) base + size * nmemb;
    char *pm = NULL;
    char *res = NULL;

    while (pb < pe && res == NULL)
    {
        pm = pb + (pe - pb) / size / 2 * size;

        if ((* compar)(x, pm) == 0)
            res = pm + size;
        else if ((* compar)(x, pm) < 0)
            pe = pm;
        else
            pb = pm + size;
    }
    if (res == NULL)
        res = pb;
    return (void *) res;
}

void right_cycle_shift(void *pb, void *pe, size_t size)
{
    char p_temp[size];
    memcpy(p_temp, pe, size);
    for (char *pa = pe; pa > (char *) pb; pa -= size)
        memcpy(pa, pa - size, size);
    memcpy(pb, p_temp, size);
}

int film_arr_add(film_arr_t *film_arr, film_t film, int (*compar)(const void*, const void*))
{
    int rc = RC_OK;

    void *temp = realloc(film_arr->arr, (film_arr->n + 1) * sizeof(film_t));
    if (temp == NULL)
        rc = RC_ALLOCATION_FAILED;
    else
    {
        film_arr->arr = temp;
        film_arr->arr[film_arr->n].title = film.title;
        film_arr->arr[film_arr->n].name = film.name;
        film_arr->arr[film_arr->n].year = film.year;

        char *pb = (void *) film_arr->arr, *pe = pb + film_arr->n * sizeof(film_t);
        char *p_insert = binary_search(pb, &film, film_arr->n, sizeof(film_t), (*compar));
        right_cycle_shift(p_insert, pe, sizeof(film_t));
        (film_arr->n)++;
    }
    return rc;
}

int read_film(FILE *f, film_t *film)
{
    int rc = RC_OK;
    size_t len = 0;
    int read;

    if ((read = getline(&film->title, &len, f)) == -1 || read <= 1)
        rc = RC_INCORRECT_INPUT;
    else if ((read = getline(&film->name, &len, f)) == -1 || read <= 1)
        rc = RC_INCORRECT_INPUT;
    else if (fscanf(f, "%d\n", &(film->year)) != 1 || film->year <= 0)
        rc = RC_INCORRECT_INPUT;
    else
    {
        if (film->title[strlen(film->title) - 1] == '\n')
            film->title[strlen(film->title) - 1] = '\0';
        if (film->name[strlen(film->name) - 1] == '\n')
            film->name[strlen(film->name) - 1] = '\0';
    }
    return rc;
}

int read_film_array(char *file_name, film_arr_t *film_arr, int (*compar)(const void*, const void*))
{
    int rc = RC_OK;

    FILE *f = fopen(file_name, "r");
    if (f == NULL)
        rc = RC_INCORRECT_FILE;
    else
    {
        while (!feof(f) && rc == RC_OK)
        {
            film_t film = { NULL, NULL, 0 };
            if ((rc = read_film(f, &film)))
                free_film(&film);
            else
                rc = film_arr_add(film_arr, film, (*compar));
        }
        fclose(f);
    }
    return rc;
}

film_t *find_film(film_arr_t film_arr, char *field, char *key, int (*compar)(const void*, const void*))
{
    film_t film = { NULL, NULL, 0 };
    film_t *p_film = NULL;

    if (strcmp("title", field) == 0)
        film.title = key;
    else if (strcmp("name", field) == 0)
        film.name = key;
    else if (strcmp(field, "year") == 0)
        film.year = strtol(key, NULL, 10);

    char *p_insert = binary_search(film_arr.arr, &film, film_arr.n, sizeof(film_t), (*compar));

    if (p_insert > (char *) film_arr.arr && compar((film_t *) p_insert - 1, &film) == 0)
        p_film = ((film_t *) p_insert - 1);
    return p_film;
}
