#include "Saveas.h"
#include <fstream>
#include <stdio.h>

Saveas::Saveas(XMLParser& parser)
	: FileOperation(parser, "saveas") {};


void Saveas::execute() {
	std::string name;

	std::cin >> name;

	FileOperation* op = (FileOperation*)(parser.find_operation("save"));

	if(op != nullptr) {

		op->set_file_name(name);

		op->execute();
	}

}

