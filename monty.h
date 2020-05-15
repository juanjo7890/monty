#ifndef GRANDPARENT_H
#define GRANDPARENT_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* This is for macros */
#define EXIT_ERROR 1
#define EXIT_FAILIURE 1
/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;
/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;
void op_compare(stack_t **st, unsigned int line, char *command,
		instruction_t instruct[]);
/* This is the instruction */
stack_t push(stack_t **stack, unsigned int line_number);
stack_t pall(stack_t **stack, unsigned int line_number);
stack_t pint(stack_t **stack, unsigned int line_number);
void pop(stack_t **stack, unsigned int line_number);
stack_t swap(stack_t **stack, unsigned int line_number);
stack_t mul(stack_t **stack, unsigned int line_number);
void nop(stack_t **stack, unsigned int line_number);
void add(stack_t **stack, unsigned int line_number);
void sub(stack_t **stack, unsigned int line_number);
void pchar(stack_t **stack, unsigned int line_number);

#endif /* GRANDPARENT_H */

