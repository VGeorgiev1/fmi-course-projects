#ifndef SELECT_H
#define SELECT_H
#include "XMLOperation.h"
#include "Attribute.h"

class Select : public XMLOperation {
public:
	Select(Node& h);
	void execute();
	void recursive_search(Node n, std::string id, std::string key);
};

#endif
