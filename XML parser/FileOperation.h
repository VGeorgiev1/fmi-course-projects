#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H
#include "Operation.h"
#include "XMLParser.h"

class FileOperation : public Operation {
protected:
	XMLParser& parser;
	std::string file_name = "";
public:
	FileOperation(XMLParser& parent, std::string name);
	void set_file_name(std::string file);
};

#endif 
