#ifndef CHILDREN_H
#define CHILDREN_H

#include "XMLOperation.h"
#include "../../Attribute.h"

class Children : public XMLOperation {
public:
	Children(XMLParser& xml);
	void execute();
};

#endif
