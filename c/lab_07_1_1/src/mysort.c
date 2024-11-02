#include "mysort.h"

int compare_int(const void *p, const void *q)
{
    return *(int*)p - *(int*)q;
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

void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void*, const void*))
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
