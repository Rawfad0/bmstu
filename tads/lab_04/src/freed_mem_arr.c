#include "freed_mem_arr.h"

int fma_add(fma_t *fma, list_t *p)
{
    int rc = RC_OK;
    // printf("new size:%zu; val:'%c'; p:%p; p_da:%p   ", (fma->len + 1) * sizeof(char), p->value, (void *) p, (void *) fma->da);
    void *tmp = realloc(fma->da, (fma->len + 1) * sizeof(list_t));
    
    if (tmp == NULL)
        printf("ALLOC ERROR"), rc = RC_ALLOCATION_FAILED;
    else
    {
        fma->da = tmp;
        fma->da[fma->len] = p;
        fma->len++;
    }
    return rc;
}

void fma_print(fma_t *fma)
{
    if (fma->len == 0)
        printf(".\n");
    for (size_t i = 0; i < fma->len; i++)
        printf("%p\n", (void *) fma->da[i]);
}

void fma_free(fma_t *fma)
{
    free(fma->da);
}
