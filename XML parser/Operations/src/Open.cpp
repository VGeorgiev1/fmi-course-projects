#include "../headers/Open.h"
#include <fstream>
#include <stdio.h>

Open::Open(XMLParser& parser)
	: FileOperation(parser, "open") {};


void Open::execute() {
	std::string name;

	std::cin >> name;

	try {
		parser.parse(name);
		parser.set_operatable(true);

		FileOperation* save = (FileOperation*)(parser.find_operation("save"));

		if (save != nullptr) {
			save->set_file_name(name);
		}
	}
	catch (std::invalid_argument err) {
		std::cout << err.what() << std::endl;
		parser.remove_nodes();
	}
	std::cout << "file " << name << " opened successufuly!" << std::endl;
}

bool Open::file_opened() {
	return file_name.size() == 0;
}