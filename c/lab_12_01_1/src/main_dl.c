#include "consts.h"
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef int (*fm_count_int_arr_len_t)(char *, size_t *);
typedef int (*fm_read_int_arr_t)(char *, int *, int *);
typedef int (*fm_write_int_arr_t)(char *, int *, int *);
typedef int (*fm_get_new_arr_size_t)(const int *, const int *, int **, int **);
typedef int (*fm_key_t)(const int *, const int *, int *);
typedef int (*fm_compare_int_t)(const void *, const void *);
typedef void (*fm_mysort_t)(void *, size_t, size_t, int (*)(const void*, const void*));

int func_loader(
    fm_count_int_arr_len_t *count_int_arr_len,
    fm_read_int_arr_t *read_int_arr,
    fm_write_int_arr_t *write_int_arr,
    fm_get_new_arr_size_t *get_new_arr_size,
    fm_key_t *key,
    fm_compare_int_t *compare_int,
    fm_mysort_t *mysort);

int controller(int argc, char **argv, int *pb, int *pe,
    fm_write_int_arr_t write_int_arr,
    fm_get_new_arr_size_t get_new_arr_size,
    fm_key_t key,
    fm_compare_int_t compare_int,
    fm_mysort_t mysort);

int main(int argc, char **argv)
{
    if (argc != ARGC_NO_FILTER && argc != ARGC_FILTER)
        return RC_INCORRECT_ARGUMENT_COUNT;    // некорректное количество аргументов
    int rc = 0;
    size_t n = 0;
    fm_count_int_arr_len_t count_int_arr_len;
    fm_read_int_arr_t read_int_arr;
    fm_write_int_arr_t write_int_arr;
    fm_get_new_arr_size_t get_new_arr_size;
    fm_key_t key;
    fm_compare_int_t compare_int;
    fm_mysort_t mysort;
    if (RC_OK != (rc = func_loader(&count_int_arr_len, &read_int_arr, 
    &write_int_arr, &get_new_arr_size, &key, &compare_int, &mysort)));
    else if (!(rc = count_int_arr_len(FILE_IN, &n)))
    {
        int *pb = malloc(n * sizeof(int));
        if (!pb)
            rc = RC_ALLOCATION_FAILED;
        else
        {
            int *pe = pb + n;
            if (!(rc = read_int_arr(FILE_IN, pb, pe)))
                rc = controller(argc, argv, pb, pe,
                    write_int_arr, get_new_arr_size, key, compare_int, mysort);
            free(pb);
        }
    }
    return rc;
}

int func_loader(
    fm_count_int_arr_len_t *count_int_arr_len,
    fm_read_int_arr_t *read_int_arr,
    fm_write_int_arr_t *write_int_arr,
    fm_get_new_arr_size_t *get_new_arr_size,
    fm_key_t *key,
    fm_compare_int_t *compare_int,
    fm_mysort_t *mysort)
{
    int rc = RC_OK;
    void* hlib;

    hlib = dlopen("./out/libarr.so", RTLD_NOW);
    if ((hlib = dlopen("./out/libarr.so", RTLD_NOW)) == NULL)
        rc = RC_DL_FAILED;
    else if ((*count_int_arr_len = (fm_count_int_arr_len_t) dlsym(hlib, "count_int_arr_len")) == NULL)
        rc = RC_DL_FUNC_FAILED;
    else if ((*read_int_arr = (fm_read_int_arr_t) dlsym(hlib, "read_int_arr")) == NULL)
        rc = RC_DL_FUNC_FAILED;
    else if ((*write_int_arr = (fm_write_int_arr_t) dlsym(hlib, "write_int_arr")) == NULL)
        rc = RC_DL_FUNC_FAILED;
    else if ((*get_new_arr_size = (fm_get_new_arr_size_t) dlsym(hlib, "get_new_arr_size")) == NULL)
        rc = RC_DL_FUNC_FAILED;
    else if ((*key = (fm_key_t) dlsym(hlib, "key")) == NULL)
        rc = RC_DL_FUNC_FAILED;
    else if ((*compare_int = (fm_compare_int_t) dlsym(hlib, "compare_int")) == NULL)
        rc = RC_DL_FUNC_FAILED;
    else if ((*mysort = (fm_mysort_t) dlsym(hlib, "mysort")) == NULL)
        rc = RC_DL_FUNC_FAILED;
    if (rc != RC_DL_FAILED)
        dlclose(hlib);

    return rc;
}

int controller(int argc, char **argv, int *pb, int *pe,
    fm_write_int_arr_t write_int_arr,
    fm_get_new_arr_size_t get_new_arr_size,
    fm_key_t key,
    fm_compare_int_t compare_int,
    fm_mysort_t mysort)
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
