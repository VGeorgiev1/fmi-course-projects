#include "XMLOperation.h"


XMLOperation::XMLOperation(Node& node, std::string name)
	: Operation(name), parent_node(node) {};

