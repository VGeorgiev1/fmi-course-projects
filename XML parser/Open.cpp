#include "Open.h"
#include <fstream>
#include <stdio.h>

Open::Open(XMLParser& parser)
	: FileOperation(parser, "open") {};


void Open::execute() {
	std::string name;

	std::cin >> name;

	parser.parse(name);
}

bool Open::file_opened() {
	return file_name.size() == 0;
}