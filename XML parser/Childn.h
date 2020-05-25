#ifndef CHILDN_H
#define CHILDN_H
#include "XMLOperation.h"
#include "Attribute.h"

class Childn : public XMLOperation {
public:
	Childn(Node& h);
	void execute();
    Node* recursive_search(Node* n,std::string id);
};

#endif
