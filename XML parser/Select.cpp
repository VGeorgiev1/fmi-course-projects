#include "Select.h"
#include <iostream>


Select::Select(Node* h)
	: XMLOperation(h, "select") {};

void Select::execute() {
	std::string id, key;

	std::cin >> id >> key;

	Node* n = recursive_search(parent_node, id);

	Attribute* atr = n->get_attribute(key);

	if (atr != nullptr) {
		std::cout << "Node " << n->get_name() << ", attribute: " << atr->get_name() << " value: " << atr->get_value();
		return;
	}

	std::cout << "Node " << n->get_name() << "has no attribute: " << key;
	return;
}