#include "monty.h"
/**
 * pall -  prints all the values on the stack, starting from
 * the top of the stack.
 * @stack: pointer to the top of the stack
 * @line_number: the line number of the command being run
 *
 * Return: 0
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *pStack = *stack;
	(void) line_number;

	while (pStack != NULL)
	{
		fprintf(stderr, "%d\n", pStack->n);
		pStack = pStack->next;
	}
}
/**
 * pint - prints the value at the top of the stack, followed by a new line.
 * @stack: pointer to the top of the stack
 * @line_number: the line number of the command being run
 *
 * Return: 0
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)

	{
		ERROR_MANAGE = -1;
		printf("L%d: can't pint, stack empty\n", line_number);
		return;
	}
	printf("%d\n", (*stack)->n);
}
/**
 *pchar - Will print the char located in top of the stack
 *@stack: the pointer to the top of the stack
 *@line_number: the line number in the Monty file
 *Return: 0
 */
void pchar(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)

	{
		ERROR_MANAGE = -1;
		fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
		return;
	}
	if ((*stack)->n > 127)
	{
		fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
		return;
	}
	putchar((*stack)->n);
}
