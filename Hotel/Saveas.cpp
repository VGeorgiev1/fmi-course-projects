#include "Saveas.h"
#include "Save.h"
#include <fstream>
#include <stdio.h>

Saveas::Saveas(Hotel& h)
	: FileOperation(h, "saveas") {};


void Saveas::execute() {
	std::string name;

	std::cin >> name;

	file_name = name;

	Save(hotel_).execute();

}

