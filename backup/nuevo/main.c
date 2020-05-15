#include "monty.h"
#include <ctype.h>

int ERROR_MANAGE = 0;

/**
 * main - is the main functioj
 * @argc: int of how many arguments
 * @argv: is the arguments passed into the file
 *
 * Return: if fails throught errors
 */
int main(int argc, char *argv[])
{
	size_t size = 0;
	FILE *monty_file;
	char *buffer = NULL;
	int lines = 1;
	stack_t *stack = NULL;
	instruction_t instruct[] = {{"push", push}, {"pall", pall},
		{"nop", nop}, {"pop", pop}, {"pint", pint}, {"swap", NULL},
		{"add", add}, {"sub", sub}, {"div", NULL}, {NULL, NULL}};

	if (argc != 2)
	{
		printf("USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	monty_file = fopen(argv[1], "r");
	if (monty_file == NULL)
	{
		printf("ERROR: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (getline(&buffer, &size, monty_file) > 0)
	{
		if (excute(&stack, lines, buffer, instruct, monty_file) < 0)
		{
			free(buffer);
			free_dlist(stack);
			fclose(monty_file);
			exit(EXIT_FAILURE);
		}
		lines++;
	}

	free_dlist(stack);
	free(buffer);
	fclose(monty_file);
	return (0);
}

/**
 * main - is the main functioj
 * @st: is the stack
 * @line: is the line of the comand
 *
 * Return: if fails throught errors
 */
int excute(stack_t **st, unsigned int line, char *command,
	   instruction_t instruct[], FILE *monty_file)
{
	char *word = NULL, *number = NULL;
	int i = 0, count = 0, num = 0;

	if (command[i] == '\n' || command[i] == '#')
		return (0);
	for (i = 0; command[i]; i++)
		if (command[i] == '\t' || command[i] == '\n' || command[i] == ' ')
			count++;
	if (count == strlen(command))
		return (0);
	if (command[strlen(command) - 1] == '\n')
		command[strlen(command) - 1] = '\0';

	number = strdup(command), word = strtok(command, " \t");
	for (i = 0; instruct[i].opcode != NULL; i++)
	{
		if (strcmp(instruct[i].opcode, word) == 0)
		{
			if (instruct[i].f != NULL)
			{
				instruct[i].f(st, line);
				if (strcmp(instruct[i].opcode, "push") == 0)
					num = number_node(number, line);

				if (ERROR_MANAGE == -1)
				{
					free(number), free(command), free_dlist(*st);
					fclose(monty_file), exit(EXIT_FAILURE);
				}
				(*st)->n = num;
			}
			free(number);
			return (0);
		}
	}
	free_dlist(*st), free(number);
	printf("L%u: Unknown instruction %s\n", line, word);
	return (-1);
}

int number_node(char *token, unsigned int line_number)
{
	int i;
	char *found, *num;

    	found = strsep(&token,"\t ");
	found = strsep(&token,"\t ");

	for (i = 0; found[i]; i++)
	{
		if (isdigit(found[i]) == 0)
		{
			ERROR_MANAGE = -1;
			printf("L%d: usage: push integer\n", line_number);
			return (-1);
		}
	}
	i = atoi(found);
	return (i);
}

void push(stack_t **stack, unsigned int line_number)
{
	stack_t *pStack;

	(void) line_number;
	pStack = malloc(sizeof(stack_t));
	if (pStack == NULL)
	{
		printf("Error: malloc failed");
		ERROR_MANAGE = -1;
		return;
	}
	pStack->next = NULL;
	pStack->prev = NULL;

	if (*stack == NULL)
	{
		*stack = pStack;
		return;
	}

	pStack->next = *stack;
	(*stack)->prev = pStack;
	*stack = pStack;
}

void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *pStack = *stack;

	(void) line_number;
	while (pStack != NULL)
	{
		printf("%d\n", pStack->n);
		pStack = pStack->next;
	}
}

void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		ERROR_MANAGE = -1;
		printf("L%d: can't pint, stack empty", line_number);
		return;
	}

	printf("%d\n", (*stack)->n);
}

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

/**
 *nop - does nothing
 *@stack: pointer to the top of the stack
 *@line_number: the line number of the command being run
 *Return: 0
 */

void nop(stack_t **stack, unsigned int line_number)
{
	(void) line_number;
	(void) stack;
}

/**
 * pop - Will delete in the value on top of the stack
 * @stack: pointer to top of the stack
 * @line_number: the line that will run
 */

void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = NULL;

	if (*stack == NULL)
	{
		printf("L%u: can't pop an empty stack\n", line_number);
		ERROR_MANAGE = -1;
		return;
	}
	tmp = *stack;
	*stack = tmp->next;
	if (tmp->next)
	{
		tmp->next->prev = NULL;
	}
	free(tmp);
}

/**
 *sub - Will subtract the values at the top of the stack
 *@stack: pointer to the top of the stack
 *@line_number: the line number of the command being run
 *Return: 0
 */
void sub(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack, *iter = *stack;
	int subb = 0, node = 0;

	while (iter != NULL)
	{
		node++;
		iter = iter->next;
	}
	if (node < 2)
	{
		printf("L%u: can't sub, stack too short\n", line_number);
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
		exit(EXIT_FAILURE);
	}
	adds = (*stack)->n + (*stack)->next->n;
	(*stack)->next->n = adds;
	(*stack)->prev = NULL;
}
