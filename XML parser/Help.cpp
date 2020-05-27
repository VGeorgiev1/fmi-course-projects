#include <iostream>
#include "Help.h"

Help::Help(XMLParser& h)
	: FileOperation(h, "help") {};

void Help::execute() {
	std::cout << "prin                       - prints formatted view of the xml opened" << std::endl;
	std::cout << "select <id> <key>          - prints the value of <key> attrictue of node with <id>" << std::endl;
	std::cout << "set <id> <key> <value>	 - set the value of <key> attrictue of node with <id>"  << std::endl;
	std::cout << "children <id>              - prints the attributes of the children of the element with <id>" << std::endl;
	std::cout << "child <id> <n>             - returns the <n> child of element with <id>" << std::endl;
	std::cout << "text <id>                  - return list of free rooms for <date>" << std::endl;
	std::cout << "delete <id> <key>          - removes attribute <key> from element with <id>" << std::endl;
	std::cout << "newchild <id>              - adds new node to the element with <id>" << std::endl;
	std::cout << "xpath <XPath>              - execute xpath request for the currenctly opened xml" << std::endl;
}