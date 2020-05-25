#ifndef SELECT_H
#define SELECT_H
#include "XMLOperation.h"
#include "Attribute.h"

class Select : public XMLOperation {
public:
	Select(Node* h);
	void execute();
};

#endif
