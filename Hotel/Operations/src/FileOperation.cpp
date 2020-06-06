#include "../headers/FileOperation.h"


FileOperation::FileOperation(Hotel& hotel, std::string name)
	: Operation(name), hotel_(hotel) {};

void FileOperation::set_file_name(std::string file) {
	file_name = file;
}
