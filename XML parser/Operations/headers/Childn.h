#ifndef CHILDN_H
#define CHILDN_H
#include "XMLOperation.h"
#include "../../Attribute.h"

class Childn : public XMLOperation {
public:
	Childn(XMLParser& xml);
	void execute();
};

#endif
