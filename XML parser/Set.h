#ifndef SET_H
#define SET_H
#include "XMLOperation.h"
#include "Attribute.h"

class Set : public XMLOperation {
public:
	Set(Node* h);
	void execute();
};

#endif
