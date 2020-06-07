#include "../headers/Close.h"
#include <fstream>
#include <stdio.h>

Close::Close(XMLParser& h)
	: FileOperation(h, "close") {};


void Close::execute() {

	parser.remove_nodes();

	FileOperation* save = (FileOperation*)(parser.find_operation("save"));
	FileOperation* saveas = (FileOperation*)(parser.find_operation("saveas"));

	if(save != nullptr && saveas != nullptr) {
		save->set_file_name("");
		saveas->set_file_name("");
	}

	parser.set_operatable(false);

	std::cout << "Successfully closed " << file_name << std::endl;
}

