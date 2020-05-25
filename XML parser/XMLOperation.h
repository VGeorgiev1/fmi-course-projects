#ifndef XML_OPERATION_H
#define XML_OPERATION_H
#include "Operation.h"
#include "Node.h"

class XMLOperation : public Operation {
protected:
	Node& parent_node;
public:
	XMLOperation(Node& node, std::string name);
};

#endif