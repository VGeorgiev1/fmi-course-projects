#include "Parser.h"
#include <iostream>

Parser::Parser(Lexer lexer, Engine eng) {
    lex = lexer;
    engine = eng;
}

Parser::Parser(const Parser& old_obj) {
    lex = old_obj.lex;
    engine = old_obj.engine;
}

Parser::Parser(Parser&& obj) {
    lex = obj.lex;
    engine = obj.engine;
}

Result* Parser::tree_parse(Call* currentRoot) {

    int argumentIdx = 0;
    bool expectPointer = false;

    while (!lex.consumed()) {

        Token t = lex.get_next_token();

        if (t.get_type() == ERR) {
            return new Result("Uknown token: " + t.val());
        }

        if (t.get_type() == FUNC) {
            std::string funcName = t.val();

            if (currentRoot->head.val() == "") {
                currentRoot->head.set_val(t.val());
                if (engine.expectPointer(t.val())) {
                    currentRoot->expectFuncPointer = true;
                }
            }
            else {

                if (currentRoot->expectFuncPointer) {
                    currentRoot->expectFuncPointer = false;
                    currentRoot->nextCalls.push_back(new Call({ t, false, false, std::vector<Call*>(), 0 }));
                    continue;
                }
                expectPointer = engine.expectPointer(t.val());

                currentRoot->nextCalls.push_back(new Call({ t, false, expectPointer, std::vector<Call*>(), 0 }));

            }

            t = lex.get_next_token();

            if (t.val() != "(" && t.get_type() != ASSIGN) {
                return new Result("Invalid syntax!");
            }

            if (t.get_type() == ASSIGN) {

                if (engine.already_defined(funcName)) {
                    return new Result("Function " + funcName + " already defined!");
                }

                Result* res = tree_parse(currentRoot);
                if (res->type == ERROR) {
                    return res;
                }
            }
            else if (currentRoot->nextCalls.size() > 0) {
                //currentRoot.nextCalls[currentRoot.nextCalls.size() - 1].expectArgument = !expectPointer;
                Result* res = tree_parse(currentRoot->nextCalls[currentRoot->nextCalls.size() - 1]);

                if (res->type == ERROR) {
                    return res;
                }
                else if (res->type == RESULT) {
                    currentRoot->nextCalls.pop_back();
                    for (Call* r : res->val) {
                        currentRoot->nextCalls.push_back(r);
                    }
                }
                currentRoot->expectArgument = false;
            }
        }

        if (t.get_type() == LITERAL || t.get_type() == POSITION_PARAMETER) {

            if (t.get_type() == POSITION_PARAMETER) {
                currentRoot->nextCalls.push_back(new Call({ t, false, false, std::vector<Call*>(), 0 }));
            }
            else {
                double d_val = 0;

                try {
                    d_val = std::stod(t.val());
                }
                catch (std::invalid_argument e) {
                    return new Result("Invalid argument!");
                }

                Token identity = Token(IDENTITY, "id");

                currentRoot->nextCalls.push_back(new Call({ identity, false, false, std::vector<Call*>(), d_val }));
            }

            currentRoot->expectArgument = false;
        }

        if (t.get_type() == DELIMITER) {
            if (t.val() == "") {
                return new Result("Paranthesis missmatch!");
            }
            if (t.val() == ",") {
                if (currentRoot->expectArgument) {
                    return new Result("Expected argument got: ,");
                }
                if (!currentRoot->expectArgument) {
                    currentRoot->expectArgument = true;
                }
                argumentIdx++;
            }

            if (t.val() == ")") {
                if (currentRoot->expectArgument) {
                    return new Result("Argument missmatch!");
                }

                currentRoot->expectArgument = false;

                return new Result(VOID, std::vector<Call*>());
            }
        }
    }
    return new Result(VOID, std::vector<Call*>());
}

Result* Parser::parse() {
    Call* node = new Call({ Token(FUNC, ""), false, false, std::vector<Call*>(), 0 });
    
    Result* res = tree_parse(node);

    if (res->type == ERROR) {
        return res;
    }

    if (lex.isDeclaration()) {
        engine.set_function(node->head.val(), node);
        return res;
    }
    else {
        return engine.execute(node);
    }
}
Lexer& Parser::get_lex() {
    return lex;
}