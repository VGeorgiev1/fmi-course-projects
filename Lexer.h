#pragma once
#include "Token.h"
class Lexer {
    int pos;
    std::string current_expression;
public:
    Lexer();

    void set_current_expression(std::string exp);

    bool isDeclaration();

    bool isNumber(std::string str);

    bool consumed();

    Token get_next_token();
};