//
// Created by Dan Starner on 2/8/17.
//

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef bool
#define bool int
#define true 1
#define false 0
#endif

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

int get_length(token *tokens) {
    return sizeof(tokens) / sizeof(token);
}


void print_token(token tok) {
    if (tok.is_operator) {
        printf("\nOp: %c", tok.op_value);
    } else {
        printf("\nInt: %d", tok.int_value);
    }
}


bool is_rn(char c) {

    return c == 'I' || c == 'V' || c == 'X' || c == 'M' || c == 'D' || c == 'L' || c == 'C';

}

/**
 * This function takes in a valid roman numeral in
 * all CAPS and returns the integer value.
 * @param roman_numeral
 * @return
 */
int roman_to_int(char *roman_numeral) {
    int converted_int = 0, currentNum = 0, lastNum = 0;
    for (unsigned int i = 0; i < strlen(roman_numeral); ++i) {
        if (roman_numeral[i] == 73) currentNum = 1;
        else if (roman_numeral[i] == 86) currentNum = 5;
        else if (roman_numeral[i] == 88) currentNum = 10;
        else if (roman_numeral[i] == 76) currentNum = 50;
        else if (roman_numeral[i] == 67) currentNum = 100;
        else if (roman_numeral[i] == 68) currentNum = 500;
        else if (roman_numeral[i] == 77) currentNum = 1000;
        //check if next number is higher (therefore subtracting current number from total)
        if ((i > 0) && (lastNum < currentNum)) currentNum -= (lastNum * 2);
        converted_int += currentNum;
        lastNum = currentNum;
        //still need to implement weird exceptions or flat out errors (eg iiii)
    }
    return converted_int;
}


/**
 * This function determines the number of tokens that will be needed for a string
 * to correctly be parsed.
 * @param string
 * @return int
 */
int determine_token_size(char *string) {
    int needed = 0;

    int i = 0;
    while (string[i]) {
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
        else if ((48 <= string[i] && string[i] <= 57) || (string[i] == 45 && (48 <= string[i+1] && string[i+1] <= 57))) {
            // If negative
            bool neg = string[i] == 45;

            // Increment to number
            if (neg) {i++;}

            int num = 0;
            // Keep incrementing i until not number
            while (48 <= string[i] && string[i] <= 57) {
                num *= 10;
                num += (string[i] - '0');
                i++;
            }
            needed++;

        } else if (string[i] == 40 || string[i] == 41) {
            needed++;
            i++;

            // If roman numeral (i/I, x/X, v/V)
        } else if (is_rn(string[i]) || (string[i] == 45 && is_rn(string[i+1]))) {

            // If negative
            bool neg = string[i] == 45;

            // Increment to number
            if (neg) {i++;}

            // Keep incrementing until not roman numeral
            while (is_rn(string[i])) {
                i++;
            }

            needed++;

            // Operator
        } else if (string[i] == 42 || string[i] == 43 || string[i] == 45 || string[i] == 47) {
            needed++;
            i++;
        } else {
            return -1;
        }
    }

    return needed;
}


void build_tokens(token *tokens, int size, char *string) {

    int cur_token = 0;

    int i = 0;
    while (string[i]) {
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
        else if ((48 <= string[i] && string[i] <= 57) || (string[i] == 45 && (48 <= string[i+1] && string[i+1] <= 57))) {
            // If negative
            bool neg = string[i] == 45;

            // Increment to number
            if (neg) {i++;}

            int num = 0;
            // Keep incrementing i until not number
            while (48 <= string[i] && string[i] <= 57) {
                num *= 10;
                num += (string[i] - '0');
                i++;
            }

            if (neg) {num = -1 * num;}

            token tok = {.op_value=0, .int_value=num, .is_operand=1, .is_operator=0};
            tokens[cur_token] = tok;
            cur_token++;
        }

        else if (string[i] == 40 || string[i] == 41) {
            token tok = {.op_value=string[i], .int_value=0, .is_operand=0, .is_operator=1};
            tokens[cur_token] = tok;
            cur_token++;
            i++;
        }

            // If roman numeral (i/I, x/X, v/V)
        else if (is_rn(string[i]) || (string[i] == 45 && is_rn(string[i+1]))) {

            // If negative
            bool neg = string[i] == 45;

            // Increment to number
            if (neg) {i++;}

            int size = 0;
            char *roman_numeral = (char *) malloc(1);
            // Keep incrementing until not roman numeral
            while (is_rn(string[i])) {
                // Increment size
                size++;
                // Reallocate size
                roman_numeral = (char *) realloc(roman_numeral, size);
                roman_numeral[size - 1] = string[i];
                i++;
            }

            int value = roman_to_int(roman_numeral);
            if (neg) {value = -1 * value;}
            token tok = {.op_value=0, .int_value=value, .is_operand=1, .is_operator=0};
            free(roman_numeral);
            tokens[cur_token] = tok;
            cur_token++;

        }

            // Operator
        else if (string[i] == 42 || string[i] == 43 || string[i] == 45 || string[i] == 47) {
            token tok = {.op_value=string[i], .int_value=0, .is_operand=0, .is_operator=1};
            tokens[cur_token] = tok;
            cur_token++;
            i++;
        }

    }


}


#endif //INC_306_CALCULATOR_TOKEN_H

