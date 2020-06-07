#include "../headers/Save.h"
#include <fstream>
#include <stdio.h>

Save::Save(XMLParser& parser)
	: FileOperation(parser, "save") {};

void Save::execute() {
	std::ofstream stream;

	if (file_name.size() == 0) {
		return;
	}
	stream.open(file_name);

	if (stream.is_open()) {
		parser.print(stream);
		std::cout << "File " << file_name << " was saved!" << std::endl;
	}
	
}

