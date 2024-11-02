#include "associative_array.h"

#include <string.h>
#include <stdlib.h>

typedef struct
{
    char *key;
    int value;
} pair_t;

// Реализация на основе отсортированного динамически расширяемого массива
struct assoc_array_type
{
    pair_t *arr;    // Динамически расширяемый массив пар ключ-значение
    size_t n;       // Количество элементов
};

void *binary_search(void *base, void *x, size_t nmemb, size_t size)
{
    char *pb = base, *pe = (char *) base + size * nmemb;
    char *pm = NULL;
    char *res = NULL;

    while (pb < pe && res == NULL)
    {
        pm = pb + (pe - pb) / size / 2 * size;
        if (strcmp(x, ((pair_t *) pm)->key) == 0)
            res = pm + size;
        else if (strcmp(x, ((pair_t *) pm)->key) < 0)
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

assoc_array_t assoc_array_create(void)
{
    assoc_array_t assoc_arr = malloc(sizeof(struct assoc_array_type));
    if (assoc_arr != NULL)
    {
        assoc_arr->arr = NULL;
        assoc_arr->n = 0;
    }
    return assoc_arr;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (arr == NULL);
    else 
    {
        assoc_array_clear(*arr);
        free(*arr);
        *arr = NULL;
    }
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    if (arr == NULL || key == NULL || strlen(key) == 0)
        rc = ASSOC_ARRAY_INVALID_PARAM;
    else
    {
        pair_t *p_insert = binary_search(arr->arr, (char *) key, arr->n, sizeof(pair_t));
        if (p_insert != arr->arr && strcmp(key, (p_insert - 1)->key) == 0)
            rc = ASSOC_ARRAY_KEY_EXISTS;
        else
        {
            void *tmp = realloc(arr->arr, (arr->n + 1) * sizeof(pair_t));
            char *str = NULL;
            if (tmp == NULL)
                rc = ASSOC_ARRAY_MEM;
            else if ((str = malloc(sizeof(char) * (strlen(key) + 1))) == NULL)
                rc = ASSOC_ARRAY_MEM, free(tmp);
            else
            {
                arr->arr = tmp;
                memcpy(str, key, sizeof(char) * (strlen(key) + 1));
                arr->arr[arr->n].key = str;
                arr->arr[arr->n].value = num;
                p_insert = binary_search(arr->arr, arr->arr[arr->n].key, arr->n, sizeof(pair_t));
                right_cycle_shift(p_insert, arr->arr + arr->n, sizeof(pair_t));
                (arr->n)++;
            }
        }
    }
    return rc;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    if (arr == NULL || num == NULL || key == NULL || strcmp(key, "") == 0)
        rc = ASSOC_ARRAY_INVALID_PARAM;
    else
    {
        pair_t *tmp = binary_search(arr->arr, (char *) key, arr->n, sizeof(pair_t));
        if (tmp == arr->arr || strcmp(key, (tmp - 1)->key) != 0)
            rc = ASSOC_ARRAY_NOT_FOUND;
        else
            *num = &((tmp - 1)->value);
    }
    return rc;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    if (arr == NULL || key == NULL || strcmp(key, "") == 0)
        rc = ASSOC_ARRAY_INVALID_PARAM;
    else
    {
        pair_t *p_rem = binary_search(arr->arr, (char *) key, arr->n, sizeof(pair_t));
        if (p_rem == arr->arr || strcmp(key, (p_rem - 1)->key) != 0)
            rc = ASSOC_ARRAY_NOT_FOUND;
        else
        {
            p_rem--;
            free(p_rem->key);
            for (pair_t *pa = p_rem + 1; pa < arr->arr + arr->n; pa++)
                memcpy(pa - 1, pa, sizeof(pair_t));
            (arr->n)--;
            pair_t *tmp = NULL;
            if (arr->n == 0)
                free(arr->arr), arr->arr = NULL;
            else if ((tmp = realloc(arr->arr, (arr->n) * sizeof(pair_t))) == NULL)
                rc = ASSOC_ARRAY_MEM;
            else
                arr->arr = tmp;
        }
    }
    return rc;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    if (arr == NULL)
        rc = ASSOC_ARRAY_INVALID_PARAM;
    else
    {
        for (pair_t *pa = arr->arr; pa < arr->arr + arr->n; pa++)
            free(pa->key);
        free(arr->arr);
        arr->arr = NULL;
        arr->n = 0;
    }
    return rc;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    if (arr == NULL || (*action) == NULL)
        rc = ASSOC_ARRAY_INVALID_PARAM;
    else
        for (pair_t *pa = arr->arr; pa < arr->arr + arr->n; pa++)
            (*action)(pa->key, &pa->value, param);
    return rc;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    if (arr == NULL || num == NULL)
        rc = ASSOC_ARRAY_INVALID_PARAM;
    else if (arr->arr == NULL)
        rc = ASSOC_ARRAY_NOT_FOUND;
    else
        *num = &(arr->arr[0].value);
    return rc;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    if (arr == NULL || num == NULL)
        rc = ASSOC_ARRAY_INVALID_PARAM;
    else if (arr->arr == NULL)
        rc = ASSOC_ARRAY_NOT_FOUND;
    else
        *num = &(arr->arr[arr->n - 1].value);
    return rc;
}
