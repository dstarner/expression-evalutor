#include <iostream>

#include "token.h"
#include "stack.h"

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

    struct stack *stack;

    stack = init_stack();

    for (int i=0; i < token_arr_size; i++) {
        push(tokens[i], stack);
        //printf("op: %c, val: %d\n", tokens[i].op_value, tokens[i].int_value);
    }

    while (!is_empty(stack)) {
        token tk = pop(stack);
        printf("%d -- %d\n", tk.op_value, tk.int_value);
    }

    return 0;
}