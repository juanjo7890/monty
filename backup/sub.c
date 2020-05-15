#include "monty.h"

/**
 *sub - Will subtract the values at the top of the stack
 *@stack: pointer to the top of the stack
 *@line_number: the line number of the command being run
 *Return: 0
 */
void sub(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;
	int subb;
	int node = 0;
	stack_t *iter = *stack;

	while (iter != NULL)
	{
		node++;
		iter = iter->next;
	}
	if (node < 2)
	{
		printf("L%u: can't sub, stack too short\n", line_number);
		exit(EXIT_FAILIURE);
	}
	subb = (*stack)->next->n - (*stack)->n;
	(*stack)->next->n = diff;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	free(tmp);
}
