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
	char buffer[1024];
	FILE *monty_file;
	stack_t *stack;
	int lines = 1;
	instruction_t instruct[] = {{"push", push}, {"pall", pall},
		{"nop", NULL}, {"pop", NULL}, {"pint", pint}, {"swap", NULL},
		{"add", NULL}, {"sub", NULL}, {"div", NULL}, {"#", NULL},
		{NULL, NULL}};

	if (argc != 2)
	{
		printf("USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	if ((monty_file = fopen(argv[1], "r")) == NULL)
	{
		printf("ERROR: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
/* Indicate the end of the file give 0 if didn't find the end of the file */
	for (; !feof(monty_file); lines++)
	{
/* the 1024 is the number the file is goint to read */
		if (fgets(buffer, 1024, monty_file) != NULL)
		{
			if(excute(&stack, lines, buffer, instruct, monty_file) < 0)
			{
				fclose(monty_file);
                    free_dlist(stack);
				exit (EXIT_FAILURE);
			}
		}
	}

     free_dlist(stack);
	fclose(monty_file);
	return(0);
}

int excute(stack_t **st, unsigned int line, char *command,
	   instruction_t instruct[], FILE *monty_file)
{
	char *word, *number;
	int i, count = 0;

	for (i = 0; command[i]; i++)
          if (command[i] == '\t' || command[i] == '\n' || command[i] == ' ')
               count++;
     if (count == (strlen(command) - 1))
          return (0);

	command[strlen(command) - 1] = '\0';
	number = strdup(command);
     word = strtok(command, " ");


	for (i = 0; instruct[i].opcode != NULL; i++)
	{
	 	if (strcmp(instruct[i].opcode, word) == 0)
	 	{
			/* hacer funcion para modular*/
			instruct[i].f(st, line);
          	if (strcmp(instruct[i].opcode, "push") == 0)
	 		{
                    number_node(number, st, line);
                    if (ERROR_MANAGE == -1)
                    {
                         free_dlist(*st);
                         fclose(monty_file);
                         exit (EXIT_FAILURE);
                    }
				return (1);
			}
	 		return (1);
	 	}
	}

     free(number);
	printf("L%u: Unknown instruction %s\n", line, word);
	return (-1);
}

int number_node(char *token, stack_t **stack, unsigned int line_number)
{
	int i;

     if (strlen(token) <= 4)
     {
          ERROR_MANAGE = -1;
		printf("L%d: usage: push integer\n", line_number);
		return (-1);
     }

	for (i = 5; token[i]; i++)
	{
          if ((isdigit(token[i])) == 0)
		{
               ERROR_MANAGE = -1;
		     printf("L%d: usage: push integer\n", line_number);
		     return (-1);
		}
	}
	token = strtok(token, " ");
     token = strtok(NULL, token);

     (*stack)->n = atoi(token);

     /*free(token);*/
	return (0);
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

void push(stack_t **stack, unsigned int line_number)
{
	stack_t *pStack;

     (void ) line_number;
	pStack = malloc(sizeof(stack_t));
	if (pStack == NULL)
	{
		printf("Error: malloc failed");
		return;
	}

	pStack->next = NULL;
	pStack->prev = NULL;

	if (*stack == NULL)
	{
		*stack = pStack;
		return;
	}

	(*stack)->prev = pStack;
	pStack->next = *stack;
	*stack = pStack;
}

void pint(stack_t **stack, unsigned int line_number)
{
	stack_t *pStack;

	if (*stack == NULL)
	{
		ERROR_MANAGE = -1;
		printf("L%d: can't pint, stack empty", line_number);
		return;
	}

	pStack = *stack;
	while (pStack != NULL)
	{
		printf("%d\n", pStack->n);
		pStack = pStack->next;
	}
}

void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *pStack = *stack;

     (void ) line_number;
	while (pStack != NULL)
	{
		printf("%d\n", pStack->n);
		pStack = pStack->next;
	}
}
