#include "Select.h"
#include <iostream>


Select::Select(Node& h)
	: XMLOperation(h, "select") {};

void Select::execute() {
	std::string id, key;

	std::cin >> id >> key;

	recursive_search(parent_node, id, key);
}

void Select::recursive_search(Node n, std::string id, std::string key) {

	Attribute* atr = n.get_attribute(key);

	if(n.get_id() == id && atr != nullptr) {
		std::cout << "Node " << n.get_name() << ", attribute: " << atr->get_name() << " value: " << atr->get_value();
	}

	if(!n.has_children()) {
		return;
	}

	std::vector<Node> children = n.get_children();

	for(std::vector<Node>::iterator it = children.begin(); it != children.end(); ++it) {
		recursive_search(*it, id, key);
	}

	return;

}
