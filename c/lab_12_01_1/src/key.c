#include "key.h"

void find_max_and_min(int *pb, int *pe, int **p_min, int **p_max)
{
    *p_min = pb, *p_max = pb;
    for (int *pa = pb; pa < pe; pa++)
        if (*pa < **p_min)
            *p_min = pa;
        else if (*pa > **p_max)
            *p_max = pa;
}

void reorder_pointers(int *p1, int *p2, int **pa, int **pb)
{
    if (p1 < p2)
        *pa = p1, *pb = p2;
    else
        *pa = p2, *pb = p1;
}

int get_new_arr_size(const int *pb_src, const int *pe_src, int **pb, int **pe)
{
    if (pe_src - pb_src <= 0)
        return RC_INCORRECT_ARRAY;     // Исходный массив пуст или указатели не в том порядке
    
    int rc = 0;
    int *p_min, *p_max;
    find_max_and_min((int *) pb_src, (int *) pe_src, &p_min, &p_max);
    if (p_min == p_max || (labs(p_min - p_max) - 1) == 0)
        rc = RC_INCORRECT_DST_ARRAY;   // Один и тот же элемент либо соседние элементы
    else
    {
        reorder_pointers(p_min, p_max, pb, pe);
        ++*pb;
    }
    return rc;
}


int key(const int *pb_src, const int *pe_src, int *pb_dst)
{
    int rc = 0;
    int *pb, *pe;
    if ((rc = get_new_arr_size(pb_src, pe_src, &pb, &pe)) == RC_OK)
        for (int *pa = pb_dst; pb < pe; pa++, pb++)
            *pa = *pb;
    return rc;
}
