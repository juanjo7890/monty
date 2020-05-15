#include "monty.h"
/**
 *sub - Will subtract the values at the top of the stack
 *@stack: pointer to the top of the stack
 *@line_number: the line number of the command being run
 *Return: 0
 */
void sub(stack_t **stack, unsigned int line_number)
{
	stack_t *iter = *stack;
	int subb = 0, node = 0;

	while (iter != NULL)
	{
		node++;
		iter = iter->next;
	}
	if (node < 2)
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
		ERROR_MANAGE = -1;
		return;
	}
	subb = (*stack)->next->n - (*stack)->n;
	(*stack)->next->n = subb;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
}
/**
 *add - Will add the two values at the top of the stack
 *@stack: pointer to the top of the stack
 *@line_number: the line number of the command being run
 *Return: 0
 */
void add(stack_t **stack, unsigned int line_number)
{
	int adds = 0, node = 0;
	stack_t *iter = *stack;

	while (iter != NULL)
	{
		node++;
		iter = iter->next;
	}
	if (node < 2)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	adds = (*stack)->n + (*stack)->next->n;
	(*stack)->next->n = adds;
	(*stack)->prev = NULL;
}
