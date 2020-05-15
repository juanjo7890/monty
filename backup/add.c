#include "monty.h"

/**
 *add - Will add the two values at the top of the stack
 *@stack: pointer to the top of the stack
 *@line_number: the line number of the command being run
 *Return: 0
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;
	int adds;
	int node = 0;
	stack_t *iter = *stack;

	while (iter != NULL)
	{
		node++;
		iter = iter->next;
	}
	if (node < 2)
	{
		printf("L%u: can't add, stack too short\n", line_number);
		exit(EXIT_FAILIURE);
	}
	adds = (*stack)->n + (*stack)->next->n;
	(*stack)->next->n = adds;
	(*stack)->prev = NULL;
	free(tmp);
}
