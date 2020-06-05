#ifndef XML_OPERATION_H
#define XML_OPERATION_H
#include "Operation.h"
#include "../../XMLparser.h"

class XMLOperation : public Operation {
protected:
	XMLParser& xml;
public:
	XMLOperation(XMLParser& node, std::string name);
};

#endif