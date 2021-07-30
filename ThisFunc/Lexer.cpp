#include "Lexer.h"


Lexer::Lexer() {
    pos = 0;
};

void Lexer::set_current_expression(std::string exp) {
    current_expression = exp;
    pos = 0;
}

bool Lexer::isDeclaration() {
    std::size_t declarationIdx = current_expression.find("<-");

    return declarationIdx != std::string::npos;
}

bool Lexer::isNumber(std::string str) {
    try {
        double res = std::stod(str);

        if (isnan(res)) {
            return false;
        }

        return true;
    }
    catch (...) {
        return false;
    }
}

bool Lexer::consumed() {
    return (pos >= current_expression.size());
}

Token Lexer::get_next_token() {

    std::string currentToken;

    if (consumed()) {
        return Token(TOKENS::ERR, "ERROR");
    }

    while (pos < current_expression.size()) {

        if (isspace(current_expression[pos]) && currentToken.size() != 0) {
            if (currentToken == "<-") {
                return Token(ASSIGN, currentToken);
            }

            return Token(FUNC, currentToken);
        }

        if (isspace(current_expression[pos]) && currentToken.size() == 0) {
            if (currentToken.size() != 0) {

            }
            pos++;
            continue;
        }

        if (current_expression[pos] == '('
            || current_expression[pos] == ')'
            || current_expression[pos] == ',') {

            if (currentToken.size() != 0) {
                if (isNumber(currentToken)) {
                    return Token(LITERAL, currentToken);
                }

                if (currentToken[0] == '#') {
                    return Token(POSITION_PARAMETER, currentToken);
                }

                return Token(FUNC, currentToken);
            }
            else {
                currentToken.push_back(current_expression[pos]);

                pos++;

                return Token(DELIMITER, currentToken);
            }
        }
        currentToken.push_back(current_expression[pos]);
        pos++;
    }

    if (currentToken != "") {
        if (isNumber(currentToken)) {
            return Token(LITERAL, currentToken);
        }
        else {
            return Token(ERR, currentToken);
        }
    }
    return Token(ERR, currentToken);
}