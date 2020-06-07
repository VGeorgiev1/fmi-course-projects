#include "../headers/Select.h"
#include <iostream>


Select::Select(XMLParser& xml)
	: XMLOperation(xml, "select") {};

void Select::execute() {
	std::string id, key;

	std::cin >> id >> key;

	Node* n = xml.recursive_search(xml.get_parent(), id);

	if (n == nullptr) {
		throw XMLException("Node with this id cannot be found!");
	}

	Attribute* atr = n->get_attribute(key);

	if (atr == nullptr) {

		throw XMLException("Node with this id has no attirbute with this key");
	}

	std::cout << "Node " << n->get_name() << ", attribute: " << atr->get_name() << " value: " << atr->get_value() << std::endl;
}