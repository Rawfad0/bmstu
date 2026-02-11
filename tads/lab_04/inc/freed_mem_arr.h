#ifndef __FREED_MEM_ARR__H__
#define __FREED_MEM_ARR__H__

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "consts.h"
#include "linked_list_stack.h"

typedef struct
{
    list_t **da;
    size_t len;
} fma_t;

int fma_add(fma_t *fma, list_t *p);

void fma_print(fma_t *fma);

void fma_free(fma_t *fma);

#endif
