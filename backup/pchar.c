#include "monty.h"

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
		printf("L%u: can't pchar, stack empty\n", line_number);
		return;
	}

	if ((*stack)->n > 127)
	{
		printf("L%u: can't pchar, value out of range\n", line_number);
		return;
	}
	putchar((*stack)->n);
}