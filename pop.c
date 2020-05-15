#include "monty.h"
/**
 * pop - Will delete in the value on top of the stack
 * @stack: pointer to top of the stack
 * @line_number: the line that will run
 */

void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = NULL;

	if (stack == NULL || *stack == NULL)
	{
		printf("L%u: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILIURE);
	}
	tmp = *stack;
	*stack = tmp->next;
	if (tmp->next)
	{
		tmp->next->prev = NULL;
	}
	free(tmp);
}

