#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "stack.h"


#ifndef bool
#define bool int
#define true 1
#define false 0
#endif


int ops(token num1, token op, token num2){
	int total=0;
	switch(op.op_value){
		case '+': total=num1.int_value+num2.int_value;
		break;
		case '-': total=num1.int_value-num2.int_value;
		break;
		case '*': total=num1.int_value*num2.int_value;
                break;
		case '/': total=num1.int_value/num2.int_value;
                break;

		default:
		break;
	
	}
	return total;
	
}

int main(int argc, char *argv[]) {

    // Ensure that there is another argument
    if (argc != 2) {
        fprintf(stderr, "There must be %d arguments!", 2);
        return 1;
    }

    FILE *input_file;

    input_file = fopen(argv[1], "r");

    if (!input_file) {
        printf("File not found.");
        return -1;
    }

    char expression[1024];

    if (feof (input_file)) {
        printf("Invalid file.");
        return -1;
    }

    fgets(expression, sizeof (expression), input_file);

    // Token size needed
    int token_arr_size = 0;
    token_arr_size = determine_token_size(expression);

    if (token_arr_size < 0) {
        printf("Invalid token.");
        return -1;
    }

    token tokens[token_arr_size];

    build_tokens(tokens, token_arr_size, expression);

    struct stack * value_stack;
    struct stack * op_stack;

    value_stack = init_stack();
    op_stack = init_stack();

    // Read all the tokens in
    for (int i=0; i < token_arr_size; i++) {
        token current = tokens[i];

        // Value
        if (current.is_operand) {
            // Push to value stack
            push(current, value_stack);

        // '('
        } else if (current.op_value == 40) {
            push(current, op_stack);
        // ')'
        } else if (current.op_value == 41) {
            while (peek(op_stack).op_value != 40) {
                // APPLYOPS
            }
            pop(op_stack);
        // Token is operator
        } else if (current.is_operator) {

            // While top of 'op_stack' has precedence

        }
    }

    while (!is_empty(op_stack)) {

    }

    // DESTROYER OF ALL THINGS

    return 0;
}
