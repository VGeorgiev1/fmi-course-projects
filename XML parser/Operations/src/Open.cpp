#include "../headers/Open.h"
#include <fstream>
#include <stdio.h>
#include "../../XMLParserException.h"
#include "../../XMLException.h"

Open::Open(XMLParser& parser)
	: FileOperation(parser, "open") {};


void Open::execute() {
	std::string name;

	std::cin >> name;

	try {
		parser.parse(name);
		parser.set_operatable(true);

		FileOperation* save = (FileOperation*)(parser.find_operation("save"));
		FileOperation* saveas = (FileOperation*)(parser.find_operation("saveas"));

		if (save != nullptr && saveas != nullptr) {
			save->set_file_name(name);
			save->set_file_name(name);
		}
		std::cout << "file " << name << " opened successufuly!" << std::endl;
	}
	catch (XMLParserException err) {
		std::cout << err.what() << std::endl;
		parser.remove_nodes();
		throw XMLException("There was a problem parsing the file!");
	}
}

bool Open::file_opened() {
	return file_name.size() == 0;
}