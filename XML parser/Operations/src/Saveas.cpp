#include "../headers/Saveas.h"
#include <fstream>
#include <stdio.h>

Saveas::Saveas(XMLParser& parser)
	: FileOperation(parser, "saveas") {};


void Saveas::execute() {
	std::string name;

	std::cin >> name;

	FileOperation* save = (FileOperation*)(parser.find_operation("save"));
	FileOperation* close = (FileOperation*)(parser.find_operation("close"));

	if(save != nullptr && close != nullptr) {

		save->set_file_name(name);
		close->set_file_name(name);

		save->execute();

		std::cout << "File " << name << " was saved!" << std::endl;
		return;
	}

	std::cout << "File couldnt not be saved!" << std::endl;

}

