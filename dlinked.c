#include "monty.h"

/**
 * free_dlist - free a double linked list
 * @stack: pointer to the top of the stack
 */
void free_dlist(stack_t *stack)
{
	stack_t *pStack;

	while (stack != NULL)
	{
		pStack = stack;
		stack = stack->next;
		free(pStack);
	}
}
