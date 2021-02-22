#pragma once
#include <vector>
#include "Call.h"
#include "Result.h"
#include <map>
class Engine {
private:
    typedef Result*(Engine::* Functor)(std::vector<Call*>); // function pointer type
    typedef Result*(Engine::* AtomFunctor)(Result*);
    typedef Result*(Engine::* Validator)(std::vector<Call*>);

    struct Atom {
        AtomFunctor func;
        Validator validator;
        int number_of_args;
    };
    struct Lambda {
        Functor func;
        bool expectPointer;
        int number_of_args;
    };

    typedef std::map<std::string, Atom> Atoms;
    typedef std::map<std::string, Lambda> Lambdas;

    std::map<std::string, Call*> functions;
    Lambdas lambdas;
    Atoms atoms;



    Result* binary_validator(std::vector<Call*> args);


    // This validator is for atoms that dont need to execute all of their arguments in order to return result
    // Only the first arguments needs to be evaluated so the underlying atom can make decision for its evaluation
    Result* conditional_validator(std::vector<Call*> args);

    Result* unary_validator(std::vector<Call*> args);

    Result* add(Result* operands);

    Result* sub(Result* operands);

    Result* mul(Result* operands);

    Result* div(Result* operands);

    Result* pow(Result* operands);

    Result* eq(Result* operands);

    Result* le(Result* operands);

    Result* cos(Result* operand);

    Result* sqrt(Result* operands);

    Result* sin(Result* operand);

    Result* nand(Result* operands);

    Result* if_(Result* operands);

    void set_up_atoms();

    Result* recursiveCall(Call* currentCall, std::vector<Call*> inline_args);

public:
    Engine();

    bool expectPointer(std::string name);

    bool already_defined(std::string name);

    Result* list(std::vector<Call*> vec);

    Result* filter(std::vector<Call*> vec);

    Result* map(std::vector<Call*> vec);

    Result* head(std::vector<Call*> vec);

    Result* tail(std::vector<Call*> vec);

    void set_function(std::string name, Call* tree);

    Result* composite_function(std::string name, Call* inline_call);

    Result* execute(Call* call);
};