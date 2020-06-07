#ifndef NEWCHILD_H
#define NEWCHILD_H
#include "XMLOperation.h"

class Newchild : public XMLOperation {
public:
	Newchild(XMLParser& h);
	void execute();

};

#endif