#pragma once
#include "Lexer.h"
#include "Engine.h"

class Parser {
    Lexer lex;
    Engine engine;
public:
    Parser(Lexer lexer, Engine eng);

    Parser(const Parser& old_obj);

    Parser(Parser&& obj);

    Result tree_parse(Call& currentRoot);

    Result parse();

    Lexer& get_lex();
};