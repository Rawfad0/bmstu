#include "static_array_stack.h"

int sa_push(sa_stack_t *stack, char element)
{
    if (stack->sp == stack->pe)
        return RC_STACK_FULL;
    *stack->sp = element;
    stack->sp++;
    return RC_OK;
}

int sa_pop(sa_stack_t *stack, char *element)
{
    if (stack->sp == stack->array)
        return RC_STACK_EMPTY;
    stack->sp--;
    *element = *stack->sp;
    return RC_OK;
}

void sa_print(sa_stack_t *stack)
{
    if (stack->sp == stack->array)
        printf("Стек пуст.\n"); 

    sa_stack_t stack_tmp =  { { '\0' }, NULL, NULL };
    stack_tmp.pe = stack_tmp.array + MAX_ARR_LEN;
    stack_tmp.sp = stack_tmp.array;
    
    // Перекладываем стек во временный стек и вывод элементов
    size_t i = 1;
    char tmp = '\0';
    for ( ; stack->sp > stack->array; i++)
    {
        sa_pop(stack, &tmp);
        sa_push(&stack_tmp, tmp);
        printf("%*zu: %c\n", 3, i, *stack->sp);
    }
    printf("Всего элементов: %zu\nЗанимаемая память: %zu\n", i - 1, sizeof(sa_stack_t));
    // Перекладываем обратно
    for ( ; stack_tmp.sp > stack_tmp.array; )
    {
        sa_pop(&stack_tmp, &tmp);
        sa_push(stack, tmp);
    }
}
