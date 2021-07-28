#pragma once
#include<vector>
#include "Call.h"
enum ResultTypes { RESULT, VOID, ERROR };

struct Result {
    ResultTypes type;
    std::vector<Call*> val;
    std::string error;
    Result(std::string _error) : type(ERROR), val(std::vector<Call*>()), error(_error) {}
    Result(ResultTypes _type, std::vector<Call*> _val) : type(_type), val(_val), error("Ok") {}
    Result() {}
};