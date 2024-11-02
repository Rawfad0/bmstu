#include "key.h"

void find_max_and_min(int *pb, int *pe, int **p_min, int **p_max)
{
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

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (pe_src - pb_src <= 0)
        return RETURN_CODE_INCORRECT_ARRAY;     // Исходный массив пуст или указатели не в том порядке
    
    int rc = 0;
    int *p_min = (int *) pb_src, *p_max = (int *) pb_src;
    *pb_dst = NULL, *pe_dst = NULL;

    find_max_and_min((int *) pb_src, (int *) pe_src, &p_min, &p_max);
    if (p_min == p_max || !(labs(p_min - p_max) - 1))
        rc = RETURN_CODE_INCORRECT_DST_ARRAY;   // Один и тот же элемент либо соседние элементы
    else
    {
        int *pb = NULL, *pe = NULL;
        reorder_pointers(p_min, p_max, &pb, &pe);
        pb++;

        *pb_dst = malloc((pe - pb) * sizeof(int));
        if (*pb_dst == NULL)
            rc = RETURN_CODE_ALLOCATION_FAILED;     // Память не выделилась
        else
        {
            *pe_dst = *pb_dst + (pe - pb);

            // Указатель pa итерируется по новому массиву от *pb_dst до *pe_dst
            // Указатель pb по исходному массиву от pb до pe
            for (int *pa = *pb_dst; pb < pe; pa++, pb++)
                *pa = *pb;
        }    
    }
    
    return rc;
}
