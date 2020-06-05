#include "../headers/Select.h"
#include <iostream>


Select::Select(XMLParser& xml)
	: XMLOperation(xml, "select") {};

void Select::execute() {
	std::string id, key;

	std::cin >> id >> key;

	Node* n = xml.recursive_search(xml.get_parent(), id);

	Attribute* atr = n->get_attribute(key);

	if (atr != nullptr) {
		std::cout << "Node " << n->get_name() << ", attribute: " << atr->get_name() << " value: " << atr->get_value() << std::endl;
		return;
	}

	std::cout << "Node " << n->get_name() << "has no attribute: " << key;
	return;
}