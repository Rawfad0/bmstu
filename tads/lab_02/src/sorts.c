#include "sorts.h"

/**
 * @brief Двоичный поиск для вставки элемента
 * 
 * @param base Указатель на начало сортируемой области
 * @param x вставляемый элемент
 * @param nmemb количество элементов
 * @param size размер элемента
 * @param compar указатель на функцию сравнения элементов
 * @return void* указатель на место вставки элемента
 */
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

/**
 * @brief Поиск от конца к началу для вставки элемента
 * 
 * @param base Указатель на начало сортируемой области
 * @param x вставляемый элемент
 * @param nmemb количество элементов
 * @param size размер элемента
 * @param compar указатель на функцию сравнения элементов
 * @return void* указатель на место вставки элемента
 */
void *end_to_beg_search(void *base, void *x, size_t nmemb, size_t size, int (*compar)(const void*, const void*))
{
    char *pb = base, *pe = (char *) base + size * nmemb;
    char *pa;
    for (pa = pe - size; pa > pb && (* compar)(x, pa) <= 0; pa -= size)
        ;
    return (void *)(pa + size);
}

/**
 * @brief Циклический сдвиг вправо
 * 
 * @param pb Указатель на начало области
 * @param pe Указатель на конец области
 * @param size размер элемента (или же размер сдвига в char'ах)
 */
void right_cycle_shift(void *pb, void *pe, size_t size)
{
    char p_temp[size];
    memcpy(p_temp, pe, size);
    for (char *pa = pe; pa > (char *) pb; pa -= size)
        memcpy(pa, pa - size, size);
    memcpy(pb, p_temp, size);
}

/**
 * @brief Функция сортировки бинарными вставками
 * 
 * @param base Указатель на начало сортируемой области
 * @param nmemb количество элементов
 * @param size размер элемента
 * @param compar указатель на функцию сравнения элементов
 */
void binary_insertion_sort(void *base, size_t nmemb, size_t size, int (*compar)(const void*, const void*))
{
    char *pb = base, *pe = pb + nmemb * size;
    char *p_insert = NULL;

    for (char *pa = pb + size; pa < pe; pa += size)
    {
        p_insert = binary_search(pb, pa, (pa - pb) / size, size, (*compar));
        if (pa != p_insert)
            right_cycle_shift(p_insert, pa, size);
    }
}

/**
 * @brief Функция сортировки бинарными вставками
 * 
 * @param base Указатель на начало сортируемой области
 * @param nmemb количество элементов
 * @param size размер элемента
 * @param compar указатель на функцию сравнения элементов
 */
void insertion_sort(void *base, size_t nmemb, size_t size, int (*compar)(const void*, const void*))
{
    char *pb = base, *pe = pb + nmemb * size;
    char *p_insert = NULL;

    for (char *pa = pb + size; pa < pe; pa += size)
    {
        p_insert = end_to_beg_search(pb, pa, (pa - pb) / size, size, (*compar));
        if (pa != p_insert)
            right_cycle_shift(p_insert, pa, size);
    }
}
