#include "Close.h"
#include <fstream>
#include <stdio.h>

Close::Close(XMLParser& h)
	: FileOperation(h, "close") {};


void Close::execute() {

	parser.remove_nodes();

	FileOperation* save = (FileOperation*)(parser.find_operation("save"));

	if(save != nullptr) {
		save->set_file_name(file_name);
	}

	parser.set_operatable(false);

	std::cout << "Successfully closed " << file_name << std::endl;
}

