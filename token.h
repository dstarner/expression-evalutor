//
// Created by Dan Starner on 2/8/17.
//

#include <ctype.h>

#ifndef INC_306_CALCULATOR_TOKEN_H
#define INC_306_CALCULATOR_TOKEN_H

typedef struct {

    // Values of token
    char op_value;
    int int_value;

    // Type of token
    int is_operand;
    int is_operator;
} token;

int get_length(token* tokens) {
    return sizeof(tokens) / sizeof(token);
}



bool is_rn(char c) {

    return c == 'I' || c == 'V' || c == 'X' || c == 'M' || c == 'D' || c == 'L';

}

/**
 * This function takes in a valid roman numeral in
 * all CAPS and returns the integer value.
 * @param roman_numeral
 * @return
 */
int roman_to_int(char* roman_numeral) {


    // THIS IS DUMMY CODE TILL IT GETS FILLED IN
    printf("%s", roman_numeral);
    return 0;
}


/**
 * This function determines the number of tokens that will be needed for a string
 * to correctly be parsed.
 * @param string
 * @return int
 */
int determine_token_size(char* string) {
    int needed = 0;

    int i = 0;
    while(string[i]) {
        string[i] = toupper(string[i]);
        i++;
    }

    i = 0;
    // Iterate over every string
    while (string[i] != '\0') {
        // Check what string[i] is.

        // Space, skip
        if (string[i] == 32 || string[i] == 10) {
            i++;
        }

        // If number
        else if (48 <= string[i] && string[i] <= 57) {
            int num = 0;
            // Keep incrementing i until not number
            while (48 <= string[i] && string[i] <= 57) {
                num *= 10;
                num += (string[i] - '0');
                i++;
            }
            needed++;
        }

        // Operator
        else if (string[i] == 42 || string[i] == 43 || string[i] == 45 || string[i] == 47) {
            needed++;
            i++;
        }

        // If roman numeral (i/I, x/X, v/V)
        else if (is_rn(string[i])) {

            // Keep incrementing until not roman numeral
            while (is_rn(string[i])) {
                i++;
            }

            int value = roman_to_int("VII");

            needed++;
        }

        else {
            return -1;
        }
    }

    return needed;
}


void build_tokens(token* tokens, int size, char* string) {

    int cur_token = 0;

    int i = 0;
    while(string[i]) {
        string[i] = toupper(string[i]);
        i++;
    }

    i = 0;
    // Iterate over every string
    while (string[i] != '\0') {
        // Check what string[i] is.

        // Space, skip
        if (string[i] == 32 || string[i] == 10) {
            i++;
        }

            // If number
        else if (48 <= string[i] && string[i] <= 57) {
            int num = 0;
            // Keep incrementing i until not number
            while (48 <= string[i] && string[i] <= 57) {
                num *= 10;
                num += (string[i] - '0');
                i++;
            }
            token tok = {.int_value=num, .op_value=0, .is_operand=1, .is_operator=0};
            tokens[cur_token] = tok;
            cur_token++;
        }

            // Operator
        else if (string[i] == 42 || string[i] == 43 || string[i] == 45 || string[i] == 47) {
            token tok = {.int_value=0, .op_value=string[i], .is_operand=0, .is_operator=1};
            tokens[cur_token] = tok;
            cur_token++;
            i++;
        }

            // If roman numeral (i/I, x/X, v/V)
        else if (is_rn(string[i])) {

            // Keep incrementing until not roman numeral
            while (is_rn(string[i])) {
                i++;
            }
        }
    }


}


#endif //INC_306_CALCULATOR_TOKEN_H

