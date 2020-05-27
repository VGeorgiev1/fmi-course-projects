#ifndef PRINT_H
#define PRINT_H
#include "FileOperation.h"

class Print : public FileOperation {
public:
	Print(XMLParser& parser);
	void execute();
};

#endif
