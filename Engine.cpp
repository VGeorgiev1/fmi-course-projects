#include "Engine.h"
#include <cmath>

Engine::~Engine() {
    if (functions.size() == 0) {
        return;
    }

    std::map<std::string, Call*>::iterator it;

    for (it = functions.begin(); it != functions.end(); it++)
    {
        recursiveDelete(it->second);
    }

}
void Engine::recursiveDelete(Call* call) {
    for (int i = 0; i < call->nextCalls.size(); i++) {
        recursiveDelete(call->nextCalls[i]);
    }
    delete call;
}
Call* Engine::recursiveCopy(Call* call) {
    Call* nCall = new Call(*call);
    for (int i = 0; i < call->nextCalls.size(); i++) {
        nCall->nextCalls[i] = recursiveCopy(call->nextCalls[i]);
    }
    return nCall;

};
Result Engine::binary_validator(std::vector<Call*> args) {

    Result left = execute(args[0]);
    Result right = execute(args[1]);

    if (left.type == ERROR) {
        return left;
    }
    if (right.type == ERROR) {
        return right;
    }

    if (left.val.size() != 1 || right.val.size() != 1 ||
        left.val[0]->head.get_type() != IDENTITY ||
        right.val[0]->head.get_type() != IDENTITY) {

        return Result("Function value not determined!");
    }

    return Result(RESULT, std::vector<Call*>{ left.val[0], right.val[0] });
}

// This validator is for atoms that dont need to execute all of their arguments in order to return result
// Only the first arguments needs to be evaluated so the underlying atom can make decision for its evaluation
Result Engine::conditional_validator(std::vector<Call*> args) {
    if (args.size() <= 1) {
        return Result("Not anough arguments!");
    }

    Result condition = execute(args[0]);

    if (condition.type == ERROR) {
        return condition;
    }

    std::vector<Call*> resultCalls;

    resultCalls.push_back(condition.val[0]);

    resultCalls.insert(resultCalls.end(), args.begin() + 1, args.end());

    return Result(RESULT, resultCalls);

}

Result Engine::unary_validator(std::vector<Call*> args) {
    if (args.size() != 1) {
        return Result("Not anough arguments!");
    }

    Result left = execute(args[0]);

    if (left.val.size() != 1 || left.val[0]->head.get_type() != IDENTITY) {
        return Result("Result of function is not determined!");
    };

    return left;
}

Result Engine::add(Result operands) {

    double res = operands.val[0]->val + operands.val[1]->val;

    return Result(RESULT, std::vector<Call*>{new Call({ Token(IDENTITY,"id"), false, false, std::vector<Call*>(), res })});
}

Result Engine::sub(Result operands) {

    double res = operands.val[0]->val - operands.val[1]->val;

    return Result(RESULT, std::vector<Call*>{new Call({ Token(IDENTITY,"id"), false, false, std::vector<Call*>(), res })});
}

Result Engine::mul(Result operands) {

    double res = operands.val[0]->val * operands.val[1]->val;

    return Result(RESULT, std::vector<Call*>{new Call({ Token(IDENTITY,"id"), false, false, std::vector<Call*>(), res })});
}

Result Engine::div(Result operands) {

    if (operands.val[1]->val == 0) {
        return Result("div: Division by 0!");
    }

    double res = operands.val[0]->val / operands.val[1]->val;

    return Result(RESULT, std::vector<Call*>{new Call({ Token(IDENTITY,"id"), false, false, std::vector<Call*>(), res })});
}

Result Engine::pow(Result operands) {
    double result = operands.val[0]->val;

    for (int i = 0; i < operands.val[1]->val; i++) {
        result *= result;
    }

    return Result(RESULT, std::vector<Call*>{new Call({ Token(IDENTITY,"id"), false,false, std::vector<Call*>(), result })});
}

Result Engine::eq(Result operands) {
    return Result(RESULT, std::vector<Call*>{new Call({ Token(IDENTITY,"id"), false, false, std::vector<Call*>(), (operands.val[0]->val == operands.val[1]->val) ? 1.0 : 0.0 })});
}

Result Engine::le(Result operands) {
    return Result(RESULT, std::vector<Call*>{new Call({ Token(IDENTITY,"id"), false,false, std::vector<Call*>(), (operands.val[0]->val <= operands.val[1]->val ? 1.0 : 0.0) })});
}

Result Engine::cos(Result operand) {
    return Result(RESULT, std::vector<Call*>{new Call({ Token(IDENTITY,"id"), false, false, std::vector<Call*>(), std::cos(operand.val[0]->val) })});
}

Result Engine::sqrt(Result operands) {

    if (operands.val[0]->val < 0) {
        return Result("sqrt: Cant take square root of negative numbers!");
    }

    return Result(RESULT, std::vector<Call*>{new Call({ Token(IDENTITY,"id"), false, false, std::vector<Call*>(), std::sqrt(operands.val[0]->val) })});
}

Result Engine::sin(Result operand) {
    return Result(RESULT, std::vector<Call*>{new Call({ Token(IDENTITY,"id"), false, false, std::vector<Call*>(), std::sin(operand.val[0]->val) })});
}

Result Engine::nand(Result operands) {
    if (operands.val[0]->val == 0.0) {
        return Result(RESULT, std::vector<Call*>{new Call({ Token(IDENTITY,"id"), false, false, std::vector<Call*>(), 1 })});
    }

    Result right = execute(operands.val[1]);

    return Result(RESULT, std::vector<Call*>{new Call({ Token(IDENTITY,"id"), false, false, std::vector<Call*>(), (!operands.val[0]->val || !right.val[0]->val) ? 1.0 : 0.0 })});

}

Result Engine::if_(Result operands) {

    if (operands.val[0]->val != 0) {
        return execute(operands.val[1]);
    }

    return execute(operands.val[2]);
}

void Engine::set_up_atoms() {
    atoms["add"] = Atom({ &Engine::add, &Engine::binary_validator, 2 });
    atoms["sub"] = Atom({ &Engine::sub, &Engine::binary_validator, 2 });
    atoms["mul"] = Atom({ &Engine::mul, &Engine::binary_validator, 2 });
    atoms["div"] = Atom({ &Engine::div, &Engine::binary_validator, 2 });
    atoms["pow"] = Atom({ &Engine::pow, &Engine::binary_validator, 2 });
    atoms["eq"] = Atom({ &Engine::eq,  &Engine::binary_validator, 2 });
    atoms["le"] = Atom({ &Engine::le,  &Engine::binary_validator, 2 });


    atoms["sin"] = Atom({ &Engine::sin, &Engine::unary_validator, 1 });
    atoms["cos"] = Atom({ &Engine::cos, &Engine::unary_validator, 1 });
    atoms["sqrt"] = Atom({ &Engine::sqrt, &Engine::unary_validator, 1 });

    atoms["if"] = Atom({ &Engine::if_, &Engine::conditional_validator, 3 });
    atoms["nand"] = Atom({ &Engine::nand, &Engine::conditional_validator, 2 });

    lambdas["list"] = Lambda({ &Engine::list, false });
    lambdas["map"] = Lambda({ &Engine::map, true, 2 });
    lambdas["filter"] = Lambda({ &Engine::filter, true, 2 });
    lambdas["head"] = Lambda({ &Engine::head, false, 1 });
    lambdas["tail"] = Lambda({ &Engine::tail, false, 1 });
}

Result Engine::recursiveCall(Call* currentCall, std::vector<Call*> inline_args) {

    for (int i = 0; i < currentCall->nextCalls.size(); i++) {
        if (currentCall->nextCalls[i]->head.get_type() == POSITION_PARAMETER) {
            int position = std::stoi(currentCall->nextCalls[i]->head.val().substr(1));

            if (position >= inline_args.size()) {
                return Result("Positional parameter out of bounds!");
            }
            delete currentCall->nextCalls[i];
            currentCall->nextCalls[i] = new Call(*inline_args[position]);
        }
    }

    for (int i = 0; i < currentCall->nextCalls.size(); i++) {
        if (currentCall->nextCalls[i]->head.get_type() == FUNC) {
            recursiveCall(currentCall->nextCalls[i], inline_args);
        }
    }

    return Result(RESULT, std::vector<Call*>());
}
Engine::Engine() {
    set_up_atoms();
}
bool Engine::expectPointer(std::string name) {
    if (lambdas.find(name) == lambdas.end()) {
        return false;
    }

    return lambdas[name].expectPointer;
}
bool Engine::already_defined(std::string name) {
    if (functions.find(name) != functions.end() ||
        atoms.find(name) != atoms.end() ||
        lambdas.find(name) != lambdas.end()) {
        return true;
    }
    return false;
}
Result Engine::list(std::vector<Call*> vec) {
    ResultTypes type;
    std::vector<Call*> val;
    for (Call* c : vec) {
        Result res = execute(c);

        if (res.type == ERROR) {
            return res;
        }

        for (Call* c : res.val) {
            if (c->head.get_type() != IDENTITY) {
                return Result("list: expects number as argument");
            }
            val.push_back(c);
        }
    }

    return Result(RESULT, val);
}

Result Engine::filter(std::vector<Call*> vec) {
    std::vector<Call*> res;
    Call* filter = vec[0];

    Call* list = vec[1];

    Result listResult = execute(list);
    if (listResult.type == ERROR) {
        return listResult;
    }
    std::vector<Call*> listCalls = listResult.val;

    for (int i = 1; i < listCalls.size(); i++) {

        filter->nextCalls.push_back(listCalls[i]);
        Result r = execute(filter);

        if (r.type == ERROR) {
            return r;
        }

        for (Call* res_el : r.val) {

            if (res_el->val != 0 && res_el->val != 1) {
                return Result("Invalid filter function!");
            }

            if (res_el->val == 1) {
                res.push_back(listResult.val[i]);
            }
        }
        filter->nextCalls.clear();
    }

    return Result(RESULT, res);
}

Result Engine::map(std::vector<Call*> vec) {
    std::vector<Call*> res;

    Call* mapper = vec[0];

    Call* list = vec[1];

    Result listResult = execute(list);

    if (listResult.type == ERROR) {
        return listResult;
    }

    std::vector<Call*> listCalls = listResult.val;

    for (int i = 0; i < listCalls.size(); i++) {
        mapper->nextCalls.push_back(listCalls[i]);
        Result r = execute(mapper);
        if (r.type == ERROR) {
            return r;
        }

        for (Call* res_el : r.val) {
            res.push_back(res_el);
        }
        mapper->nextCalls.clear();
    }

    return Result(RESULT, res);
}
Result Engine::head(std::vector<Call*> vec) {

    if (vec.size() == 0) {
        return Result("HEAD: Not enough elements in the list!");
    }

    Result res = execute(vec[0]);

    if (res.type == ERROR) {
        return res;
    }

    return Result(RESULT, std::vector<Call*>{ res.val[0] });
}
Result Engine::tail(std::vector<Call*> vec) {
    std::vector<Call*> res;

    if (vec.size() == 0) {
        return { "tail: Not enough elements in the list!" };
    }

    Result listResult = execute(vec[0]);

    for (int i = 1; i < listResult.val.size(); i++) {

        Result r = execute(listResult.val[i]);

        if (r.type == ERROR) {
            return r;
        }

        res.push_back(r.val[0]);
    }

    return { RESULT, res };
}
void Engine::set_function(std::string name, Call* tree) {
    functions[name] = tree;
}

Result Engine::composite_function(std::string name, Call* inline_call) {
    if (functions.find(name) != functions.end()) {
        Call* call = functions[name];

        Call* callCpy = recursiveCopy(new Call(*call));

        Call* fullCpy = recursiveCopy(callCpy);

        Result res = recursiveCall(callCpy, inline_call->nextCalls);

        if (res.type == ERROR) {
            return res;
        }

        Result exec_res = execute(callCpy->nextCalls[0]);

        //srecursiveDelete(inline_call);
        delete callCpy;
        recursiveDelete(fullCpy);

        return exec_res;
    }

    return Result(name + ": Function not found!");
}

Result Engine::execute(Call* call) {
    std::string name = call->head.val();

    if (call->head.get_type() == IDENTITY) {
        return Result(RESULT, std::vector<Call*>{new Call(*call)});
    }

    if (atoms.find(name) != atoms.end()) {
        if (call->nextCalls.size() != atoms[name].number_of_args) {
            return Result(name + ": Invalid number of arguments!");
        }

        Result arguments_validations = (this->*(atoms[name].validator))(call->nextCalls);
        
        if (arguments_validations.type == ERROR) {
            return arguments_validations;
        }

        Result res = (this->*(atoms[name].func))(arguments_validations);

        for (Call* acall : arguments_validations.val) {
            delete acall;
        }

        if (res.type == ERROR) {
            return res;
        }


        return Result(RESULT, res.val);
    }
    else if (lambdas.find(name) != lambdas.end()) {
        Result result;

        Call* c = call;

        if (name != "list") {
            if (call->nextCalls.size() != lambdas[name].number_of_args) {
                return Result(name + ": Invalid number of parameters!");
            }
        }

        return (this->*(lambdas[name].func))(c->nextCalls);

    }
    else {
        return composite_function(name, call);
    }

    return Result("Uknown token `" + call->head.val() + "` +error!");
}