#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Token.h"
#include "Lexer.h"
#include "Call.h"
#include "Result.h"
#include "Engine.h"
#include "Parser.h"
#include "Output.h"
#include "ThisFuncContext.h"

using namespace std;


int main(int argc, char *argv[]) {
   Lexer lex = Lexer();

   Engine engine = Engine();

   Parser parser = Parser(lex, engine);

   ThisFuncContext context = ThisFuncContext(parser);

   if (argc == 2) {

       ifstream file;

       std::string fileName = argv[1];

       file.open(fileName);

       if (!file.is_open()) {
           std::cout << "Program not found!";
       }

       std::stringstream buffer;

       buffer << file.rdbuf();

       Output res = context.executeCode(buffer.str());
       
       context.printer(res);
       
   }
   else {
       std::string input;

       while (true) {
           std::getline(cin, input);

           if (input == "exit") {
               break;
           }

           Output res = context.input(input);
           
           context.printer(res);
       }
   }
}