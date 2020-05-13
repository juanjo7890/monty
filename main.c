#include "monty.h"

extern line = 0;
int main(int argc, char *argv[])
{
	char buffer[1024];
	FILE *monty_file;
	instruction_t instruct[] = {{"push", push}, {"mul", NULL},
				    {"pall", pall}, {"pop", pop}, {"pint", pint}, {"swap", swap},
				    {"add", pint}, {"sub", NULL}, {"div", NULL}, {"NULL", NULL}};
	stack_t *st = NULL;

	if (argc != 2)
	{
		printf("USAGE: monty file\n");
		exit(EXIT_ERROR);
	}
	monty_file = fopen(argv[1], "r")
	if (monty_file == NULL)
	{
		printf("ERROR: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILIURE);
	}
/* Indicate the end of the file give 0 if didn't find the end of the file */
	while (!feof(monty_file))
	{
/* the 1024 is the number the file is goint to read */
		if (fgets(buffer, 1024, monty_file) != NULL)
			op_compare(&st, line, buffer, instruct);
	}
	fclose(monty_file);
	return (0);
}
void op_compare(stack_t **st, unsigned int line, char *command,
		instruction_t instruct[])
{
	int i = 0;
	char *opcode = NULL;
	stack_t *new_node = NULL;

	opcode = strtok(command, "\t ");

	while (instruct[i].opcode != NULL)
	{
		if (strcmp(opcode, instruct[i].opcode) == 0)
		{
			new_node = opcodes[i].f(st, line);
			if (strcmp(instruct[i].opcode, "push"))
				new_node->n = strtok(opcode, NULL);
			return;
		}
		i++;
	}
	printf("L%u: Unknown instruction %s\n", line, opcode);
	exit(EXIT_FAILURE);
}
