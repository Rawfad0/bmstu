#include "da_stack.h"

int da_push(da_stack_t *stack, char element)
{
    // printf("%ld %ld\n", stack->sp - stack->array, (long int) stack->alloc_n);
    if (stack->sp - stack->array == (long int) stack->alloc_n)
    {
        char *tmp = realloc(stack->array, stack->alloc_n + 1);
        if (tmp == NULL)
            return RC_ALLOCATION_FAILED;
        else
            stack->sp += tmp - stack->array, stack->array = tmp, stack->alloc_n++;
    }
    *stack->sp = element;
    stack->sp++;
    return RC_OK;
}

int da_pop(da_stack_t *stack, char *element)
{
    if (stack->sp == stack->array)
        return RC_STACK_EMPTY;
    stack->sp--;
    *element = *stack->sp;
    return RC_OK;
}

void da_free(da_stack_t *stack)
{
    free(stack->array);
    stack->alloc_n = 0;
    stack->sp = NULL;
}

void da_print(da_stack_t *stack)
{
    if (stack->sp == stack->array)
        printf("Стек пуст.\n");

    da_stack_t stack_tmp =  { NULL, 0, NULL };
    
    // Перекладываем стек во временный стек с выводом
    size_t i = 1;
    char tmp = '\0';
    for ( ; stack->sp > stack->array; i++)
    {
        da_pop(stack, &tmp);
        da_push(&stack_tmp, tmp);
        printf("%*zu: %c\n", 3, i, *stack->sp);
    }
    printf("Всего элементов: %zu\nЗанимаемая память: %zu\n", i - 1, sizeof(da_stack_t) + stack->alloc_n);
    // Перекладываем обратно
    for ( ; stack_tmp.sp > stack_tmp.array; )
    {
        da_pop(&stack_tmp, &tmp);
        da_push(stack, tmp);
    }
    da_free(&stack_tmp);
}
