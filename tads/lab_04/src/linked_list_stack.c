#include "linked_list_stack.h"

int ll_push(ll_stack_t *stack, char *element)
{
    list_t *tmp = malloc(sizeof(list_t));
    if (tmp == NULL)
        return RC_ALLOCATION_FAILED;
    tmp->value = *element;
    tmp->next = stack->sp;
    stack->sp = tmp;
    return RC_OK;
}

int ll_pop(ll_stack_t *stack, list_t **list_node)
{
    if (stack->sp == NULL)
        return RC_STACK_EMPTY;

    *list_node = stack->sp;
    stack->sp = stack->sp->next;
    return RC_OK;
}

void ll_print(ll_stack_t *stack)
{
    if (stack->sp == NULL)
        printf("Стек пуст.\n");

    ll_stack_t stack_tmp = { NULL };
    
    // Перекладываем стек во временный стек и вывод элементов
    size_t i = 0;
    list_t *tmp = NULL;
    // size_t is_fragmentated = 0;
    for ( ; stack->sp != NULL; i++)
    {
        ll_pop(stack, &tmp);
        ll_push(&stack_tmp, &tmp->value);
        // if (tmp->next != NULL && tmp - tmp->next != 2)
        //     printf("Фрагментация:\n"), is_fragmentated += 1;
        printf("pointer: %p -> '%c'.\n", (void *) tmp, tmp->value);
        free(tmp);
    }
    printf("Всего элементов: %zu\nЗанимаемая память: %zu\n", i, sizeof(ll_stack_t) + i*sizeof(list_t));
    // printf("Фрагментация: %zu\n", is_fragmentated);
    // Перекладываем обратно
    for ( ; stack_tmp.sp != NULL; )
    {
        ll_pop(&stack_tmp, &tmp);
        ll_push(stack, &tmp->value);
        free(tmp);
    }
}

void ll_free(ll_stack_t *stack)
{
    list_t *next_p = NULL;
    for ( ; stack->sp != NULL; stack->sp = next_p)
    {
        next_p = stack->sp->next;
        free(stack->sp);
    }
}