#ifndef PRINT_H
#define PRINT_H
#include "XMLOperation.h"

class Print : public XMLOperation {
public:
	Print(XMLParser& parser);
	void execute();
};

#endif
