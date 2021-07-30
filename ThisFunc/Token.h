#pragma once
#include <string>
enum TOKENS { LITERAL, IDENTITY, FUNC, POSITION_PARAMETER, ASSIGN, DELIMITER, EMPTY, CALL_POSITION, ERR };

class Token {
    TOKENS type;
    std::string value;
public:

    Token(TOKENS token_type, std::string token_value);

    Token();

    TOKENS get_type();

    std::string val();

    void set_val(std::string new_val);

    void stringify();
};