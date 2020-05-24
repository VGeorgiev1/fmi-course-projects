#include "Close.h"
#include <fstream>
#include <stdio.h>

Close::Close(Hotel& h)
	: FileOperation(h, "close") {};


void Close::execute() {
	

	hotel_.remove_rooms();
	hotel_.remove_records();
	

	FileOperation* save = (FileOperation*)(hotel_.find_operation("save"));

	if(save != nullptr) {
		save->set_file_name(file_name);
	}
	hotel_.set_operatable(false);
	std::cout << "Successfully closed " << file_name << std::endl;
}

