#ifndef SELECT_H
#define SELECT_H
#include "XMLOperation.h"
#include "../../Attribute.h"

class Select : public XMLOperation {
public:
	Select(XMLParser& h);
	void execute();
};

#endif
