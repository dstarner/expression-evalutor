//
// Created by Dan Starner on 2/8/17.
//

#ifndef INC_306_CALCULATOR_TOKEN_H
#define INC_306_CALCULATOR_TOKEN_H

struct token {

    // Values of token
    char op_value;
    int int_value;

    // Type of token
    int is_operand;
    int is_operator;
};

#endif //INC_306_CALCULATOR_TOKEN_H
