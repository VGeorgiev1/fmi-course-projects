#include "Close.h"
#include <fstream>
#include <stdio.h>

Close::Close(Hotel& h)
	: FileOperation(h, "close") {};


void Close::execute() {
	file_name = "";

	hotel_.remove_rooms();
	hotel_.remove_records();
}

