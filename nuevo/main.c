#include "monty.h"
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
	instruction_t instruct[] = {{"push", NULL}, {"pall", NULL},
		{"nop", NULL}, {"pop", NULL}, {"pint", NULL}, {"swap", NULL},
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
				exit (EXIT_FAILURE);
			}

		}
	}

	fclose(monty_file);
	return(0);
}

int excute(stack_t **st, unsigned int line, char *command,
	   instruction_t instruct[], FILE *monty_file)
{
	char *word, *number;
	int i, num = 0;

	command[strlen(command) - 1] = '\0';
	word = strtok(command, " ");

	for (i = 0; instruct[i].opcode != NULL; i++)
	{
	 	if (strcmp(instruct[i].opcode, word) == 0)
	 	{
	 		if (strcmp(instruct[i].opcode, "push") == 0)
	 		{
				/* en construccion */
				instruct[i].f(st, line);
	 			if ((word = strtok(NULL, word)) != NULL)
				{
					num = atoi(word);
	 				if (num != 0)
	 					(*st)->n = num;
					else
					{
						printf("L%d: usage: push integer", line);
						fclose(monty_file);
						exit (EXIT_FAILURE);
					}
					return (1);
				}
			}
			else
				instruct[i].f(st, line);

	 		return (1);
	 	}
	}
	printf("L%u: Unknown instruction %s\n", lines, word);
	return (-1);
}

void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		ERROR_MANAGE = -1;
		printf("")
		return (ERROR_MANAGE);
	}

	while (pStack)
	{
		printf("%d\n", stack->n);
		pStack = pStack->next;
	}
}


void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *pStack = *stack;

	while (pStack)
	{
		printf("%d\n", stack->n);
		pStack = pStack->next;
	}
}
