#include "Exit.h"
#include <fstream>
#include <stdio.h>

Exit::Exit(Hotel& h)
	: FileOperation(h, "exit") {};


void Exit::execute() {
	std::cout << "Exiting the program...";

	exit(0);
}

