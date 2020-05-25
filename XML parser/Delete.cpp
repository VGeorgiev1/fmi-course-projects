#include "Delete.h"
#include <iostream>


Delete::Delete(Node* h)
	: XMLOperation(h, "delete") {};

void Delete::execute() {
	std::string id, key;

	std::cin >> id >> key;

	Node* n = recursive_search(parent_node, id);

	n->remove_attribute(key);

	return;
}