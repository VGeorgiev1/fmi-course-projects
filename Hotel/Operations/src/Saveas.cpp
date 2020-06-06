#include "../headers/Saveas.h"
#include "../headers/Save.h"
#include <fstream>
#include <stdio.h>

Saveas::Saveas(Hotel& h)
	: FileOperation(h, "saveas") {};


void Saveas::execute() {
	std::string name;

	std::cin >> name;

	FileOperation* op = (FileOperation*)(hotel_.find_operation("save"));

	if(op != nullptr) {

		op->set_file_name(name);

		op->execute();
	}

}

