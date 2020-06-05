#include "../headers/Print.h"


Print::Print(XMLParser& xml)
	: XMLOperation(xml, "print") {};

void Print::execute() {
	xml.print(std::cout);
}