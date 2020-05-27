#include "FileOperation.h"


FileOperation::FileOperation(XMLParser& parser, std::string name)
	: Operation(name), parser(parser) {};

void FileOperation::set_file_name(std::string file) {
	file_name = file;
}
