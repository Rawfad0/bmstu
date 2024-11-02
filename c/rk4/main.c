#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

#define OK 0
#define IO 1
#define STACK_NOT_EMPTY 2

#define __POSIX_C_SOURCE 200809L
#include <stdio.h>

int check(char *str);

int main(void)
{
	int rc = OK;
	
	char *str = NULL;
	size_t len = 0;
	if ((rc = getline(&str, &len, stdin)) != -1)
	{
		if (str[strlen(str) - 1] == '\n')
			str[strlen(str) - 1] == '\0';
		
		if ((rc = check(str)) == OK)
			printf("YES\n");
		else
			printf("NO\n");
		free(str);
	}
	return 0;
}

int check(char *str)
{
	int rc = OK;
	stack_t stack = init();
	char tmp;
	for (char *ch = str; rc == OK && *ch != '\0'; ch++)
		if (*ch == '(')
			rc = push(stack, *ch);
		else if (*ch == ')')
			rc = pop(stack, &tmp);
	if (rc == OK && pop(stack, &tmp) != OK)
		rc = OK;
	else
		rc = STACK_NOT_EMPTY;
	del(&stack);
	return rc;
}
