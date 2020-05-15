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
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	monty_file = fopen(argv[1], "r");
	if (monty_file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (getline(&buffer, &size, monty_file) > 0)
	{
		if (excute(&stack, lines, buffer, instruct, monty_file) == 1)
		{
			free(buffer);
			free_dlist(stack);
			fclose(monty_file);
			exit(EXIT_FAILURE);
		}
		lines++;
	}
	free(buffer);
	free_dlist(stack);
	fclose(monty_file);
	return (0);
}
