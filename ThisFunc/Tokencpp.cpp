#include "Token.h"

Token::Token(TOKENS token_type, std::string token_value) {
    type = token_type;
    value = token_value;
}

Token::Token() {
    type = TOKENS::EMPTY;
}

TOKENS Token::get_type() {
    return type;
}

std::string Token::val() {
    return value;
}

void Token::set_val(std::string new_val) {
    value = new_val;
}

void Token::stringify() { // debugging purpouses only
    std::string token_type;
    switch (type)
    {
    case LITERAL:
        token_type = "LITERAL";
        break;
    case FUNC:
        token_type = "FUNC";
        break;
    case POSITION_PARAMETER:
        token_type = "POSITION_PARAMETER";
        break;
    case ASSIGN:
        token_type = "ASSIGN";
        break;
    case DELIMITER:
        token_type = "DELIMITER";
        break;
    default:
        token_type = "NULL";
        break;
    }
}