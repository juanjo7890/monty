#include "monty.h"
/**
 *number_node - Where the command is become to number
 *@token: is the command
 *@line_number: the line number of the command being run
 *
 *Return: 0
 */
int number_node(char *token, unsigned int line_number)
{
	unsigned int i = 0, count = 0;
	char *found;

	found = strtok(token, " \t");
	found = strtok(NULL, " \t");
	if (found == NULL)
	{
		ERROR_MANAGE = -1;
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		return (-1);
	}
	for (i = 0; found[i]; i++)
	{
		if (isdigit(found[i]) == 0 && found[i] != '-')
		{
			ERROR_MANAGE = -1;
			fprintf(stderr, "L%d: usage: push integer\n", line_number);
			return (-1);
		}
	}
	for (i = 0; found[i]; i++)
		if (found[i] == '\t' || found[i] == '\n' || found[i] == ' ')
			count++;
	if (count == strlen(found))
	{
		ERROR_MANAGE = -1;
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		return (-1);
	}
	i = atoi(found);
	return (i);
}
/**
 * excute - where the command is search in the dictionary
 * @st: is the stack
 * @line: is the line of the comand
 * @command: is the command
 * @instruct: is the array whit whole commands
 * @monty_file: it the file how contain
 *
 * Return: if fails throught errors
 */
int excute(stack_t **st, unsigned int line, char *command,
	   instruction_t instruct[], FILE *monty_file)
{
	char *word = NULL, *number = NULL;

	unsigned int i = 0, count = 0, num = 0;

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
				{
					num = number_node(number, line);
					(*st)->n = num;
				}
				if (ERROR_MANAGE == -1)
				{
					free(number), free(command), free_dlist(*st);
					fclose(monty_file), exit(EXIT_FAILURE);
				}
			}
			free(number);
			return (0);
		}
	}
	free(number);
	fprintf(stderr, "L%u: Unknown instruction %s\n", line, word);
	return (1);
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
