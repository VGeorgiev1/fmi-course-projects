#include "Print.h"


Print::Print(XMLParser& h)
	: FileOperation(h, "print") {};

void Print::execute() {
	parser.print(std::cout);
}