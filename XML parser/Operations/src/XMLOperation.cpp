#include "../headers/XMLOperation.h"


XMLOperation::XMLOperation(XMLParser& xml, std::string name)
	: Operation(name), xml(xml) {};
