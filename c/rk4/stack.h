#ifndef STACK_H__
#define STACK_H__

#define RC_OK 0
#define RC_MEM 11
#define RC_EMPTY_STACK 12

typedef struct stack *stack_t;

stack_t init(void);

int push(stack_t stack, char ch);

int pop(stack_t stack, char *ch);

void del(stack_t *stack);

#endif
