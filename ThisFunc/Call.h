#pragma once
#include "Token.h"
#include <vector>
struct Call {
    Token head;
    bool expectArgument;
    bool expectFuncPointer;
    std::vector<Call*> nextCalls;
    double val; // calls can only be evalutaded to single value;
};
