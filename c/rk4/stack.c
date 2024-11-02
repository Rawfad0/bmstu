#include "stack.h"

#include <stdlib.h>
#include <stddef.h>

typedef struct list list_t;
struct list
{
	char ch;
	list_t *next;
};

struct stack
{
	list_t *head;
};

stack_t init(void)
{
	stack_t tmp = malloc(sizeof(struct stack));
	if (tmp != NULL)
		tmp->head = NULL;
	return tmp;
}

int push(stack_t stack, char ch)
{
	int rc = RC_OK;
	list_t *tmp_node = malloc(sizeof(list_t));
	if (tmp_node == NULL)
		rc = RC_MEM;
	else
	{
		tmp_node->ch = ch;
		tmp_node->next = stack->head;
		stack->head = tmp_node;
	}
	return rc;
}

int pop(stack_t stack, char *ch)
{
	if (stack->head == NULL)
		return RC_EMPTY_STACK;
	*ch = stack->head->ch;
	list_t *tmp = stack->head;
	stack->head = stack->head->next;
	free(tmp);
	return RC_OK;
}

void del(stack_t *stack)
{
	char tmp;
	while ((*stack)->head != NULL)
		pop(*stack, &tmp);
	free(*stack);
	*stack = NULL;
}
