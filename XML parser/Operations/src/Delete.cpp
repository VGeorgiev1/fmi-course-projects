#include "../headers/Delete.h"
#include <iostream>


Delete::Delete(XMLParser& xml)
	: XMLOperation(xml, "delete") {};

void Delete::execute() {
	std::string id, key;

	std::cin >> id >> key;

	Node* n = xml.recursive_search(xml.get_parent(), id);

	bool result = n->remove_attribute(key);

	std::cout << "Attribute " << key << " " << (result ? " was removed" : " wasnt found") << std::endl;
}