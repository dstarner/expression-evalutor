#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "stack.h"


#ifndef bool
#define bool int
#define true 1
#define false 0
#endif

bool hasPrecedence(token op1, token op2){
	if(op2.op_value == '(' || op2.op_value == ')')
		return false;
	if((op1.op_value=='*'||op1.op_value=='/')&&(op2.op_value=='+'||op2.op_value=='-'))
		return false;
	else
		return true;
}

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

char* toPostfix(token* tokens,int size){
	struct stack* output = init_stack();
	struct stack* st = init_stack();
	for(int i=0; i<size; ++i){
		token t = tokens[i];
		if(t.is_operand){
			push(t,output);
		}
		else if(t.is_operator){
			if(t.op_value=='('){
				push(t,st);
			}
			if(t.op_value==')'){
				char c=' ';
				while((st->top).op_value!='('){
					push(pop(st),output);
					c = st->top.op_value;	
				}
				if(is_empty(st) && c!='('){
					return "error";
				}
				while(!is_empty(st)){
					if(st->top.op_value==')' || '(') return "error";
					push(pop(st),output); 
				}
				
			}
			else{
			while(!is_empty(st)){
				token top = st->top;
				if(hasPrecedence(top,t)){
					push(pop(st),output);
					push(t,st);
				}
				else{
					push(t,st);
				}
				
			}
			}
		}
		
	}

	char* result=(char*)malloc(sizeof(1));
	while(!is_empty(output)){
		result=(char*)malloc(sizeof(result+1));
		result=result+get_val(pop_bottom(output));
	}
	return result;
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
        } else if (current.is_operator && current.op_value == 40) {
            push(current, op_stack);

        // ')'
        } else if (current.is_operator && current.op_value == 41) {
            while (peek(op_stack).op_value != 40) {
                token num2 = pop(value_stack);
                token num1 = pop(value_stack);
                int val = ops(num1, pop(op_stack), num2);
                token temp = {.op_value=0, .int_value=val, .is_operand=1, .is_operator=0};
                push(temp, value_stack);
            }
            if (is_empty(op_stack)) {
                return 1;
            }
            pop(op_stack);

        // Token is operator
        } else if (current.is_operator) {

            // While top of 'op_stack' has precedence
            while (!is_empty(op_stack) && hasPrecedence(current, peek(op_stack))) {
                token num2 = pop(value_stack);
                token num1 = pop(value_stack);
                int val = ops(num1, pop(op_stack), num2);
                token temp = {.op_value=0, .int_value=val, .is_operand=1, .is_operator=0};
                push(temp, value_stack);
            }

            push(current, op_stack);

        }
    }

    while (!is_empty(op_stack)) {
        token num2 = pop(value_stack);
        token num1 = pop(value_stack);
        int val = ops(num1, pop(op_stack), num2);
        token temp = {.op_value=0, .int_value=val, .is_operand=1, .is_operator=0};
        push(temp, value_stack);
    }

    printf("\n%d\n", pop(value_stack).int_value);

    // DESTROYER OF ALL THINGS

    return 0;
}
