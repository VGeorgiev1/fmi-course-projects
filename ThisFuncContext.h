#pragma once
#include "Parser.h"
#include "Output.h"

class ThisFuncContext {
    Parser parser;
public:

    ThisFuncContext(Parser p);

    Output input(std::string in);

    Output executeCode(std::string program);

    void printer(Output out);
};