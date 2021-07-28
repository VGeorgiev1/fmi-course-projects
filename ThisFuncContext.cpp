#include "ThisFuncContext.h"
#include <iostream>
#include <sstream>

ThisFuncContext::ThisFuncContext(Parser p) : parser(p) {};

Output ThisFuncContext::input(std::string in) {
    parser.get_lex().set_current_expression(in);
    Result res = parser.parse();
    if (res.type == ERROR) {
        return Output({ std::vector<double>(), res.error });
    }
    else {
        std::vector<double> identities;

        for (Call* c : res.val) {
            identities.push_back(c->val);
            delete c;
        }

        return Output({ identities, "" });
    }
};

Output ThisFuncContext::executeCode(std::string program) {
    std::istringstream st(program);
    std::string line;

    Output lastOutput;

    while (std::getline(st, line)) {
        Output l_e = input(line);
        if (l_e.error != "") {
            return l_e;
        }
        lastOutput = l_e;
    }
    return lastOutput;
}

void ThisFuncContext::printer(Output out) {
    std::cout << "> ";

    if (out.error != "") {
        std::cout << out.error << "\n";
    }
    if (out.val.size() == 0) {
        std::cout << "\n";
        return;
    }
    else {
        if (out.val.size() == 1) {
            std::cout << out.val[0];
        }
        else {
            std::cout << "[ ";
            for (size_t i = 0; i < out.val.size(); ++i)
            {
                if (i != 0)
                    std::cout << ", ";
                std::cout << out.val[i];
            }
            std::cout << " ]";
        }
    }
    std::cout << "\n";
}