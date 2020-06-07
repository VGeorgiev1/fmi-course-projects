#include "../headers/Delete.h"
#include <iostream>


Delete::Delete(XMLParser& xml)
	: XMLOperation(xml, "delete") {};

void Delete::execute() {
	std::string id, key;

	std::cin >> id >> key;

	Node* n = xml.recursive_search(xml.get_parent(), id);

	if (n == nullptr) {
		throw XMLException("No node with this id can be found!");
	}

	bool result = n->remove_attribute(key);

	if (!result) {
		throw XMLException("Attribute wasn't found");
	}

	std::cout << "Attribute " << key << " " << " was removed" << std::endl;
}