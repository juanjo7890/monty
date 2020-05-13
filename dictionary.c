#include "monty.h"
/**
 *op_compare - Will compare the opcodes and run associated functions
 *@st: is a pointer to the top of the stack
 *@line: line number of command
 *@opcode: the opcode for Monty interpretor
 *Return: 0
 */

void op_compare(stack_t **st, unsigned int line, char *opcode)
{
	int i = 0;
	instruction_t opcodes[] = {
		{"push", push}, {"pall", pall}, {"pop", pop}
		{"pint", pint}, {"swap", swap}, {"add", pint}
		{"sub", NULL}, {"div", NULL}, {"mul", NULL}
		{"NULL", NULL}
	};
	while (opcodes[i].opcode != NULL)
	{
		if (_strcmp(opcode, opcodes[i].opcode) == 0)
		{
			opcodes[i].f(st, line);
			return;
		}
		i++;
	}
	printf("L%u: Unknown instruction %s\n", line, opcode);
	exit(EXIT_FAILURE);
}
