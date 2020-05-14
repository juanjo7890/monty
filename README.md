# monty: Our custom interpreter for Monty ByteCodes files.

Monty 0.98 is a scripting language that is first compiled into Monty byte codes
(just like Python). It relies on a unique stack, that has specific instructions to manipulate it. 
The Goal of this project is to create an interpreter for Monty ByteCodes files.

## Requirements
  * All files compiled on Ubuntu 14.04 LTS
  * Allow to use max one global variable
  * Usage: `monty file`
    * `file` is the path to the file containing Monty byte code
  * If the user does not give any file or more than one argument to your program, print the error message USAGE: monty file, followed by a new line, and exit with the status EXIT_FAILURE
  * If, for any reason, it’s not possible to open the file, print the error message Error: Can't open file <file>, followed by a new line, and exit with the status EXIT_FAILURE
    * where <file> is the name of the file
  * If the file contains an invalid instruction, print the error message L<line_number>: unknown instruction <opcode>, followed by a new line, and exit with the status EXIT_FAILURE
    * where is the line number where the instruction appears.
    * Line numbers always start at 1
  * The monty program runs the bytecodes line by line and stop if either:
    * it executed properly every line of the file
    * it finds an error in the file
    * an error occured
  * If you can’t malloc anymore, print the error message Error: malloc failed, followed by a new line, and exit with status EXIT_FAILURE.
  * You have to use malloc and free and are not allowed to use any other function from man malloc (realloc, calloc, …)

## Commands coded in the interpretor
   * Push: Pushes an element into the stack.
   * Pall: Prints the values of the stack, starting from the top of the stack.
   * Pint: Prints the value at the top of the stack.
   * Pop: Removes the top element of the stack
   * Swap: Swaps the two elements that are on top of the stack.
   * Add: Adds the two elements in the top of the stack.
   * Nop: The code does nothing.
   * Sub: Substracts the top element of the stack from the second top element.

## Authors & Contact Information

* Andres Reyes - email: 1565@holbertonschool.com - GitHub: https://github.com/andresvanegas19
* Juan José Villegas - email: 1561@holbertonschool.com - GitHub: https://github.com/juanjo7890
