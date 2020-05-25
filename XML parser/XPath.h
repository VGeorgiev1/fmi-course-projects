#pragma once
#ifndef XPATH_OPERATION_H
#define XPATH_OPERATION_H
#include "XMLOperation.h"
#include "Node.h"

class XPATH : public XMLOperation {
public:
	XPATH(Node* node);
	void execute();
	void xpath_recursive_search(Node* const& n, std::vector<std::string>::iterator, std::vector<std::string>::iterator end, int index_of_results, std::vector<Node*>& results);
};

#endif