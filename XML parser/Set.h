#ifndef SET_H
#define SET_H
#include "XMLOperation.h"
#include "Attribute.h"

class Set : public XMLOperation {
public:
	Set(Node& h);
	void execute();
	void recursive_search(Node n, std::string id, std::string key, std::string value);
};

#endif
